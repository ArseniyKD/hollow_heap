#include<iostream>
#include<vector>
#include<queue>
#include "../src/hollow_heap.h"

using namespace std;

bool test_decrease_key() {
    cout << "\tStarting the decrease key unit test" << endl;
    hollow_heap< int, int > heap = hollow_heap< int, int >();
    // Create a vector of hh items in order to use decrease key properly
    vector< hollow_heap_item< int, int >* > elements( 5, nullptr );
   
    // Allocate all the elements on the heap, as otherwise delete operations 
    // will fail because deleting pointers off the stack is problematic. 
    for( int i = 0; i < 5; i++ ) elements[i] = new hollow_heap_item<int, int>();
    // Assign values to the hh items
    for( int i = 0; i < 5; i++ ) elements[i]->item = i+1;
    // Insert the items into the heap
    for( int i = 0; i < 5; i++ ) heap.insert( elements[i], i+1 );
    if ( heap.find_min() != 1 ) {
        cout << "\t\tFailed construction of the heap with out of heap item construction" << endl;
        return false;
    }
    cout << "\t\tSuccesfully constructed the heap with out of heap item construction" << endl;
    // Delete the minimum.
    heap.delete_min();

    // Decrease the key of the item ( 4, 4 ) to ( 4, 1 )
    heap.decrease_key( elements[3], 1 );
    if ( heap.find_min() != 4 ) {
        cout << "\t\tDecrease Key failed." << endl;
        return false;
    }
    cout << "\t\tDecrease Key succeeded." << endl;
    
    // Delete the minimal value.
    heap.delete_min();

    if ( heap.find_min() != 2 ) {
        cout << "\t\tDecrease key broke the heap structure after first delete_min." << endl;
        return false;
    }
    
    heap.delete_min();

    if ( heap.find_min() != 3 ) {
        cout << "\t\tDecrease key broke the heap structure after second delete_min." << endl;
        return false;
    }

    heap.delete_min();

    if ( heap.find_min() != 5 ) {
        cout << "\t\tDecrease key broke the heap structure after third delete_min." << endl;
        return false;
    }

    return true;
}

bool test_arbitrary_delete() {
    cout << "\tStarting the decrease key unit test" << endl;
    hollow_heap< int, int > heap = hollow_heap< int, int >();
    // Create a vector of hh items in order to use decrease key properly
    vector< hollow_heap_item< int, int >* > elements( 5, nullptr );
   
    // Allocate all the elements on the heap, as otherwise delete operations 
    // will fail because deleting pointers off the stack is problematic. 
    for( int i = 0; i < 5; i++ ) elements[i] = new hollow_heap_item<int, int>();
    // Assign values to the hh items
    for( int i = 0; i < 5; i++ ) elements[i]->item = i+1;
    // Insert the items into the heap
    for( int i = 0; i < 5; i++ ) heap.insert( elements[i], i+1 );
    if ( heap.find_min() != 1 ) {
        cout << "\t\tFailed construction of the heap with out of heap item construction" << endl;
        return false;
    }
    cout << "\t\tSuccesfully constructed the heap with out of heap item construction" << endl;
    // Delete the minimum.
    heap.delete_min();

    heap.delete_item( elements[3] );
    if ( heap.find_min() != 2 ) {
        cout << "\t\tArbitrary item deletion broke the heap structure." << endl;
        return false;
    }
    cout << "\t\tArbitrary Item Deletion succeeded!" << endl;
    heap.delete_min();

    if ( heap.find_min() != 3 ) {
        cout << "\t\tArbitrary item deletion broke the heap structure." << endl;
        return false;
    }
    heap.delete_min();

    if ( heap.find_min() != 5 ) {
        cout << "\t\tArbitrary item deletion broke the heap structure." << endl;
        return false;
    }

    return true;
}

int main() {
    cout << "These unit tests only test decrease_key and delete_item from the "
        << "user perspective.\nThese unit tests also implicitly test insert() "
        << "with an item being provided.\nThe purpose of these tests is to "
        << "test the functions that aren't tested in the performance tests."
        << endl;
    if ( test_decrease_key() ) {
        cout << "\tDecrease Key Unit Test Passed!" << endl;
    } else {
        cout << "\tDecrease Key Unit Test Failed!" << endl;
    }
    if ( test_arbitrary_delete() ) {
        cout << "\tArbitrary Delete Unit Test Passed!" << endl;
    } else {
        cout << "\tArbitrary Delete Unit Test Failed!" << endl;
    }

    return 0;
}
