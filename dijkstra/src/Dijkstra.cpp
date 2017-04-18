#include <vector>
#include <limits>
#include <memory>
#include <chrono>
#include <iostream>

#include "Dijkstra.hpp"
#include "NAryHeap.hpp"
#include "BinaryHeap.hpp"

using namespace std;

#include <boost/heap/d_ary_heap.hpp>
using namespace boost;

struct compare_cells_d_ary {
inline bool operator()
(const Vertex& c1 , const Vertex& c2) const {

    return c1.distance_to > c2.distance_to;        
}
};
typedef heap::d_ary_heap<Vertex, heap::arity<2>, heap::mutable_<true>, heap::compare<compare_cells_d_ary>> binary_heap;
typedef binary_heap::handle_type handle_t;

int shortest_path(const Graph& graph, size_t from, size_t to,
				  unsigned int& num_pops, unsigned int& num_pushes, unsigned int& num_updates, bool stopAtFinal){

	NAryHeap<Vertex> pq(2, graph.number_vertexes());
	// binary_heap pq;
	vector<Vertex> vertexes;
	vertexes.reserve(graph.number_vertexes());
	vector<bool> visited(graph.number_vertexes(), false);
	vector<handle_t> handles(graph.number_vertexes());

	//Initialization - All vertexes have infinity distance, except the source
	for(size_t i = 0; i < graph.number_vertexes(); i++){
		vertexes.push_back(Vertex(i, i == from ? 0 : numeric_limits<unsigned int>::max(), -1));
	}

	// handles[from] = pq.push(vertexes[from]);
	pq.push( from , vertexes[from] );

	chrono::microseconds total_push(0);
	chrono::microseconds total_pop(0);
	chrono::microseconds total_update(0);

	//For each vertex with the minimum distance to, relax
	while(!pq.empty()){

		chrono::system_clock::time_point t = chrono::system_clock::now();
		auto v = pq.pop();
		// auto v = pq.top();
		// pq.pop();
		total_pop += chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now()-t);
		visited[v.index] = true;
		
		if( stopAtFinal && v.index == to ) return vertexes[to].distance_to; 

		for(const auto& edge: graph.adjacents(v.index)){
			if( !visited[edge.to] ){
				if( vertexes[edge.to].distance_to == numeric_limits<unsigned int>::max() ){
					vertexes[edge.to].distance_to = v.distance_to + edge.weight;
					vertexes[edge.to].came_from = v.index;

					chrono::system_clock::time_point t = chrono::system_clock::now();
					pq.push( edge.to , vertexes[edge.to] );
					// handles[edge.to] = pq.push(vertexes[edge.to]);
					total_push += chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now()-t);
				}else if( v.distance_to + edge.weight < vertexes[edge.to].distance_to ){
					vertexes[edge.to].distance_to = v.distance_to + edge.weight;
					vertexes[edge.to].came_from = v.index;

					chrono::system_clock::time_point t = chrono::system_clock::now();
					pq.update( edge.to , vertexes[edge.to] );
					// pq.increase( handles[edge.to] , vertexes[edge.to] );
					total_update += chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now()-t);
				}
			}
		}
	}

	num_updates = pq.get_nro_update();
	num_pushes = pq.get_nro_pushes();
	num_pops = pq.get_nro_pops();

	cerr << "pushes : " << total_push.count() << endl;
	cerr << "updates : " << total_update.count() << endl;
	cerr << "pops : " << total_pop.count() << endl;

	//cerr << "took " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() << " whole dijkstra" << endl;
	return vertexes[to].distance_to;
}