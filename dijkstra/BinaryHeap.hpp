#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include <vector>
#include <algorithm>
#include <memory>
#include <exception>

template<class T>
class BinaryHeap{
	private:
        std::vector<std::shared_ptr<T>> keys;
        std::vector<int> heap;
        std::vector<int> heap_inv;
            
        void shiftUp(int i){
            int k = i;
            while( k > 0 && getKey(parent(k)) > getKey(k)){
                swap( parent(k) , k);
                k = parent(k);
            }
        };

        T getKey(int i){
            return *keys[heap[i]];
        };
        void shiftDown(int i){
            int k = i;
            while( numChildren(k) > 0 ){
                if( numChildren(k) == 1 && getKey(left(k)) < getKey(k) ){
                    swap( left(k) , k );
                    k = left(k);
                }else if( numChildren(k) == 2 && (getKey(left(k)) < getKey(k) || getKey(right(k)) < getKey(k)) ){
                    if( getKey(left(k)) < getKey(right(k)) ){
                        swap( left(k) , k );
                        k = left(k);
                    }else{
                        swap( right(k) , k );
                        k = right(k);
                    }
                }else{
                    break; //only one children and order is maintained
                }
            }
        }

        bool isRoot(int i){ return i == 0; };
        int parent(int i){ return (i-1)/2; };
        int right(int i){ return 2*i + 2; };
        int left(int i){ return 2*i + 1; };
        int numChildren(int i){ return std::max(std::min(static_cast<int>(heap.size() - left(i)), 2 ) , 0 ); };

        void swap(int from, int to){
            if( from == to ) return;

            heap_inv[heap[from]] = to;
            heap_inv[heap[to]] = from;
            std::iter_swap(begin(heap) + from, begin(heap) + to);
        };

    public:
        BinaryHeap(int maxSize){
            std::generate_n(std::back_inserter(keys), maxSize, [](){return nullptr;});
            std::generate_n(std::back_inserter(heap_inv), maxSize, [](){return -1;});
        };

        void push(int p, const T& value){
            if( p > keys.size() ) throw std::length_error("exceeded size");

            keys[p] = std::make_shared<T>(value);
            heap.push_back(p);
            heap_inv[p] = heap.size() - 1; 
            
            shiftUp(heap_inv[p]);
        }

        void update(int p, const T& value){
            if( *keys[p] < value ){
                keys[p] = std::make_shared<T>(value);
                shiftDown(heap_inv[p]);
            }else{
                keys[p] = std::make_shared<T>(value);
                shiftUp(heap_inv[p]);
            }
        };
        
        T pop(){
            if( empty() ) throw std::length_error("empty heap");
            
            T ret = getKey(0);
            swap( 0, heap.size() - 1);

            heap_inv[heap.back()] = -1;
            keys[heap.back()] = nullptr;
            heap.pop_back();
            
            shiftDown(0);

            return ret;
        };

        T peek(){
            if( empty() ) throw std::length_error("empty heap");

            return getKey(0);
        };

        bool empty(){ return heap.size() == 0; };
};

#endif