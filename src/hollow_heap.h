#include<vector>
#include<cstddef>
#include<iostream>

// Predeclaration of the hollow_heap_item. This is necessary for the struct 
// definition of hollow_heap_node.
template< class T, class K >
struct hollow_heap_item;

// This is the definition of the hollow_heap_node struct. hollow_heap_nodes
// keep the structure of the DAG representing the overall hollow heap. 
template <class T, class K>
struct hollow_heap_node {
    hollow_heap_item< T, K >* item;
    K key;
    // ep is the pointer to the second parent of the node.
    hollow_heap_node< T, K >* ep;
    hollow_heap_node< T, K >* next;
    hollow_heap_node< T, K >* child;
    int rank;
};

// This is the definition of the hollow_heap_item struct. The hollow_heap_items
// are the containers that store the values that are placed into the hollow 
// heap.
template <class T, class K>
struct hollow_heap_item {
    T item;
    hollow_heap_node< T, K>* node;
};

// This is the template class declaration for the hollow heap. The hollow heap
// has been implemented from the paper on hollow heaps from 2015.
template <class T, class K>
class hollow_heap {
    public:
        // Constructors and destructors.
        hollow_heap();
        ~hollow_heap();
        
        // Make heap simply returns a new instance of a hollow heap.
        hollow_heap< T, K > make_heap();
        // Here I have insert both for a simple item type, and an insert if 
        // someone passes in a hollow_heap_item in order to use decrease_key.
        void insert( T e, K k );
        void insert( hollow_heap_item< T, K > item, K k );
        void meld( hollow_heap_node< T, K >* h, hollow_heap_node< T, K >* g );
        void decrease_key( hollow_heap_item< T, K >* e, K k );
        T find_min( );
        void delete_min();
        void delete_item( hollow_heap_item< T, K >* item );

        // Quality of life heap functions.
        int get_size();
        bool is_empty();
        // TODO: Delete this function. Used only in development.
        void dump_state();
        
    private:
        // This is the reference to the root node of the pointer based DAG.
        hollow_heap_node< T, K >* heap;
        hollow_heap_node< T, K >* link( 
                hollow_heap_node< T, K >* v, 
                hollow_heap_node< T, K >* w );
        // Here I have make_node for both a simple item type, and one for if
        // someone passes in a hollow_heap_item in order to use decrease_key.
        hollow_heap_node< T, K >* make_node( T e, K k );
        hollow_heap_node< T, K >* make_node( 
                hollow_heap_item< T, K > item, K k );
        void add_child( 
                hollow_heap_node< T, K >* v, 
                hollow_heap_node< T, K >* w );
        int max_rank;
        void do_ranked_links( hollow_heap_node< T, K >* u );
        void do_unranked_links( );
        // size tracks the number of elements in the heap, and not the number 
        // of vertices in the DAG representing the hollow heap.
        int size;
        // This is the array of full roots, indexed by rank. This helps 
        // reconstruct the heap properly after a deletion of any type.
        std::vector< hollow_heap_node< T, K >* > A;
        
};

//TODO: Delete this function.
template < class T, class K >
void hollow_heap< T, K >::dump_state() {
    hollow_heap_node< T, K >* u = heap;
    hollow_heap_node< T, K >* v;
    std::cout << "Starting from the root" << std::endl;
    while( u ) {
        std::cout << "   Key: " << u->key << " Value: " << u->item->item << std::endl;
        std::cout << "   Iterating through children" << std::endl;
        v = heap->child;
        while( v ) {
            std::cout << "       Key: " << v->key << " Value: " << v->item->item << std::endl;
            if ( !v->next ) {
                v = v->child;
                continue;
            }
            v = v->next;
        }

        u = u->next;
    } 
}


// The constructor simply helps instantiate this object and sets default values 
// for size, max_rank and the heap root pointer.
template < class T, class K >
hollow_heap< T, K >::hollow_heap() {
    size = 0;
    max_rank = 0;
    heap = nullptr;
}


// Upon the destruction of the hollow heap object, will clean up memory.
template < class T, class K >
hollow_heap< T, K >::~hollow_heap() {
    while( heap ) delete_min();    
}


// Returns a reference to another hollow heap object. Only exists for the sake
// of keeping true to the spec of the original paper. 
template < class T, class K >
hollow_heap< T, K > hollow_heap< T, K >::make_heap() {
    return hollow_heap();
}


// Insert a new item into the heap. 
template < class T, class K >
void hollow_heap< T, K >::insert( T e, K k ) {
    meld( make_node( e, k ), heap );
    // Must update size here to stay consistent.
    size++;
}


// Insert a new hollow_heap_item into the heap. Useful for decrease_key.
template < class T, class K >
void hollow_heap< T, K >::insert( hollow_heap_item< T, K > item, K k ) {
    meld( make_node( item, k ), heap );
    size++;
}


// Join two heaps into one and keep the root in the currently called hollow
// heap object.
template < class T, class K >
void hollow_heap< T, K >::meld( 
        hollow_heap_node< T, K >* h,
        hollow_heap_node< T, K >* g ) {
    if ( h == nullptr ) { 
        heap = g;
        return;
    }
    if ( g == nullptr ) { 
        heap = h;
        return;
    }
    heap = link( h, g );
}


// Return the value of the smallest item in the heap, or NULL if the heap is
// empty.
template < class T, class K >
T hollow_heap< T, K >::find_min() {
    if ( heap == nullptr ) { 
        return NULL;
    }
    return heap->item->item;
}

// Delete the smallest element in the heap.
template < class T, class K >
void hollow_heap< T, K >::delete_min() {
    delete_item( heap->item );
}


// Getter for the size.
template < class T, class K >
int hollow_heap< T, K >::get_size() {
    return size;
}

template < class T, class K >
bool hollow_heap< T, K >::is_empty() {
    return size == 0;
}


// Do a simple link between the two hollow_heap_nodes provided.
template < class T, class K >
hollow_heap_node< T, K >* hollow_heap< T, K >::link( 
        hollow_heap_node< T, K >* v,
        hollow_heap_node< T, K >* w ) {
    if ( v->key >= w->key ) {
        add_child( v, w );
        return w;
    } else {
        add_child( w, v );
        return v;
    }
}


// Create a new node given an item and a key for it.
template < class T, class K >
hollow_heap_node< T, K >* hollow_heap< T, K >::make_node( T e, K k ){
    hollow_heap_node< T, K >* u = new hollow_heap_node< T, K >();
    u->item = new hollow_heap_item< T, K >();
    u->item->item = e;
    u->child = nullptr;
    u->next = nullptr;
    u->ep = nullptr;
    u->key = k;
    u->item->node = u;
    u->rank = 0;
    return u;
}


// Create a new node given a hollow_heap_item and a key for it.
template < class T, class K >
hollow_heap_node< T, K >* hollow_heap< T, K >::make_node( 
        hollow_heap_item< T, K > item, K k ) {
    hollow_heap_node< T, K >* u = new hollow_heap_node< T, K >();
    u->item = item;
    u->child = nullptr;
    u->next = nullptr;
    u->ep = nullptr;
    u->key = k;
    item->node = u;
    u->rank = 0;
    return u;
}


// Decrease the key value of a given item and rebalance the heap as needed.
template < class T, class K >
void hollow_heap< T, K >::decrease_key( hollow_heap_item< T, K >* e, K k ) {
    hollow_heap_node< T , K >* u = e->node;
    if ( u == heap ) {
        u->key = k;
        return;
    }
    hollow_heap_node< T, K >* v = make_node( e, k );
    u->item = nullptr;
    if ( u->rank > 2 ) v->rank = u->rank - 2;
    v->child = u;
    u->ep = v;
    heap = link( v, heap );
}


// Make a node a child of another node.
template < class T, class K >
void hollow_heap< T, K >::add_child( 
        hollow_heap_node< T, K >* v,
        hollow_heap_node< T, K >* w ) {
    v->next = w->child;
    w->child = v;
}


// Delete a provided item from the heap and rebalance it as needed. Clean up 
// the hollow nodes as necessary.
template < class T, class K >
void hollow_heap< T, K >::delete_item( hollow_heap_item< T, K >* item ){
    // Delete the node as necessary.
    item->node->item = nullptr;
    delete item;

    // Update the size of the heap.
    size--;

    // If the root was not affected, exit early. This will create a hollow 
    // node in the heap.
    if ( heap->item != nullptr ) return;

    // In the case the root becomes hollow, clean up all hollow nodes.
    // Setting max_rank to 0 will ignore all the full roots that stayed in the
    // A vector. 
    max_rank = 0;
    // Loop until the all the hollow roots are processed.
    while( heap != nullptr ) {
        // Get a pointer to the child of the current root being processed.
        hollow_heap_node< T, K >* w = heap->child;
        // Have a reference to the current hollow root being processed.
        hollow_heap_node< T, K >* v = heap;
        // This will iterate through the linked list of hollow roots. Will 
        // trigger the loop end condition. 
        heap = heap->next;

        // Loop through the siblings of the children of the current hollow root
        // being processed.
        while( w != nullptr ) {
            // Keep a copy of the pointer to the current sibling being 
            // processed.
            hollow_heap_node< T, K >* u = w;
            // Iterate through the siblings. 
            w = w->next;
            // If the current sibling is hollow.
            if ( u->item == nullptr ) {
                // But it has only a single parent.
                if ( u->ep == nullptr ) {
                    // Make the current sibling the root of the heap.
                    u->next = heap;
                    heap = u;
                // In the case when the current sibling has two parents.
                } else {
                    // If the second parent is the current hollow root being 
                    // processed, end this iteration.
                    if ( u->ep == v ) w = nullptr;
                    else u->next = nullptr;
                    u->ep = nullptr;
                }
            // If the current sibling is full, do a ranked link with other 
            // full roots.
            } else {
                do_ranked_links( u );
            }
        }
        // Destroy the current root being processed.
        delete v;
    }
    // Set a new root from the full roots remaining.
    do_unranked_links();
}


// Do a link between the current node being processed and all the remaining 
// full roots.
template < class T, class K >
void hollow_heap< T, K >::do_ranked_links( hollow_heap_node< T, K >* u ) {
    // Implementation detail - make A fit all the ranked full roots properly.
    while( u->rank >= A.size() ){
        A.push_back( nullptr );
    }
    // Update all ranks.
    while ( A[ u->rank ] != nullptr ) {
        u = link( u, A[ u->rank ] );
        A[ u->rank ] = nullptr;
        u->rank++;
    }
    A[ u->rank ] = u;

    if ( u->rank > max_rank ) max_rank = u->rank;
}


// Set a new root for the hollow heap after rebalancing.
template < class T, class K >
void hollow_heap< T, K >::do_unranked_links( ) {
    for ( int i = 0; i <= max_rank; i++ ) {
        if ( A[i] != nullptr ) {
            if ( heap == nullptr ) heap = A[i];
            else heap = link( heap, A[i] );
            A[i] = nullptr;
        }
    }
}
