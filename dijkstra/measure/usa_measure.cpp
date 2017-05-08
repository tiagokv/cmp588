#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <random>

#include "Graph.hpp"
#include "Dijkstra.hpp"

using namespace std;

void read_dimacs(std::istream& in, Graph& a) {
	string line="", dummy;
	while (line.substr(0,4) != "p sp")
		getline(in,line);
	
  // (1) get nodes and edges
	stringstream linestr;
	unsigned n, m;
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
      		a.connect(u,v,w);
			i++;
		}
	}
}

int main(int argv, char** argc){

	Graph g;

	read_dimacs( cin , g);

	cout << "Graph loaded successfully - with " << g.number_vertices() << " vertices and " << g.number_edges() << " edges" << endl; 

	chrono::milliseconds total(0);
	int rep = 10;

	random_device rd;		
	mt19937 mt(rd());
	uniform_int_distribution<unsigned int> rand_vertex(0, g.number_vertices() - 1);

	while(rep--){
		unsigned int from = rand_vertex(mt);

		chrono::system_clock::time_point t = chrono::system_clock::now();

		Dijkstra dijks(g, from);

		total += chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
	}

	cout << "Took " << total.count() << " ms to execute" << endl;
	return 0;
}