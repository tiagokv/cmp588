#include <exception>
#include <algorithm>

#include "BinaryHeap.hpp"

using namespace std;

void BinaryHeap::shiftUp(int i){
    int k = i;
    while( k > 0 && values[keys[parent(k)]] > values[keys[k]]){
        iter_swap(begin(keys) + parent(k), begin(keys) + k);
        k = parent(k);
        pos[i] = k;
    }
}

void BinaryHeap::shiftDown(int i){
    int k = i;
    while( k < keys.size() ){
        if( isRoot(k) ) break;
        else if( parent(keys.size()-1) == parent(k) ){
            iter_swap( begin(keys) + left(k) , begin(keys) + k );
            k = left(k);
            pos[i] = k;
        }else if( keys[left(k)] < keys[k] || keys[right(k)] < keys[k] ){
            if( keys[left(k)] < keys[right(k)] ){
                iter_swap( begin(keys) + left(k) , begin(keys) + k );
                k = left(k);
                pos[i] = k;
            }else{
                iter_swap( begin(keys) + right(k) , begin(keys) + k );
                k = right(k);
                pos[i] = k;
            }
        }
    }
}

void BinaryHeap::insert(int p, T& value){
    keys.push_back(value);
    pos[p] = keys.size() - 1;
    
    shiftUp(pos[p]);
}

void BinaryHeap::update(int p, T& value){

    if( keys[pos[p]] < value ){
        keys[pos[p]] = value;
        shiftDown(pos[p]);
    }else{
        keys[pos[p]] = value;
        shiftUp(pos[p]);
    }
}

T BinaryHeap::pop(){
    if( keys.size() == 0 ) throw length_error;
    
    iter_swap(begin(keys), end(keys) - 1);
    keys.pop_back();
    
    shiftDown(0);
}

T BinaryHeap::peek(){
    return *begin(keys);
}

        //void update(T value);
