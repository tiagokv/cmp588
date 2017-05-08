

#include "FordFulkFattestPath.hpp"


void FordFulkersonFattestPath::run(){

}

class 
{
	const ResidualGraph& graph;
	size_t source;
	size_t target;

	void run();
public:
	FordFulkersonFattestPath(const ResidualGraph& graph, size_t source, size_t target):graph(graph), source(source), target(target){};

	double get_max_flow();
};
#endif