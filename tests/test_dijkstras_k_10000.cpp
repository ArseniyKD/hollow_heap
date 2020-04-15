#include<vector>
#include<iostream>
#include<queue>
#include<cstdlib>
#include<chrono>
#include<limits>
#include<functional>
#include"../src/hollow_heap.h"

using namespace std;
using namespace std::chrono;

const int N = 10000;

vector<int> dijkstras_pq( vector< vector< int > > adjL ) {
    auto cmp = [](pair<int, int> lhs, pair<int,int> rhs ) {
        return lhs.first > rhs.first;
    };
    priority_queue< pair< int, int >, vector< pair< int, int > >, decltype(cmp) > q(cmp);
    vector< bool > vis( N, false );
    vector< int > dist( N, numeric_limits<int>::max() );
    vector< int > prev( N, -1 );

    dist[0] = 0;
    q.push( make_pair( 0, 0 ) );

    while( !q.empty() ) {
        pair< int, int > entry = q.top(); q.pop();
        int cur = entry.second;

        if ( vis[cur] ) continue;

        for( int i = 0; i < N; i++ ) {
            if ( vis[i] ) continue;
            if ( i == cur ) continue;
            if ( dist[cur] + adjL[cur][i] < dist[i] ) {
                dist[i] = dist[cur] + adjL[cur][i];
                prev[i] = cur;
                q.push( make_pair( dist[i], i ) );
            }
        }
        vis[cur] = true;
    }
    return prev;
}

vector< int > dijkstras_hh ( vector< vector< int > > adjL ) {
    hollow_heap< int, int > h = hollow_heap< int, int >();
    vector< bool > vis( N, false );
    vector< int > dist( N, numeric_limits<int>::max() );
    vector< int > prev( N, -1 );

    dist[0] = 0;
    h.insert( 0, 0 );

    int cnt = 0;
    while( !h.is_empty() ) {
        int cur = h.find_min(); h.delete_min();

        if ( vis[cur] ) continue;

        for( int i = 0; i < N; i++ ) {
            if ( vis[i] ) continue;
            if ( i == cur ) continue;
            if ( dist[cur] + adjL[cur][i] < dist[i] ) {
                dist[i] = dist[cur] + adjL[cur][i];
                prev[i] = cur;
                h.insert( i , dist[i] );
            }
        }
        vis[cur] = true;
    }
    return prev;
}


int main() {
    vector< vector< int > > adjL;

    for ( int i = 0; i < N; i++ ) {
        adjL.push_back( vector<int>() );
        for ( int j = 0; j < N; j++ ) {
            adjL[i].push_back( 1 + rand()%100000 );
        }
    }
    vector< int > res;
    auto start = high_resolution_clock::now();
    res = dijkstras_pq( adjL );
    auto end = high_resolution_clock::now();
    duration< double, milli > duration_pq = end - start;
    cout << "The time to run Dijkstra's on K_10000 with std::priority_queue: " 
        << duration_pq.count() << " ms" << endl;
    
    vector< int > res2;
    auto start2 = high_resolution_clock::now();
    res2 = dijkstras_hh( adjL );
    auto end2 = high_resolution_clock::now();
    duration< double, milli > duration_hh = end2 - start2;
    cout << "The time to run Dijkstra's on K_10000 with hollow heap: " 
        << duration_hh.count() << " ms" << endl;
    cout << "Hollow Heap runs " << duration_pq.count() / duration_hh.count()
        << " times faster than the Priority Queue version." << endl;
    
    long long cst1 = 0;
    long long cst2 = 0;
    for ( int i = 1; i < res.size(); i++ ) {
        cst1 += adjL[res[i]][i];
        cst2 += adjL[res2[i]][i];
    }
    cout << "Cost of tree 1: " << cst1 << " Cost of tree2: " << cst2 << endl;
    if ( cst1 == cst2 ) { 
        cout << "Both heaps are correct in identifying shortest paths" << endl;
    } else {
        cout << "One of the heaps is not correct in identifying the shortest paths" << endl;
    }



    return 0;

}
