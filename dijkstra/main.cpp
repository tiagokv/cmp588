#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <cstdlib>

#include "BinaryHeap.hpp"
#include "Graph.hpp"
using namespace std;

void read_dimacs(std::istream& in, unsigned& n, unsigned& m, Graph& a) {
	string line="", dummy;
	while (line.substr(0,4) != "p sp")
		getline(in,line);
	
  // (1) get nodes and edges
	stringstream linestr;
	linestr.str(line);
	linestr >> dummy >> dummy >> n >> m;
	a.resize(n);
	unsigned i=0;
	while (i<m) {
		getline(in,line);
		if (line.substr(0,2) == "a ") {
			stringstream arc(line);
			unsigned u,v,w;
			char ac;
			arc >> ac >> u >> v >> w;
      		a.connect(u,v,w);
			i++;
		}
	}
}

class Vertex
{
public:
	unsigned int index;
	unsigned int distance_to;
	unsigned int came_from;

	Vertex(unsigned int index, unsigned int distance_to, unsigned int came_from ):index(index), 
																				  distance_to(distance_to), 
																				  came_from(came_from){};
};

int shortest_path(const Graph& graph, unsigned int from, unsigned int to){

	BinaryHeap<shared_ptr<Vertex>> pq(graph.number_vertexes());
	vector<shared_ptr<Vertex>> vertexes;
	vector<bool> visited(graph.number_vertexes(), false);

	//Initialization - All vertexes have infinity distance, except the source
	for(int i = 0; i < graph.number_vertexes(); i++){
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
		if( v->index == to )
			return v->distance_to;
	}

	return -1;
}

int main(int argv, char** argc){

	if( argv < 3 ){
		cerr << "No suficient parameters" << endl;
		return 1;
	}

	unsigned int from = atoi(argc[1]), to = atoi(argc[2]);
	unsigned int num_vertexes, num_edges;
	Graph g;

	read_dimacs( cin , num_vertexes, num_edges, g);

	cout << "Graph loaded successfully - with " << num_vertexes << " vertexes and " << num_edges << " edges" << endl; 

	cout << shortest_path(g, from, to) << endl;
	return 0;
}