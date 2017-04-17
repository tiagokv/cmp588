#ifndef NARYHEAP_HPP
#define NARYHEAP_HPP

#include <vector>
#include <algorithm>
#include <memory>
#include <exception>
#include <cassert>

template<class T>
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
            
        void shiftUp(size_t i){
            auto k = i;
            while( k > 0 && getKey(parent(k)) > getKey(k)){
                swap( parent(k) , k);
                k = parent(k);
            }
        };

        T getKey(size_t i){
            return *keys[heap[i]];
        };
        void shiftDown(size_t i){
            auto k = i;
            while( numChildren(k) > 0 ){
                if( numChildren(k) == 1 ){
                    if( getKey(getChild(k,1)) < getKey(k) ){
                        swap( getChild(k,1) , k );
                        k = getChild(k,1);
                    }else{
                        break;
                    }
                }else if( numChildren(k) >= 2 ){
                    auto min_child = getChild(k,1);
                    for(int child = 2; child <= numChildren(k); child++){
                        if( getKey(min_child) > getKey(getChild(k, child)))
                            min_child = getChild(k, child);
                    }

                    if( getKey(min_child) < getKey(k) ){
                        swap( min_child , k );
                        k = min_child;
                    }else{
                        break;
                    }
                }
            }
        }

        bool isRoot(size_t i){ return i == 0; };
        size_t parent(size_t i){ return (i-1)/heap_size; };
        size_t getChild(size_t i, size_t p){
            assert(p > 0 && p <= heap_size);
            return heap_size*i + p;
        };

        size_t numChildren(size_t i){ return static_cast<size_t>(std::max(std::min(static_cast<int>(heap.size() - getChild(i,1)), static_cast<int>(heap_size) ) , 
                                                         0 )); };

        void swap(size_t from, size_t to){
            if( from == to ) return;

            heap_inv[heap[from]] = to;
            heap_inv[heap[to]] = from;
            std::iter_swap(begin(heap) + from, begin(heap) + to);

            nro_swaps++;
        };

    public:
        NAryHeap(size_t heapSize, size_t maxSize):nro_swaps(0),nro_pushs(0), nro_updates(0), nro_pops(0), heap_size(heapSize){
            keys.reserve(maxSize);
            heap_inv.reserve(maxSize);
            heap.reserve(maxSize);

            std::generate_n(std::back_inserter(keys), maxSize, [](){return nullptr;});
            std::generate_n(std::back_inserter(heap_inv), maxSize, [](){return -1;});
        };

        NAryHeap(size_t maxSize):nro_swaps(0),nro_pushs(0), nro_updates(0), nro_pops(0), heap_size(2){
            keys.reserve(maxSize);
            heap_inv.reserve(maxSize);
            heap.reserve(maxSize);

            std::generate_n(std::back_inserter(keys), maxSize, [](){return nullptr;});
            std::generate_n(std::back_inserter(heap_inv), maxSize, [](){return -1;});
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
        }

        void push(size_t p, const T& value){
            if( p > keys.size() ) throw std::length_error("exceeded size");

            keys[p] = std::make_shared<T>(value);
            heap.push_back(p);
            heap_inv[p] = heap.size() - 1; 
            
            shiftUp(heap_inv[p]);

            nro_pushs++;
        }

        void update(size_t p, const T& value){
            if( *keys[p] < value ){
                keys[p] = std::make_shared<T>(value);
                shiftDown(heap_inv[p]);
            }else{
                keys[p] = std::make_shared<T>(value);
                shiftUp(heap_inv[p]);
            }

            nro_updates++;
        };
        
        T pop(){
            if( empty() ) throw std::length_error("empty heap");
            
            auto ret = getKey(0);
            swap( 0, heap.size() - 1);
            nro_swaps--; // compensate the swap ++

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
        }

        unsigned long get_nro_swaps() const{
            return nro_swaps;
        }

        unsigned long get_nro_pushes() const{
            return nro_pushs;
        }

        unsigned long get_nro_update() const{
            return nro_updates;
        }

        unsigned long get_nro_pops() const{
            return nro_pops;
        }
};

#endif