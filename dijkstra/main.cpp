#include <iostream>

#include "BinaryHeap.hpp"

using namespace std;

int main(int argv, char** argc){

	BinaryHeap<char> bh(argv - 1);

	for(int i = 1; i < argv; i++){
		cout << "pushing " << *argc[i] << endl;
		bh.push( i - 1, *argc[i]);
	}

	bh.update(2, 'z');

	while( !bh.empty() ) cout << bh.pop() << endl;

	return 0;
}