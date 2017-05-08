#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_
#include <memory>
#include <iostream>

#include "Graph.hpp"

class Dijkstra
{
	size_t num_pops;
	size_t num_pushes;
	size_t num_updates;

	const Graph& graph;
	size_t source;
	std::vector<int> distance_to;
	std::vector<size_t> came_from;

	void run();
public:
	Dijkstra(const Graph& graph, size_t source): graph(graph), source(source){
		run();
	};
	
	size_t get_pops(){
		return num_pops;
	};

	size_t get_pushes(){
		return num_pushes;
	};

	size_t get_updates(){
		return num_updates;
	};

	int get_shortest_distance(size_t to){
		return distance_to[to];
	}
};

#endif


