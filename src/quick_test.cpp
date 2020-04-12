#include<iostream>
#include "hollow_heap.h"
using namespace std;

int main() {
    hollow_heap<int, int> h = hollow_heap<int, int>();
    cout << "Initialization test passed" << endl;
    /*
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
    cout << "First dump" << endl;
    h.dump_state();
    h.delete_min();
    cout << "second dump" << endl;
    h.dump_state();
    h.insert( 3, 3 );
    h.insert( 3, 3 );
    cout << "Double insert of min value done" << endl;
    cout << h.find_min() << " " << h.get_size() << endl;
    cout << "Survived that." << endl;
   h.dump_state();
    h.delete_min();
    cout << "\n\n\n";
   h.dump_state();
    cout << h.find_min() << " " << h.get_size() << endl;
   
   */
    h.insert( 3, 3 );
    h.insert( 4, 4 );
    h.insert( 6, 6 );
    h.dump_state();

    h.delete_min();
    cout << endl << endl;
    h.dump_state();

    h.insert( 5,5 );

    cout << endl << endl;

    h.dump_state();

    h.delete_min();

    cout << endl;
    h.dump_state();

    cout << endl;
    h.delete_min();
    h.dump_state();
    cout << endl;
    cout << "HELLO :)" <<endl;
    h.delete_min();
    h.dump_state();
  

    
   


    return 0;
}
