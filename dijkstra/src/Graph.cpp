#include <memory>
#include <algorithm>

#include "Graph.hpp"

using namespace std;

void Graph::resize(int newSize){
	edges.resize(newSize);
	for (int i = 0; i < newSize; ++i) edges.push_back( vector<shared_ptr<Edge>>() );
}

void Graph::connect(unsigned int from, unsigned int to, unsigned int weight){
	shared_ptr<Edge> path = make_shared<Edge>(from, to, weight);
	edges[from].push_back(path);
}

std::vector<std::shared_ptr<Edge>> Graph::adjacents(unsigned int vertex) const{
	return edges[vertex];
}

bool Graph::are_connected(unsigned int a, unsigned int b) const{
	return find_if(begin(edges[a]), end(edges[a]), [=](const shared_ptr<Edge> edge){ return edge->to == b; }) != end(edges[a]);
}