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
};

int shortest_path(const Graph& graph, unsigned int from, unsigned int to);