#include <fstream>
#include <string>
#include <chrono>
#include <regex>

using namespace std;

#include <boost/filesystem.hpp>
using namespace boost;

#include "DimacsReader.hpp"
#include "ResidualGraph.hpp"
#include "FordFulkersonFattestPath.hpp"

const string data_path = "../measure/data/";

int main(int argv, char** argc){
	
	string graph_type(argc[1]);
	
	ofstream measure_file;
	measure_file.open("../measure/measure_" + graph_type + ".dat");

	measure_file << "Edges Vertices Iterations TotalCapacity MaxFlow Time" << endl;

	filesystem::path p(data_path);
	regex file_name_regex(graph_type + ".+\\.gr");

	for(auto&& file : filesystem::directory_iterator(p)){
		if( regex_match(file.path().filename().c_str() , file_name_regex) ){
			DimacsReader direader;

		    size_t source, target;
		    auto graph = direader.read_max_flow_graph( file.path().c_str() , source, target);

		    chrono::system_clock::time_point t = chrono::system_clock::now();
		    FordFulkersonFattestPath fffat(*graph, source, target);
		    chrono::milliseconds time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);

		    measure_file << graph->number_edges() << " " << graph->number_vertices() << " "
		    			 << fffat.get_iterations() << " " << fffat.get_max_flow() << " " << graph->get_total_capacities() << " "
		    			 << time.count() << endl;
		}
	}

	measure_file.close();
	return 0;
}