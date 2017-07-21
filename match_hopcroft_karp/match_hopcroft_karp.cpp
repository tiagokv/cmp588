
#include <iostream>

#include "MaximumMatching.hpp"
#include "DimacsReader.hpp"

using namespace std;

int main(int argv, char** argc){
	DimacsReader di;
	auto graph = di.read_matching_graph(cin);

	MaximumMatching mm(graph);
	auto cardinality = mm.get_cardinality();
	cerr << "The maximum cardinality is " << cardinality << endl;
	cout << cardinality << endl;
	
	return 0;
}