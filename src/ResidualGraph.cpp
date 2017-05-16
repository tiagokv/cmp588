#include "ResidualGraph.hpp"

using namespace std;

void ResidualGraph::connect(const size_t& from,const size_t& to, size_t max_capacity){
	nro_edges++;
	auto edge = make_shared<FlowEdge>(from, to, max_capacity);
	edges[from].push_back(edge);
	edges[to].push_back(edge);

	max_capacities = max(max_capacities, max_capacity);
	total_capacities += max_capacity; 
}