#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

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

	unsigned int num_pops = 0, num_pushes = 0, num_updates = 0;

	cout << "Shortest Path from " << from << " to " << to << " costs " << shortest_path(g, from, to, num_pops, num_pushes, num_updates) << endl;
	return 0;
}