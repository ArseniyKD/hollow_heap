#include<iostream>
#include "hollow_heap.h"
using namespace std;

int main() {
    hollow_heap<int, int> h = hollow_heap<int, int>();
    cout << "Initialization test passed" << endl;

    h.insert( 3, 3 );
    cout << h.find_min() << " " << h.get_size() << endl;

    h.insert( 2, 2 );
    cout << h.find_min() << " " << h.get_size() << endl;
    h.insert( 1, 1 );
    cout << h.find_min() << " " << h.get_size() << endl;
    h.dump_state();

    h.delete_min();
    //if ( h.find_min() == NULL ) cout << "UHHH" << endl;
    cout << h.find_min() << " " << h.get_size() << endl;
    //h.dump_state();
    cout << h.find_min() << " " << h.get_size() << endl;
    cout << "Survived that." << endl;


    return 0;
}
