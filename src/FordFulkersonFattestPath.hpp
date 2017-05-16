#ifndef FORDFULKERSONFATTESTPATH_HPP
#define FORDFULKERSONFATTESTPATH_HPP

#include "ResidualGraph.hpp"

class FordFulkersonFattestPath{
	ResidualGraph& graph;
	size_t source;
	size_t target;

	unsigned iterations;
	double max_flow;

	void run();

public:
	FordFulkersonFattestPath(ResidualGraph& rgraph, size_t source, size_t target):graph(rgraph), 
																				 source(source), 
																				 target(target),
																				 iterations(0),
																				 max_flow(0.0) {
		run();
	};

	double get_max_flow(){
		return max_flow;
	};

	unsigned get_iterations(){ 
		return iterations; 
	};
	// constante C = sum(Capacities) ou (n-1)*max(Capacities)
};
#endif