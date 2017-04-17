#include <chrono>
#include <cmath>
#include <random>
#include <iostream>

#include "Dijkstra.hpp"

using namespace std;

const int REP = 1;

random_device rd;		
mt19937 mt(rd());

struct vert_random{
	unsigned int index;
	vector<unsigned int> vertexes;
};

void build_graph(bool vary_edge, Graph& graph, int max_vertexes, int quantity_edges){


	srand48(time(0));
	chrono::milliseconds total(0);

	chrono::system_clock::time_point t = chrono::system_clock::now();

	graph.reserve(max_vertexes);

	double probability = min( static_cast<double>(quantity_edges) / pow(max_vertexes,2), 1.0 );
	bernoulli_distribution rand_vertex(probability);
	uniform_int_distribution<unsigned int> rand_weight(0, 1000);

	for(size_t from = 0; from < max_vertexes; from++){
		for(size_t to = 0; to < max_vertexes; to++){
			/*if( from != to && rand_vertex(mt) ){
				graph.connect(from, to, rand_weight(mt));
			}*/

			if( from != to && drand48() < probability ){
				graph.connect(from, to, rand_weight(mt));
			}
		}
	}

	total += chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
	cerr << "Took " << total.count() << "ms to instantiate the graph" << endl;
}

void measure_dijkstra(bool vary_edges, int max_objs, int max_repetition, int min_var_obj, int max_var_obj){

    cout << "i ii V E I(i) D(i) U(i) R R*T(i)" << endl;

	for(int i = min_var_obj; i < max_var_obj; i++){

		int repetition = max_repetition;
		Graph g;

		if( vary_edges ){
			build_graph(vary_edges, g, max_objs, pow(2, i));
		}else{
			build_graph(vary_edges, g, pow(2, i), max_objs);
		}

		uniform_int_distribution<size_t> rand_vertex(0, g.number_vertexes()-1);

		size_t stop_vertex = rand_vertex(mt);

		while(repetition--){
			auto initial_vertex = stop_vertex;
			while( stop_vertex == initial_vertex ) initial_vertex = rand_vertex(mt);

			unsigned int num_pops = 0, num_pushes = 0, num_updates = 0;

			chrono::milliseconds total(0);
			chrono::system_clock::time_point t = chrono::system_clock::now();

			for(int i = 0; i < REP; i++){
				shortest_path(g, initial_vertex, stop_vertex, num_pops, num_pushes , num_updates );
				total += chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
			}

			cout << i << " " << (max_repetition - repetition) << " " << g.number_vertexes() << " " << g.number_edges() << " " 
				 << num_pushes << " " << num_pops << " " << num_updates << " " 
				 << REP << " " << total.count() << endl;
		}
	}
	
}

int main(int argv, char** argc){

	// const int max_vertexes = pow(2, 10);
	// const int max_repetition = 30;
	// const int max_edges = 21;
	// const int min_edges = 10;

	bool vary_edges = argc[1][0] == 'e';
	int max_objs = atoi(argc[2]);
	int max_repetition = atoi(argc[3]);
	int min_var_obj = atoi(argc[4]);
	int max_var_obj = atoi(argc[5]);

	cerr << "Enter following parameters: " << endl;
	cerr << "Vary edges: " << boolalpha << vary_edges << endl;
	cerr << "Max objs: " << max_objs << endl;
	cerr << "Max repetition: " << max_repetition << endl;
	cerr << "Min var obj: " << min_var_obj << endl;
	cerr << "Max var obj: " << max_var_obj << endl;

	measure_dijkstra(vary_edges, max_objs, max_repetition, min_var_obj, max_var_obj);

	return 0;
}