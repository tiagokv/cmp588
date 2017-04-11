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

void build_graph(Graph& graph, int max_vertexes, int quantity_edges){
	graph.resize(max_vertexes);
	uniform_int_distribution<unsigned int> rand_vertex(0, max_vertexes-1);
	uniform_int_distribution<unsigned int> rand_weight(0, 1000);

	std::vector<vert_random> v;

	//Yes, this is not good for memory, but is temporary
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

/*	while(quantity_edges--){
		unsigned int from = rand_vertex(mt);
		unsigned int to = rand_vertex(mt);
		while(from == to || graph.are_connected(from,to)){
			to = rand_vertex(mt);
		}
		graph.connect(from, to, rand_weight(mt));
	}*/
}

int main(int argv, char** argc){

	const int max_vertexes = pow(2, 10);
	const int max_repetition = 30;
	const int max_edges = 21;
	const int min_edges = 10;

    cout << "i I(i) D(i) U(i) T(i)" << endl;

	uniform_int_distribution<unsigned int> rand_vertex(0, max_vertexes-1);

	for(int i = min_edges; i < max_edges; i++){
		int quantity_edges = pow(2, i);

		int repetition = max_repetition;
		Graph g;
		build_graph(g, max_vertexes, quantity_edges);
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
	

	return 0;
}