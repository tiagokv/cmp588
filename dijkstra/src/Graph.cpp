#include <memory>
#include <algorithm>

#include "Graph.hpp"

using namespace std;

void Graph::reserve(size_t newSize){
	edges.reserve(newSize);
	for (size_t i = 0; i < newSize; ++i) edges.push_back( vector<shared_ptr<Edge>>() );
}

void Graph::connect(const size_t& from, const size_t& to, unsigned int weight){
	shared_ptr<Edge> path = make_shared<Edge>(from, to, weight);
	edges[from].push_back(path);
	qtt_edges++;
}

const std::vector<std::shared_ptr<Edge>>& Graph::adjacents(const size_t& vertex) const{
	return edges[vertex];
}

bool Graph::are_connected(const size_t& a, const size_t& b) const{
	return find_if(begin(edges[a]), end(edges[a]), [=](const shared_ptr<Edge> edge){ return edge->to == b; }) != end(edges[a]);
}