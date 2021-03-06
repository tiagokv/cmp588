#include <sstream>
#include <cstdlib>
#include <fstream>
#include <chrono>

#include "DimacsReader.hpp"

using namespace std;

shared_ptr<ResidualGraph> DimacsReader::read_max_flow_graph(std::string filepath, size_t& source, size_t& target){
    fstream dimacs_file(filepath);
    return read_max_flow_graph(dimacs_file, source, target);
}

shared_ptr<ResidualGraph> DimacsReader::read_max_flow_graph(std::istream& in, size_t& source, size_t& target){
    auto graph = make_shared<ResidualGraph>();
	string line="", dummy;
	while (line.substr(0,5) != "p max") 
		getline(in,line);
	
  // (1) get nodes and edges
	stringstream linestr;
	linestr.str(line);
    size_t number_vertices, number_edges;
	linestr >> dummy >> dummy >> number_vertices >> number_edges;
	graph->reserve(number_vertices);

	size_t id;
	string which;
	while(line[0] != 'n') 
		getline(in,line);

	linestr.clear();
	linestr.str(line);
	linestr >> dummy >> id >> which;
	if( which[0] == 's' )
		source = id - 1;
	else
		target = id - 1;

	getline(in,line);
	while(line[0] != 'n') 
		getline(in,line);

	linestr.clear();
	linestr.str(line);
	linestr >> dummy >> id >> which;

	if( which[0] == 's' )
		source = id - 1;
	else
		target = id - 1;

	unsigned i = 0;
	while (i < number_edges) {
		getline(in,line);
		if (line.substr(0,2) == "a ") {
			stringstream arc(line);
			unsigned u,v, w;
			char ac;
			arc >> ac >> u >> v >> w;
      		graph->connect(static_cast<size_t>(u-1), 
      					   static_cast<size_t>(v-1), 
      					   static_cast<size_t>(w));
			i++;
		}
	}

    return graph;
}

shared_ptr<Graph> DimacsReader::read_graph(std::string filepath){
    fstream dimacs_file(filepath);
    return read_graph(dimacs_file);
}

shared_ptr<Graph> DimacsReader::read_graph(std::istream& in){
    auto graph = make_shared<Graph>();
	string line="", dummy;
	while (line.substr(0,4) != "p sp")
		getline(in,line);
	
  // (1) get nodes and edges
	stringstream linestr;
	linestr.str(line);
    size_t number_vertices, number_edges;
	linestr >> dummy >> dummy >> number_vertices >> number_edges;
	graph->reserve(number_vertices);
	unsigned i=0;
	while (i < number_edges) {
		getline(in,line);
		if (line.substr(0,2) == "a ") {
			stringstream arc(line);
			unsigned u,v,w;
			char ac;
			arc >> ac >> u >> v >> w;
      		graph->connect(static_cast<size_t>(u-1),static_cast<size_t>(v-1),w);
			i++;
		}
	}

    return graph;
}

shared_ptr<MatchingGraph> DimacsReader::read_matching_graph(std::string filepath){
    fstream dimacs_file(filepath);
    return read_matching_graph(dimacs_file);
}

shared_ptr<MatchingGraph> DimacsReader::read_matching_graph(std::istream& in){
	chrono::system_clock::time_point t = chrono::system_clock::now();
	//Usually this both functions below enables faster processing
	ios_base::sync_with_stdio(false); // unsync C-io with C++-io
	cin.tie(nullptr); // remove sync from cout and cin

    auto graph = make_shared<MatchingGraph>();
	string line="", dummy;
	while (line.substr(0,6) != "p edge")
		getline(in,line);
	
  // (1) get nodes and edges
	stringstream linestr;
	linestr.str(line);
    size_t number_vertices, number_edges;
	linestr >> dummy >> dummy >> number_vertices >> number_edges;
	graph->reserve(number_vertices);
	unsigned i=0;
	while (i < number_edges) {
		getline(in,line);
		if (line.substr(0,2) == "e ") {
			stringstream arc(line);
			unsigned u, v;
			char ac;
			arc >> ac >> u >> v;
      		graph->connect(static_cast<size_t>(u-1), static_cast<size_t>(v-1));
			i++;
		}
	}

	chrono::milliseconds time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);

	cerr << "Succesfully loaded graph with " << graph->number_vertices() << " vertices and "
		 << graph->number_edges() << " edges in " << time.count() << "ms" << endl;

    return graph;
}