#include <chrono>
#include <cmath>
#include <random>

#include "Dijkstra.hpp"

using namespace std;

random_device rd;		
mt19937 mt(rd());

struct vert_random{
	unsigned int index;
	vector<unsigned int> vertexes;
};

void build_graph(bool vary_edge, Graph& graph, int max_vertexes, int quantity_edges){
	graph.resize(max_vertexes);
	uniform_int_distribution<unsigned int> rand_vertex(0, max_vertexes-1);
	uniform_int_distribution<unsigned int> rand_weight(0, 1000);

	// if( vary_edge ){
		std::vector<vert_random> v;

		//Yes, this is not good for memory, but is temporary to build the graph
		for (unsigned int i = 0; i < max_vertexes; ++i)
		{
			vert_random vert;
			vert.index = i;
			//vert.vertexes.resize(max_vertexes);
			for (unsigned int j = 0; j < max_vertexes; ++j)
			{
				if( i != j ){
					vert.vertexes.push_back(j);
				}
			}
			v.push_back(vert);
		}

		//connect all vertexes
		while(!v.empty() && quantity_edges > 0){
			uniform_int_distribution<size_t> rand_vertex(0, v.size()-1);
			size_t from_index = rand_vertex(mt);

			uniform_int_distribution<size_t> rand_vertex_to(0, v[from_index].vertexes.size()-1);
			
			size_t to_index = rand_vertex_to(mt);

			graph.connect(v[from_index].index, v[from_index].vertexes[to_index], rand_weight(mt));
			quantity_edges--;

			v[from_index].vertexes.erase(begin(v[from_index].vertexes) + to_index);
			if( v[from_index].vertexes.empty() ){
				v.erase(begin(v) + from_index);
			}
		}

		// sanity check
		//cout << "terminou com " << quantity_edges << " e com " << v.size() << " sobrando" << endl;
	/*}else{
		int connected = 0;
		while(quantity_edges-- && connected <= pow(max_vertexes,2) ){
			unsigned int from = rand_vertex(mt);
			unsigned int to = rand_vertex(mt);

			int tentatives = 0;
			while(from == to || graph.are_connected(from,to)){
				if( tentatives > 100 ){
					auto adj = graph.adjacents(from);
					for (int i = 0; i < max_vertexes; ++i)
					{
						
					}
				}
				to = rand_vertex(mt);
				tentatives++;
			}
			graph.connect(from, to, rand_weight(mt));
			connected++;
		}
	}*/
}

void measure_dijkstra(bool vary_edges, int max_objs, int max_repetition, int min_var_obj, int max_var_obj){

    cout << "i I(i) D(i) U(i) T(i)" << endl;

	for(int i = min_var_obj; i < max_var_obj; i++){

		int repetition = max_repetition;
		Graph g;

		if( vary_edges ){
			build_graph(vary_edges, g, max_objs, pow(2, i));
		}else{
			build_graph(vary_edges, g, pow(2, i), max_objs);
		}

		uniform_int_distribution<unsigned int> rand_vertex(0, g.number_vertexes()-1);

		unsigned int stop_vertex = rand_vertex(mt);

		unsigned int num_pops_max = 0, num_pushes_max = 0, num_updates_max = 0;
		chrono::milliseconds total(0);

		while(repetition--){
			unsigned int initial_vertex = stop_vertex;
			while( stop_vertex == initial_vertex ) initial_vertex = rand_vertex(mt);

			unsigned int num_pops = 0, num_pushes = 0, num_updates = 0;

			chrono::system_clock::time_point t = chrono::system_clock::now();

			shortest_path(g, initial_vertex, stop_vertex, num_pops, num_pushes , num_updates );

			num_pushes_max = max(num_pushes_max, num_pushes);
			num_pops_max = max(num_pops_max, num_pops);
			num_updates_max = max(num_updates_max, num_updates);

			total += chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
		}
		cout << i << " " << max_repetition << " " << num_pushes_max << " " << num_pops_max << " " << num_updates_max << " " 
				  << " " << total.count() << endl;
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