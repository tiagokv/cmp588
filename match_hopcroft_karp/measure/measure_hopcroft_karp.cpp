#include <memory>
#include <string>
#include <fstream>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;
using namespace chrono;

#include "MatchingGraph.hpp"
#include "MaximumMatching.hpp"
#include "FordFulkersonFattestPath.hpp"

const int MAX_REP = 1;

random_device rd;		
mt19937 mt(rd());

void build_matching_graph(size_t vertices, size_t edges, shared_ptr<MatchingGraph> matchGraph, shared_ptr<ResidualGraph> resGraph){

	chrono::milliseconds total(0);

	chrono::system_clock::time_point t = chrono::system_clock::now();

	matchGraph->reserve(vertices * 2);
	resGraph->reserve(vertices * 2 + 2);

	double probability = min( static_cast<double>(edges) / pow(vertices, 2), 1.0 );

	bernoulli_distribution rand_vertex(probability);

	vector<tuple<size_t,size_t>> connections;

	for(size_t from = 0; from < vertices; from++){
		for(size_t to = vertices; to < 2 * vertices; to++){
			if( rand_vertex(mt) ){
				connections.push_back(make_tuple(from,to));
			}
		}
	}

	shuffle(connections.begin(), connections.end(), mt);

	for(auto& ft: connections){
		size_t from, to;
		tie(from, to) = ft;
		matchGraph->connect(from, to);
		resGraph->connect(from + 1, to + 1, 1);
	}

	for(size_t to = 0; to < vertices; to++){
		resGraph->connect(0, to + 1, 1);
	}

	for(size_t from = vertices; from < 2 * vertices; from++){
		resGraph->connect(from + 1, 2 * vertices + 1, 1);
	}

	total += chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
	cerr << "Took " << total.count() << "ms to instantiate the graph" << endl;
}

void measure(ofstream& output, bool vary_edges, int max_objs, int min_var_obj, int max_var_obj){
	output << "Vertices Edges Phases Cardinality Repetitions HHTime FFTime" << endl;
	for (int i = min_var_obj; i < max_var_obj; ++i){
		auto graph = make_shared<MatchingGraph>();
		auto resGraph = make_shared<ResidualGraph>();

		if( vary_edges ){
			build_matching_graph(max_objs, static_cast<size_t>(pow(2, i)), graph, resGraph);
		}else{
			build_matching_graph(static_cast<size_t>(pow(2, i)), max_objs, graph, resGraph);
		}

		milliseconds totalHH(0);
		size_t phases = 0;
		size_t cardinality = 0;
		for(int i = 0; i < MAX_REP; i++){
			system_clock::time_point t = system_clock::now();
			MaximumMatching mm(graph);
			totalHH += duration_cast<milliseconds>(system_clock::now()-t);

			phases = mm.get_phases();
			cardinality = mm.get_cardinality();
		}

		milliseconds totalFF(0);
		size_t max_flow = 0;
		for(int i = 0; i < MAX_REP; i++){
			system_clock::time_point t = system_clock::now();
			FordFulkersonFattestPath fffat(*resGraph, 0, resGraph->number_vertices() - 1);
			totalFF += duration_cast<milliseconds>(system_clock::now()-t);
			max_flow = fffat.get_max_flow();
		}

		if( max_flow != cardinality ){
			cerr << "Error FF: " << max_flow << " HH: " << cardinality << endl; 
			//return;
		}

		output << graph->number_vertices() << " " << graph->number_edges() << " " <<
				  phases << " " << cardinality << " " << MAX_REP << " " <<
				  totalHH.count() << " " << totalFF.count() << endl;
	}

}

/*
	The input parameters are:
	1: 'e' or 'v', whether varies edges or vertices
	2: Fixed number of object that will not vary
	3: power of 2 that will start the varying object
	4: power of 2 that will go to 
*/
int main(int argv, char** argc){
	
	bool vary_edges = argc[1][0] == 'e';
	int max_objs = atoi(argc[2]);
	int min_var_obj = atoi(argc[3]);
	int max_var_obj = atoi(argc[4]);

	cerr << "Enter following parameters: " << endl;
	cerr << "Vary edges: " << boolalpha << vary_edges << endl;
	cerr << "Max objs: " << max_objs << endl;
	cerr << "Min var obj: " << min_var_obj << endl;
	cerr << "Max var obj: " << max_var_obj << endl;

	ofstream output_file;

	string file_name = "measure_" + to_string(argc[1][0]) + 
												 "_" + to_string(max_objs) + 
												 "_" + to_string(min_var_obj) + 
												 "_" + to_string(max_var_obj) + ".dat";
	output_file.open("../measure/" + file_name);

	measure(output_file, vary_edges, max_objs, min_var_obj, max_var_obj);

	output_file.close();
	return 0;
}