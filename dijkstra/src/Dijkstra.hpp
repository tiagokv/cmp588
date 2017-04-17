#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_
#include <memory>

#include "Graph.hpp"

class Vertex
{
public:
	size_t index;
	unsigned int distance_to;
	size_t came_from;

	Vertex(size_t index, unsigned int distance_to, size_t came_from ):index(index), 
																	  distance_to(distance_to), 
																	  came_from(came_from){};
	virtual bool operator<(const Vertex& rhs){
		return this->distance_to < rhs.distance_to;
	}
};

int shortest_path(const Graph& graph, size_t from, size_t to, 
				  unsigned int& num_pops, unsigned int& num_pushes, unsigned int& num_updates, bool stopAtFinal = false);


#endif


