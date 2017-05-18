#include "FordFulkersonFattestPath.hpp"
#include "DijkstraFattestPath.hpp"

void FordFulkersonFattestPath::run(){
	auto max_iterations = get_max_iterations();
	while(iterations < max_iterations){ //even if something is not correct, do not take forever here
		DijkstraFattestPath fat(graph, source, target);
		auto fattest_path = fat.get_fattest_path();
		if( !fattest_path.empty() ){
			iterations++;
			auto capacity = fat.get_fattest_capacity();
			max_flow += capacity;

			size_t to = fattest_path[0]->get_to();
			for(auto edge: fattest_path){
				if( to == edge->get_to() ){
					edge->add_flow(capacity);
					to = edge->get_from();
				}else{
					edge->reduce_flow(capacity);
					to = edge->get_to();
				}
			}
		}else{
			break;
		}
	}
}