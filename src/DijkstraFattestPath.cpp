#include <vector>
#include <limits>
#include <memory>
#include <chrono>
#include <iostream>

#include "DijkstraFattestPath.hpp"
#include "NAryHeap.hpp"

using namespace std;

void DijkstraFattestPath::run(){
	came_from.resize(graph.number_vertices(), nullptr);
	min_to.resize(graph.number_vertices(), 0);
	vector<bool> visited(graph.number_vertices(), false);

	NAryHeap<size_t, greater<size_t>> pq(2, graph.number_vertices());

	// for(size_t i = 0; i < graph.number_vertices(); i++){
	// 	if( i != source ) pq.push( i , min_to[i] );
	// }

	min_to[source] = numeric_limits<size_t>::max();
	pq.push( source, min_to[source] );

	while(!pq.empty()){
		auto v = pq.pop();
		if( stop_to && v == to ) break;
		visited[v]  = true;

		for(const auto& edge: graph.adjacents(v)){
			size_t from, to;

			if( v == edge->get_from() ){
				from = v;
				to = edge->get_to();
			}else{
				from = v;
				to = edge->get_from();
			}
			
			if( !visited[to] ){
				if(min_to[to] == 0 && min(min_to[v], edge->get_capacity(v)) > 0){
					min_to[to] = min(min_to[v], edge->get_capacity(v));
					came_from[to] = edge;
					pq.push( to , min_to[to] );
				}else if( min_to[to] < min(min_to[from], edge->get_capacity(v)) ){
					min_to[to] = min(min_to[from], edge->get_capacity(v));
					came_from[to] = edge;
					pq.update( to , min_to[to] );
				}
			}
		}
	}

	num_updates = pq.get_nro_update();
	num_pushes = pq.get_nro_pushes();
	num_pops = pq.get_nro_pops();
}

vector<shared_ptr<FlowEdge>> DijkstraFattestPath::get_fattest_path(size_t to){
	vector<shared_ptr<FlowEdge>> v;
	auto f = to;
	while(came_from[f] != nullptr){
		v.push_back(came_from[f]);

		//if backward edge was added
		if( came_from[f]->get_from() != f ){
			f = came_from[f]->get_from();
		}else{
			f = came_from[f]->get_to();
		}
	}
	return v;
}