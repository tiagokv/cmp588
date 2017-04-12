#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <random>

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

	unsigned int num_vertexes, num_edges;
	Graph g;

	read_dimacs( cin , num_vertexes, num_edges, g);

	cout << "Graph loaded successfully - with " << num_vertexes << " vertexes and " << num_edges << " edges" << endl; 

	unsigned int num_pops = 0, num_pushes = 0, num_updates = 0;

	chrono::milliseconds total(0);
	int rep = 10;

	random_device rd;		
	mt19937 mt(rd());
	uniform_int_distribution<unsigned int> rand_vertex(0, g.number_vertexes()-1);

	while(rep--){
		unsigned int from = rand_vertex(mt);
		unsigned int to = rand_vertex(mt);
		chrono::system_clock::time_point t = chrono::system_clock::now();

		shortest_path(g, from, to, num_pops, num_pushes, num_updates, false);

		total += chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
	}

	cout << "Took " << total.count() << " ms to execute" << endl;
	return 0;
}