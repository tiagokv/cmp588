#include <fstream>
#include <string>
#include <chrono>
#include <regex>

using namespace std;

#include <boost/filesystem.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace boost;

// graph element descriptors
typedef adjacency_list_traits<vecS,vecS,directedS>::vertex_descriptor DiNode;
typedef adjacency_list_traits<vecS,vecS,directedS>::edge_descriptor BoostEdge;
 
// a directed graph with reverse edges
struct VertexInformation {};
typedef unsigned Capacity;
struct EdgeInformation {
  Capacity edge_capacity;
  Capacity edge_residual_capacity;
  BoostEdge reverse_edge;
};
 
typedef adjacency_list<vecS,vecS,directedS,VertexInformation,EdgeInformation> DiGraph;

#include "DimacsReader.hpp"
#include "ResidualGraph.hpp"
#include "FordFulkersonFattestPath.hpp"

const string data_path = "../measure/data/";

void read_dimacs_graph(const string& filepath, DiGraph& dig, DiNode& source, DiNode& target){
	fstream fs(filepath);
	read_dimacs_max_flow(dig,
					 get(&EdgeInformation::edge_capacity, dig),
					 get(&EdgeInformation::reverse_edge, dig),
					 source, target, fs);
}


int main(int argv, char** argc){
	
	if( argv < 2 ){
		cerr << "Enter the graph type. Either mesh, ..." << endl;
		return 1;
	}

	string graph_type(argc[1]);
	
	ofstream measure_file;
	measure_file.open("../measure/measure_" + graph_type + ".dat");

	measure_file << "Edges Vertices Iterations MaxFlow Time PRTime" << endl;

	filesystem::path p(data_path);
	regex file_name_regex(graph_type + ".+\\.gr");

	for(auto&& file : filesystem::directory_iterator(p)){
		if( regex_match(file.path().filename().c_str() , file_name_regex) ){
			cout << "Processing file " << file.path().filename().c_str() << endl;

			DimacsReader direader;

		    size_t source, target;
		    auto graph = direader.read_max_flow_graph( file.path().c_str() , source, target);

		    chrono::system_clock::time_point t = chrono::system_clock::now();
		    FordFulkersonFattestPath fffat(*graph, source, target);
		    chrono::milliseconds time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);

	      	DiGraph dig;
  			DiNode nsource, ntarget;
	    	read_dimacs_graph(file.path().c_str(), dig, nsource, ntarget);

	    	t = chrono::system_clock::now();
	    	auto max_flow_pr = push_relabel_max_flow(dig, nsource, ntarget,
                                		  get(&EdgeInformation::edge_capacity, dig),
                                		  get(&EdgeInformation::edge_residual_capacity, dig),
                                		  get(&EdgeInformation::reverse_edge, dig),
                                		  get(boost::vertex_index, dig));
	    	auto time_pr = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);

	    	if( fffat.get_max_flow() != max_flow_pr ){
	    		cerr << "Dude, this shouldn't happen!" << endl;
	    		return 2;
	    	}

		    measure_file << graph->number_edges() << " " << graph->number_vertices() << " "
		    			 << fffat.get_iterations() << " " << fffat.get_max_flow() << " "
		    			 << time.count() << " " << time_pr.count() << endl;
		}
	}

	measure_file.close();
	return 0;
}