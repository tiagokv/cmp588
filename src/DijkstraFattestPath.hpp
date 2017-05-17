#ifndef DIJKSTRA_FATTEST_PATH_HPP
#define DIJKSTRA_FATTEST_PATH_HPP

#include <memory>
#include <iostream>

#include "ResidualGraph.hpp"

class DijkstraFattestPath
{
	size_t num_pops;
	size_t num_pushes;
	size_t num_updates;

	const ResidualGraph& graph;
	size_t source;
	size_t to;
	bool stop_to;

	std::vector<size_t> min_to;
	std::vector<std::shared_ptr<FlowEdge>> came_from;

	void run();
public:

	DijkstraFattestPath(const ResidualGraph& graph, size_t source): graph(graph), source(source), stop_to(false){
		run();
	};

	DijkstraFattestPath(const ResidualGraph& graph, size_t source, size_t to): graph(graph), 
																			   source(source), 
																			   to(to), 
																			   stop_to(true){
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

	std::vector<std::shared_ptr<FlowEdge>> get_fattest_path(){
		return get_fattest_path(this->to);
	};

	std::vector<std::shared_ptr<FlowEdge>> get_fattest_path(size_t to);

	size_t get_fattest_capacity(){
		return get_fattest_capacity(this->to);
	}

	size_t get_fattest_capacity(size_t to){
		return min_to[to];
	};
};

#endif