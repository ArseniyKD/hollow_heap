#include<vector>
#include<cstddef>
#include<iostream>

template< class T, class K >
struct hollow_heap_item;

template <class T, class K>
struct hollow_heap_node {
    hollow_heap_item< T, K >* item;
    K key;
    hollow_heap_node< T, K >* ep;
    hollow_heap_node< T, K >* next;
    hollow_heap_node< T, K >* child;
    int rank;
};

template <class T, class K>
struct hollow_heap_item {
    T item;
    hollow_heap_node< T, K>* node;
};

template <class T, class K>
class hollow_heap {
    public:
        hollow_heap();
        ~hollow_heap();
        
        hollow_heap< T, K > make_heap();
        void insert( T e, K k );
        void meld( hollow_heap_node< T, K >* h, hollow_heap_node< T, K >* g );
        T find_min( );
        
        void delete_min();
        int get_size();
        bool is_empty();
        void dump_state();
        
    private:
        hollow_heap_node< T, K >* heap;
        hollow_heap_node< T, K >* link( 
                hollow_heap_node< T, K >* v, 
                hollow_heap_node< T, K >* w );
        hollow_heap_node< T, K >* make_node( T e, K k );
        void decrease_key( hollow_heap_item< T, K >* e, K k );
        void add_child( 
                hollow_heap_node< T, K >* v, 
                hollow_heap_node< T, K >* w );
        int max_rank;
        void delete_item( hollow_heap_item< T, K >* item );
        void do_ranked_links( hollow_heap_node< T, K >* u );
        void do_unranked_links( );
        int size;
        std::vector< hollow_heap_node< T, K >* > A;
        
};

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


template < class T, class K >
hollow_heap< T, K >::hollow_heap() {
    size = 0;
    max_rank = 0;
    heap = nullptr;
}

template < class T, class K >
hollow_heap< T, K >::~hollow_heap() {
    while( heap ) delete_min();    
    // Figure out what needs to be destroyed
}

template < class T, class K >
hollow_heap< T, K > hollow_heap< T, K >::make_heap() {
    return hollow_heap();
}

template < class T, class K >
void hollow_heap< T, K >::insert( T e, K k ) {
    meld( make_node( e, k ), heap );
    size++;
}

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

template < class T, class K >
T hollow_heap< T, K >::find_min() {
    if ( heap == nullptr ) { 
        //std::cout << "Shouldn't be here -------------------------" << std::endl;
        return NULL;
    }
    return heap->item->item;
}

template < class T, class K >
void hollow_heap< T, K >::delete_min() {
    delete_item( heap->item );
}

template < class T, class K >
int hollow_heap< T, K >::get_size() {
    return size;
}

template < class T, class K >
bool hollow_heap< T, K >::is_empty() {
    return size == 0;
}

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

template < class T, class K >
void hollow_heap< T, K >::decrease_key( hollow_heap_item< T, K >* e, K k ) {
    // Implement decrease_key from the pseudo code.
}

template < class T, class K >
void hollow_heap< T, K >::add_child( 
        hollow_heap_node< T, K >* v,
        hollow_heap_node< T, K >* w ) {
    v->next = w->child;
    w->child = v;
}

template < class T, class K >
void hollow_heap< T, K >::delete_item( hollow_heap_item< T, K >* item ){
    //delete item;
    item->node->item = nullptr;
    delete item;
    size--;
    if ( heap->item != nullptr ) return;
    max_rank = 0;
    while( heap != nullptr ) {
        hollow_heap_node< T, K >* w = heap->child;
        hollow_heap_node< T, K >* v = heap;
        heap = heap->next;
        while( w != nullptr ) {
            //std::cout << "Deleting" << std::endl;
            hollow_heap_node< T, K >* u = w;
            w = w->next;
            if ( u->item == nullptr ) {
                if ( u->ep == nullptr ) {
                    u->next = heap;
                    heap = u;
                } else {
                    if ( u->ep == v ) w = nullptr;
                    else u->next = nullptr;
                    u->ep = nullptr;
                }
            } else {
                do_ranked_links( u );
            }
        }
        delete v;
    }
    do_unranked_links();
}

template < class T, class K >
void hollow_heap< T, K >::do_ranked_links( hollow_heap_node< T, K >* u ) {
    while( u->rank >= A.size() ){
        A.push_back( nullptr );
    }
    while ( A[ u->rank ] != nullptr ) {
        u = link( u, A[ u->rank ] );
        //A[ u->rank ] = nullptr;
        A[ u->rank ] = nullptr;
        u->rank++;
    }
    A[ u->rank ] = u;

    if ( u->rank > max_rank ) max_rank = u->rank;
}

template < class T, class K >
void hollow_heap< T, K >::do_unranked_links( ) {
    for ( int i = 0; i <= max_rank; i++ ) {
        if ( A[i] != nullptr ) {
            //std::cout << "Going deep" << std::endl;
            if ( heap == nullptr ) heap = A[i];
            else heap = link( heap, A[i] );
            A[i] = nullptr;
        }
    }
}
