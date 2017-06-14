
#include <iostream>

#include "MaximumMatching.hpp"
#include "DimacsReader.hpp"

using namespace std;

int main(int argv, char** argc){
	DimacsReader di;
	auto graph = di.read_matching_graph(cin);

	MaximumMatching mm(graph);

	cout << "The maximum cardinality is " << mm.get_cardinality() << endl;

	return 0;
}