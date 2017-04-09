#include <chrono>
#include <cmath>
#include <random>

using namespace std;

int main(int argv, char** argc){

	const int max_vertexes = pow(2, 20);
	const int max_repetition = 30;
	const int max_edges = 19;
	const int max_running_times = 5;

	random_device rd;		
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(1.0, 10.0);

	for(int i = 0; i < max_edges; i++)
		int quantity_edges = pow(2, i);

		int repetition = max_repetition;
		while(repetition--){
			Graph g;
			build_graph(g, max_vertexes, quantity_edges);

			unsigned int initial_vertex = random();
			unsigned int stop_vertex = random();

			unsigned int num_pops = 0;
			unsigned int num_pushes = 0;
			unsigned int num_updates = 0;

			int running_times = max_running_times;
			chrono::milliseconds total(0);

			while(running_times--){
				chrono::system_clock::time_point t = chrono::system_clock::now();

				int shortest_path_cost = shortest_path(g, initial_vertex, stop_vertex, 
													   num_pops, num_pushes , num_updates );
				total += chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
			}

			cout << i << " " << num_pushes << " " << num_pops << " " << num_updates << " " << max_running_times << " " << total.count() << endl;
		}

	}
	

	return 0;
}