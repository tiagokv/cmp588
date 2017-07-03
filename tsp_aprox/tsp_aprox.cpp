#include <iostream>

using namespace std;

#include "tsp_aprox_christofides.hpp"

int main(){

	auto graph = read_tsp(cin);

	cout << "Graph contains " << num_vertices(graph) << " vertices and " << num_edges(graph) << endl;

	cout << "The minimum circuit costs " << tsp_aprox_christofides<minweight_perfect_matching, true>(graph) << endl;
	// cout << "The minimum circuit costs " << tsp_aprox_christofides<greedy_perfect_matching, true>(graph) << endl;

	return 0;
}