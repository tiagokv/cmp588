#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <chrono>

#include "Graph.hpp"
#include "Dijkstra.hpp"

using namespace std;

void read_dimacs(std::istream& in, unsigned& n, unsigned& m, Graph& a) {
	string line="", dummy;
	while (line.substr(0,4) != "p sp")
		getline(in,line);
	
  // (1) get nodes and edges
	stringstream linestr;
	linestr.str(line);
	linestr >> dummy >> dummy >> n >> m;
	a.reserve(n);
	unsigned i=0;
	while (i<m) {
		getline(in,line);
		if (line.substr(0,2) == "a ") {
			stringstream arc(line);
			unsigned u,v,w;
			char ac;
			arc >> ac >> u >> v >> w;
      		a.connect(static_cast<size_t>(u-1),static_cast<size_t>(v-1),w);
			i++;
		}
	}
}

int main(int argv, char** argc){

	if( argv < 3 ){
		cerr << "No suficient parameters" << endl;
		return 1;
	}

	unsigned int from = atoi(argc[1]) - 1, to = atoi(argc[2]) - 1;
	unsigned int num_vertexes, num_edges;
	Graph g;

	read_dimacs(cin , num_vertexes, num_edges, g);

	cout << "Graph loaded successfully - with " << num_vertexes << " vertexes and " << num_edges << " edges" << endl; 

	chrono::system_clock::time_point t = chrono::system_clock::now();
	Dijkstra dijks(g, from);

	cout << "Shortest Path from " << from << " to " << to << " costs " << dijks.get_shortest_distance(to) << endl;
	cout << "Took " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() << " ms to execute" << endl;
	return 0;
}