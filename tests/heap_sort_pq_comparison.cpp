#include<iostream>
#include "../src/hollow_heap.h"
#include<queue>
#include<chrono>
#include <vector>
#include<algorithm>
using namespace std;
using namespace std::chrono;

void sort_pq( vector<int> &v, vector<int> &vv ) { 
    priority_queue< int, vector< int >, greater< int > > pq;
    for ( auto it : v ) pq.push( it ) ;
    while( !pq.empty() ) {
        vv.push_back( pq.top() );
        pq.pop();
    }
}

void sort_hh( vector<int> &v, vector< int > &vv ) {
    hollow_heap<int, int> h = hollow_heap<int, int>();
    for( auto it : v ) h.insert( it, it );
    while( !h.is_empty() ) {
        vv.push_back( h.find_min() );
        h.delete_min();
    }
}

void sort_mh( vector< int > &v, vector<int> &vv ) {
    make_heap( v.begin(), v.end() );
    sort_heap( v.begin(), v.end() );
    
    for( auto it : v ) vv.push_back( it );
}

bool compare_v_equality( vector< int > &v, vector< int > &vv ) {
    if ( v.size() != vv.size() ) return false;
    for( int i = 0; i < v.size(); i++ ) {
        if ( v[i] != vv[i] ) return false;
    }
    return true;
}

int main() {
    cout << "Naive heap sort comparison between std::priority_queue and hollow"
        << " heaps." << endl << "Additionally, a quick comparison against " 
        << "std::make_heap + std::sort_heap, and finally a test against "
        << "std::sort" << endl << endl;
    cout << "The test case runs on an input vector of size 10 million of " 
         << "integers sorted in this order: 10,000,000 ... 1" << endl << endl;

    vector< int > to_sort;
    for ( int i = 10000000; i > 0; i-- ) {
        to_sort.push_back( i );
    }
    vector< int > correctness_verification;
    for ( int i = 1; i <= 10000000; i++ ) {
        correctness_verification.push_back( i );
    }
    cout << "\tStarting time test against std::priority_queue:" << endl;
    
    vector< int > res;

    auto start = high_resolution_clock::now();
    sort_pq( to_sort, res );
    auto end = high_resolution_clock::now();

    duration<double, milli>  duration_pq = end - start;

    cout << "\t\tThe time to sort using a std::priority_queue was: " 
        << duration_pq.count() << " ms" << endl;
    if ( compare_v_equality( res, correctness_verification ) ) {
        cout << "\t\tTest resulted in a correctly sorted vector." << endl;
    } else {
        cout << "\t\tTest resulted in an incorrectly sorted vector." << endl;
    }
    cout << endl;

    cout << "\tStarting time test against hollow heap:" << endl;
    vector < int > res2;

    auto start2 = high_resolution_clock::now();
    sort_hh( to_sort, res2 );
    auto end2 = high_resolution_clock::now();

    duration<double, milli> duration_hh = end2 - start2;

    cout << "\t\tThe time to sort using a hollow heap was: " 
        << duration_hh.count() << " ms" << endl;
    if ( compare_v_equality( res2, correctness_verification ) ) {
        cout << "\t\tTest resulted in a correctly sorted vector." << endl;
    } else {
        cout << "\t\tTest resulted in an incorrectly sorted vector." << endl;
    }
    cout << endl;
    
    cout << "\tStarting time test against std::make_heap + std::sort_heap:" 
        << endl;
    vector < int > res3;

    auto start3 = high_resolution_clock::now();
    sort_mh( to_sort, res3 );
    auto end3 = high_resolution_clock::now();

    duration<double, milli> duration_mh = end3 - start3;

    cout << "\t\tThe time to sort using std::make_heap + std::sort_heap was: " 
        << duration_mh.count() << " ms" << endl;
    if ( compare_v_equality( res3, correctness_verification ) ) {
        cout << "\t\tTest resulted in a correctly sorted vector." << endl;
    } else {
        cout << "\t\tTest resulted in an incorrectly sorted vector." << endl;
    }
    cout << endl;
    
    // Have to recreate because make_heap and sort_heap destroyes the 
    // underlying data structure.
    to_sort.clear();
    for ( int i = 10000000; i > 0; i-- ) {
        to_sort.push_back( i );
    }

    cout << "\tStarting time test against std::sort:" << endl;
    vector < int > res4;

    auto start4 = high_resolution_clock::now();
    sort( to_sort.begin(), to_sort.end() );
    res4 = to_sort;
    //for ( auto it : to_sort ) res4.push_back( it );
    auto end4 = high_resolution_clock::now();

    duration<double, milli> duration_sort = end4 - start4;

    cout << "\t\tThe time to sort using std::sort was: " 
        << duration_sort.count() << " ms" << endl;
    if ( compare_v_equality( res4, correctness_verification ) ) {
        cout << "\t\tTest resulted in a correctly sorted vector." << endl;
    } else {
        cout << "\t\tTest resulted in an incorrectly sorted vector." << endl;
    }
    cout << endl;


    double ratio = duration_pq.count() / duration_hh.count();
    double ratio2 = duration_mh.count() / duration_hh.count();
    double ratio3 = duration_hh.count() / duration_sort.count();
    cout << "Hollow heap is " << ratio << " times faster than a priority_queue"
        << " in this test scenario." << endl;
    cout << "Hollow heap is " << ratio2 << " times faster than make_heap + " 
        << "sort_heap in this test scenario." << endl;
    cout << "std::sort is " << ratio3 << " times faster than hollow heap"
        << " in this test scenario." << endl;

    return 0;
}
