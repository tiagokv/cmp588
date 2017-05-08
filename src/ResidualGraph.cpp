#include "ResidualGraph.hpp"

using namespace std;

void ResidualGraph::connect(size_t from, size_t to, double max_capacity){
	nro_edges++;
	auto edge = make_shared<FlowEdge>(from, to, max_capacity);
	edges[from].push_back(edge);
	edges[to].push_back(edge);
}