#ifndef MATCHING_GRAPH_HPP
#define MATCHING_GRAPH_HPP

#include <vector>

class MatchingGraph
{
	std::vector<std::vector<size_t>> connections;
	size_t nro_edges;

public:
	MatchingGraph():nro_edges(0){
	}

	MatchingGraph(size_t qttVertices):nro_edges(0){
		connections.resize(qttVertices);
	}

	void connect(const size_t& from, const size_t& to){
		connections[from].push_back(to);
	}

	void reserve(const size_t& size){
		connections.resize(size);
	}

	const std::vector<size_t>& adjacents(const size_t& vert){
		return connections[from];
	}

	size_t number_vertices() const{
		return connections.size();
	}

	size_t number_edges() const{
		return nro_edges;
	};
};

#endif