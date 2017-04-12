#include <vector>
#include <limits>
#include <memory>

#include "Dijkstra.hpp"
#include "NAryHeap.hpp"
/*#include "BinaryHeap.hpp"*/

using namespace std;

bool operator<(const std::shared_ptr<Vertex>& lhs, const std::shared_ptr<Vertex>& rhs){
	return lhs->distance_to < rhs->distance_to;
}

int shortest_path(const Graph& graph, unsigned int from, unsigned int to,
				  unsigned int& num_pops, unsigned int& num_pushes, unsigned int& num_updates, bool stopAtFinal){

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

		if( stopAtFinal && v->index == to )
			return vertexes[to]->distance_to; 

		for(auto& edge: graph.adjacents(v->index)){
			if( !visited[edge->to] ){
				if( vertexes[edge->to]->distance_to == numeric_limits<unsigned int>::max() ){
					vertexes[edge->to]->distance_to = v->distance_to + edge->weight;
					vertexes[edge->to]->came_from = v->index;
					pq.push( edge->to , vertexes[edge->to] );
				}
				else if( v->distance_to + edge->weight < vertexes[edge->to]->distance_to ){
					vertexes[edge->to]->distance_to = v->distance_to + edge->weight;
					vertexes[edge->to]->came_from = v->index;
					pq.update( edge->to , vertexes[edge->to] );
				}
			}
		}

		visited[v->index] = true;
	}

	num_updates = pq.get_nro_update();
	num_pushes = pq.get_nro_pushes();
	num_pops = pq.get_nro_pops();

	return vertexes[to]->distance_to;
}