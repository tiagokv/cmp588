#ifndef FORDFULKERSONFATTESTPATH_HPP
#define FORDFULKERSONFATTESTPATH_HPP

#include <cmath>

#include "ResidualGraph.hpp"

class FordFulkersonFattestPath{
	ResidualGraph& graph;
	size_t source;
	size_t target;

	unsigned iterations;
	size_t max_flow;

	void run();

public:
	FordFulkersonFattestPath(ResidualGraph& rgraph, size_t source, size_t target):graph(rgraph), 
																				 source(source), 
																				 target(target),
																				 iterations(0),
																				 max_flow(0) {
		run();
	};

	size_t get_max_iterations(){
		return 2 * graph.number_edges() * std::log(graph.get_total_capacities()) + 1;
	}


	size_t get_max_flow(){
		return max_flow;
	};

	unsigned get_iterations(){ 
		return iterations; 
	};
};
#endif