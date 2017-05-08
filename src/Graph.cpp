#include <memory>
#include <algorithm>

#include "Graph.hpp"

using namespace std;

void Graph::reserve(size_t newSize){
	edges.reserve(newSize);
	for (size_t i = 0; i < newSize; ++i) edges.push_back( vector<Edge>() );
}

void Graph::connect(const size_t& from, const size_t& to, unsigned int weight){
	edges[from].emplace_back(from, to, weight);
	qtt_edges++;
}

const std::vector<Edge>& Graph::adjacents(const size_t& vertex) const{
	return edges[vertex];
}

bool Graph::are_connected(const size_t& a, const size_t& b) const{
	return find_if(begin(edges[a]), end(edges[a]), [=](const Edge& edge){ return edge.to == b; }) != end(edges[a]);
}