#ifndef TSP_APROX_CHRISTOFIDES_HPP
#define TSP_APROX_CHRISTOFIDES_HPP
#include <utility>
 
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/adjacency_list.hpp>

struct VertexInformation { };
 
struct EdgeInformation {
  int weight;
};

// using TSPGraph = boost::adjacency_list<boost::vecS,
// 									   boost::vecS,
// 									   boost::undirectedS, 
// 									   boost::no_property, 
// 									   EdgeInformation> ;
using TSPGraph = boost::adjacency_matrix<boost::undirectedS, 
									     boost::no_property, 
									     EdgeInformation> ;
using TSPNode = boost::graph_traits<TSPGraph>::vertex_descriptor;
using TSPEdge = boost::graph_traits<TSPGraph>::edge_descriptor;


TSPGraph read_tsp(std::istream& f);

struct minweight_perfect_matching{
	std::vector<TSPEdge> operator()(const TSPGraph& graph, const std::vector<TSPNode>& nodes);
};

struct greedy_perfect_matching{
	std::vector<TSPEdge> operator()(const TSPGraph& graph, const std::vector<TSPNode>& nodes);
};


std::vector<TSPEdge> prim_mst(const TSPGraph& graph); 
std::vector<TSPNode> filter_even_degrees(const TSPGraph& graph, const std::vector<TSPEdge>& edges);
std::vector<TSPEdge> euler_circuit(const TSPGraph& graph, const std::vector<TSPEdge>& edges);
std::vector<TSPEdge> transform_to_hamiltonian_circuit(const TSPGraph& graph, std::vector<TSPEdge>& edges);
void merge_edges(const TSPGraph& graph, std::vector<TSPEdge>& prim_edges, const std::vector<TSPEdge>& pf_edges);
bool visits_all(const TSPGraph& graph, const std::vector<TSPEdge>& edges);
bool only_even_degree(const TSPGraph& graph, const std::vector<TSPEdge>& edges);

template<typename PerfectMatchingStrategy, bool verbose = false>
size_t tsp_aprox_christofides(const TSPGraph& graph){
	PerfectMatchingStrategy match_strategy;

	if( verbose ) std::cerr << "Started prim..." << std::endl; 
	auto edges = prim_mst(graph);

	if( verbose ) std::cerr << "Getting odd nodes from " << edges.size() << " edges..." << std::endl;
	auto odd_nodes = filter_even_degrees(graph, edges);

	if( verbose ) std::cerr << "Applying perfect match strategy with " << odd_nodes.size() << " odd nodes ..." << std::endl;
	auto matching_edges = match_strategy(graph, odd_nodes);
	assert( (odd_nodes.size() / 2) == matching_edges.size() );

	merge_edges(graph, edges, matching_edges);

	if( verbose ) std::cerr << "Calculating eulerian circuit with " << edges.size() << " edges..." << std::endl;
	auto euler_circuit_edges = euler_circuit(graph, edges);

	if( verbose ) std::cerr << "Transforming to hamiltonian circuit..." << std::endl;
	auto halm_circ_edges = transform_to_hamiltonian_circuit(graph, euler_circuit_edges);

	assert( visits_all(graph, halm_circ_edges) );

	return std::accumulate(halm_circ_edges.begin(), 
						   halm_circ_edges.end(), 
						   0, 
							[=](size_t a, const TSPEdge& b){
								return a + graph[b].weight;
							});
}

#endif