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
	std::vector<double> min_to;
	std::vector<std::shared_ptr<FlowEdge>> came_from;

	void run();
public:
	DijkstraFattestPath(const ResidualGraph& graph, size_t source): graph(graph), source(source){
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

	std::vector<std::shared_ptr<FlowEdge>> get_fattest_path(size_t to);
	double get_fattest_capacity(size_t to){
		return min_to[to];
	};
};