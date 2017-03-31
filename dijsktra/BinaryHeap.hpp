#include <vector>

template<class T>
class BinaryHeap{
	private:
        std::vector<int> keys;
        std::vector<int> pos;
        std::vector<T> values;
            
        void shiftUp(int i);
        void shiftDown(int i);
        bool isRoot(int i){ return i == 0; };
        int parent(int i){ return (p-1)/2; };
        int right(int i){ return 2*p + 1; };
        int left(int i){ return 2*p + 2; };

    public:
        BinaryHeap();

        void insert(int p, T& value);
        void update(int p, T& value);
        
        T pop();
        T peek();
};
