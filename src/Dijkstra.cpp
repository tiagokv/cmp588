#include <vector>
#include <limits>
#include <memory>
#include <chrono>
#include <iostream>

#include "Dijkstra.hpp"
#include "NAryHeap.hpp"
#include "BinaryHeap.hpp"

using namespace std;

void Dijkstra::run(){
	came_from.resize(graph.number_vertices(), numeric_limits<size_t>::max());
	distance_to.resize(graph.number_vertices(), numeric_limits<int>::max());
	vector<bool> visited(graph.number_vertices(), false);

	NAryHeap<int> pq(2, graph.number_vertices());

	distance_to[source] = 0;
	pq.push( source, distance_to[source] );

	while(!pq.empty()){
		auto v = pq.pop();
		visited[v]  = true;

		for(const auto& edge: graph.adjacents(v)){
			if( !visited[edge.to] ){
				if( distance_to[edge.to] == numeric_limits<int>::max() ){
					distance_to[edge.to] = distance_to[edge.from] + edge.weight;
					came_from[edge.to] = distance_to[edge.from];
					pq.push( edge.to , distance_to[edge.to] );
				}else if( distance_to[edge.from] + edge.weight < distance_to[edge.to] ){
					distance_to[edge.to] = distance_to[edge.from] + edge.weight;
					came_from[edge.to] = distance_to[edge.from];
					pq.update( edge.to , distance_to[edge.to] );
				}
			}
		}
	}

	num_updates = pq.get_nro_update();
	num_pushes = pq.get_nro_pushes();
	num_pops = pq.get_nro_pops();
}

	// binary_heap pq;

	//vector<handle_t> handles(graph.number_vertices());

	// handles[from] = pq.push(vertexes[from]);
	// handles[edge.to] = pq.push(vertexes[edge.to]);

	// pq.increase( handles[edge.to] , vertexes[edge.to] );
