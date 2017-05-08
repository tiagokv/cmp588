#ifndef NARYHEAP_HPP
#define NARYHEAP_HPP

#include <vector>
#include <algorithm>
#include <memory>
#include <exception>
#include <cassert>
#include <iostream>
#include <functional>

template<class T, class Compare = std::less<T>>
class NAryHeap{
	private:
        std::vector<std::shared_ptr<T>> keys;
        std::vector<size_t> heap;
        std::vector<size_t> heap_inv;

        unsigned long nro_swaps;
        unsigned long nro_pushs;
        unsigned long nro_updates;
        unsigned long nro_pops;
        int heap_size;

        Compare compare;

        void shiftUp(const size_t& i){
            auto k = i;
            while( k > 0 && compare(getKey(k), getKey(parent(k)))){
                swap( parent(k) , k);
                k = parent(k);
            }
        };

        T getKey(const size_t& i){
            return *keys[heap[i]];
        };

        void shiftDown(const size_t& i){
            auto k = i;
            while( numChildren(k) > 0 ){
                if( numChildren(k) == 1 ){
                    if( compare(getKey(getChild(k,1)), getKey(k)) ){
                        swap( getChild(k,1) , k );
                        k = getChild(k,1);
                    }else{
                        break;
                    }
                }else if( numChildren(k) >= 2 ){
                    auto min_child = getChild(k,1);
                    for(int child = 2; child <= numChildren(k); child++){
                        if( compare(getKey(getChild(k, child)), getKey(min_child)))
                            min_child = getChild(k, child);
                    }

                    if( compare(getKey(min_child), getKey(k)) ){
                        swap( min_child , k );
                        k = min_child;
                    }else{
                        break;
                    }
                }
            }
        };

        bool isRoot(const size_t& i){ return i == 0; };
        size_t parent(const size_t& i){ return (i-1)/heap_size; };
        size_t getChild(const size_t& i,const size_t& p){
            //assert(p > 0 && p <= heap_size);
            return heap_size*i + p;
        };

        int numChildren(const size_t& i){ 
            return std::max(std::min(static_cast<int>(heap.size() - getChild(i,1)), heap_size ), 0); 
        };

        void swap(const size_t& from, const size_t& to){
            if( from == to ) return;

            heap_inv[heap[from]] = to;
            heap_inv[heap[to]] = from;

            auto aux = heap[to];
            heap[to] = heap[from];
            heap[from] = aux;

            nro_swaps++;
        };

    public:
        NAryHeap(size_t heapSize, size_t maxSize):nro_swaps(0),nro_pushs(0), nro_updates(0), nro_pops(0), heap_size(heapSize){
            keys.resize(maxSize, nullptr);
            heap_inv.resize(maxSize, -1);
            heap.reserve(maxSize);
        };

        NAryHeap(size_t maxSize):nro_swaps(0),nro_pushs(0), nro_updates(0), nro_pops(0), heap_size(2){
            keys.resize(maxSize, nullptr);
            heap_inv.resize(maxSize, -1);
            heap.reserve(maxSize);
        };

        NAryHeap(const NAryHeap& bh){
            this->keys.reserve( bh.keys.capacity() );
            this->heap.reserve( bh.heap.capacity() );
            this->heap_inv.reserve( bh.heap_inv.capacity() );

            this->keys = bh.keys;
            this->heap = bh.heap;
            this->heap_inv = bh.heap_inv;
            this->nro_swaps = bh.nro_swaps;
            this->nro_pushs = bh.nro_pushs;
            this->nro_updates = bh.nro_updates;
            this->nro_pops = bh.nro_pops;
            this->heap_size = bh.heap_size;
        };

        void reset_swaps(){
            nro_swaps = 0;
        };

        void push(const size_t& p, T value){
            if( p > keys.size() ) throw std::length_error("exceeded size");

            keys[p] = std::make_shared<T>(value);
            heap.push_back(p);
            heap_inv[p] = heap.size() - 1; 
            
            shiftUp(heap_inv[p]);

            nro_pushs++;
        };

        void update(const size_t& p, T value){
            auto k = std::make_shared<T>(value);
            if(compare(*k, *keys[p])){
                keys[p] = k;
                shiftUp(heap_inv[p]);                
            }else{
                keys[p] = k;
                shiftDown(heap_inv[p]);
            }

            nro_updates++;
        };
        
        size_t pop(){
            if( empty() ) throw std::length_error("empty heap");
            
            auto ret = heap[0];
            swap( 0, heap.size() - 1);
            if(nro_swaps > 0) nro_swaps--; // compensate the swap ++

            heap_inv[heap.back()] = -1;
            keys[heap.back()] = nullptr;
            heap.pop_back();
            
            shiftDown(0);

            nro_pops++;

            return ret;
        };

        T peek(){
            if( empty() ) throw std::length_error("empty heap");

            return getKey(0);
        };

        bool empty(){ return heap.size() == 0; };

        void print_heap(){
            std::cout << "heap: ";
            for(const auto& index: heap){
                std::cout << *keys[index] << " ";
            }
            std::cout << std::endl;
        };

        unsigned long get_nro_swaps() const{
            return nro_swaps;
        };

        unsigned long get_nro_pushes() const{
            return nro_pushs;
        };

        unsigned long get_nro_update() const{
            return nro_updates;
        };

        unsigned long get_nro_pops() const{
            return nro_pops;
        };
};

#endif