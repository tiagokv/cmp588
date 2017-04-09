#include <vector>
#include <limits>
#include <memory>

#include "Dijkstra.hpp"
#include "NAryHeap.hpp"

using namespace std;

int shortest_path(const Graph& graph, unsigned int from, unsigned int to,
				  unsigned int& num_pops, unsigned int& num_pushes, unsigned int& num_updates){

	NAryHeap<shared_ptr<Vertex>> pq(2, graph.number_vertexes());
	vector<shared_ptr<Vertex>> vertexes;
	vector<bool> visited(graph.number_vertexes(), false);

	//Initialization - All vertexes have infinity distance, except the source
	for(unsigned int i = 0; i < graph.number_vertexes(); i++){
		shared_ptr<Vertex> v = make_shared<Vertex>(i, i == from ? 0 : numeric_limits<unsigned int>::max(), -1);
		vertexes.push_back(v);
	}

	pq.push( from , vertexes[from] );

	//For each vertex with the minimum distance to, relax
	while(!pq.empty()){
		shared_ptr<Vertex> v = pq.pop();

		for(auto& edge: graph.adjacents(v->index)){
			if( !visited[edge->to] ){
				if( vertexes[edge->to]->distance_to == numeric_limits<unsigned int>::max() ){
					vertexes[edge->to]->distance_to = v->distance_to + edge->weight;
					pq.push( edge->to , vertexes[edge->to] );
				}
				else if( v->distance_to + edge->weight < vertexes[edge->to]->distance_to ){
					vertexes[edge->to]->distance_to = v->distance_to + edge->weight;
					pq.update( edge->to , vertexes[edge->to] );
				}
			}
		}
		visited[v->index] = true;
	}

	num_updates = bh.get_nro_update();
	num_pushes = bh.get_nro_pushes();
	num_pops = bh.get_nro_pops();

	return vertexes[to]->distance_to;
}