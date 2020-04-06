
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
};

template < class T, class K >
hollow_heap< T, K >::hollow_heap() {
    size = 0;
    max_rank = 0;
    heap = nullptr;
}

template < class T, class K >
hollow_heap< T, K >::~hollow_heap() {
    // Figure out what needs to be destroyed
}

template < class T, class K >
hollow_heap< T, K > hollow_heap< T, K >::make_heap() {
    return hollow_heap();
}

template < class T, class K >
void hollow_heap< T, K >::insert( T e, K k ) {
    // Implement the insertion from the pseudo-code.
}

template < class T, class K >
void hollow_heap< T, K >::meld( 
        hollow_heap_node< T, K >* h,
        hollow_heap_node< T, K >* g ) {
    // Implement the melding from the pseudo-code.
}

template < class T, class K >
T hollow_heap< T, K >::find_min() {
    if ( heap == nullptr ) return nullptr;
    return heap->item->item;
}

template < class T, class K >
void hollow_heap< T, K >::delete_min() {
    // Implement the delete_min from the pseudo-code.
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
    // Implement the link from the pseudo-code. Temporarily, returns NULL;
    return nullptr;
}

template < class T, class K >
hollow_heap_node< T, K >* hollow_heap< T, K >::make_node( T e, K k ){
    // Implement the make_node from the pseudo code. Temporarily returns NULL;
    return nullptr;
}

template < class T, class K >
void hollow_heap< T, K >::decrease_key( hollow_heap_item< T, K >* e, K k ) {
    // Implement decrease_key from the pseudo code.
}

template < class T, class K >
void hollow_heap< T, K >::add_child( 
        hollow_heap_node< T, K >* v,
        hollow_heap_node< T, K >* w ) {
    // Implement add_child from the pseudo code.
}

template < class T, class K >
void hollow_heap< T, K >::delete_item( hollow_heap_item< T, K >* item ){
    // Implement delete_item from the pseudo code.
}

template < class T, class K >
void hollow_heap< T, K >::do_ranked_links( hollow_heap_node< T, K >* u ) {
    // Implement do_ranked_links from the pseudo code.
}

template < class T, class K >
void hollow_heap< T, K >::do_unranked_links( ) {
    // Implement do_unranked_links from the pseudo code.
}
