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
	min_to.resize(graph.number_vertices(), 0.0);
	vector<bool> visited(graph.number_vertices(), false);

	NAryHeap<double, greater<double>> pq(2, graph.number_vertices());

	min_to[source] = numeric_limits<double>::max();
	pq.push( source, min_to[source] );

	while(!pq.empty()){
		auto v = pq.pop();
		num_pops++;
		visited[v]  = true;

		for(const auto& edge: graph.adjacents(v)){
			if( !visited[edge->get_to()] ){
				if(min_to[edge->get_to()] == 0.0){
					min_to[edge->get_to()] = min(min_to[v], edge->get_capacity(v));
					came_from[edge->get_to()] = edge;
					num_pushes++;
					pq.push( edge->get_to() , min_to[edge->get_to()] );
				}else if( min_to[edge->get_to()] < min(min_to[v], edge->get_capacity(v)) ){
					min_to[edge->get_to()] = min(min_to[v], edge->get_capacity(v));
					came_from[edge->get_to()] = edge;
					num_updates++;
					pq.update( edge->get_to() , min_to[edge->get_to()] );
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
		f = came_from[f]->get_from();
	}
	return v;
}