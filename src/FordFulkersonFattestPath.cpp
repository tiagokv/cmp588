#include <cmath>

#include "FordFulkersonFattestPath.hpp"
#include "DijkstraFattestPath.hpp"

void FordFulkersonFattestPath::run(){
	auto max_iterations = std::log(graph.get_total_capacities()) + 1;
	while(true){ //even if something is not correct, do not take forever here
		DijkstraFattestPath fat(graph, source, target);
		auto fattest_path = fat.get_fattest_path();
		if( !fattest_path.empty() ){
			iterations++;
			auto capacity = fat.get_fattest_capacity();
			max_flow += capacity;
			for(auto edge: fattest_path){
				edge->add_flow(capacity);
			}
		}else{
			break;
		}
	}
}