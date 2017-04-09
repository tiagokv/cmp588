#include <iostream>

#include "NAryHeap.hpp"

using namespace std;

int main(int argv, char** argc){
	NAryHeap<char> nhp(3, argv-1);
	for(int i = 1; i < argv; i++){
		cout << "Pushing " << argc[i][0] << endl;
		nhp.push( i - 1, argc[i][0] );
	}

	cout << "Poping" << endl;
	while(!nhp.empty()) cout << nhp.pop() << endl;

	cout << "End" << endl;
}