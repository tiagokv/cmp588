#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_
#include <memory>
#include <iostream>

#include "Graph.hpp"

class Vertex
{
public:
	unsigned int index;
	unsigned int distance_to;
	unsigned int came_from;

	Vertex(unsigned int index, unsigned int distance_to, unsigned int came_from ):index(index), 
																				  distance_to(distance_to), 
																				  came_from(came_from){};
	virtual bool operator<(const Vertex& rhs){
		std::cout << "compared" << std::endl; 
		return this->distance_to < rhs.distance_to;
	}
};

int shortest_path(const Graph& graph, unsigned int from, unsigned int to, 
				  unsigned int& num_pops, unsigned int& num_pushes, unsigned int& num_updates, bool stopAtFinal = false);


#endif


