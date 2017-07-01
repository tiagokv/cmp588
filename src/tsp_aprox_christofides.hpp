#ifndef TSP_APROX_CHRISTOFIDES_HPP
#define TSP_APROX_CHRISTOFIDES_HPP
#include <utility>

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/adjacency_list.hpp>

struct VertexInformation { };
 
struct EdgeInformation {
  size_t weight;
};

using TSPGraph = boost::adjacency_matrix<boost::undirectedS, 
										 VertexInformation, 
										 EdgeInformation> ;
using TSPNode = boost::graph_traits<TSPGraph>::vertex_descriptor;
using TSPEdge = boost::graph_traits<TSPGraph>::edge_descriptor;


TSPGraph read_tsp(std::istream& f);

struct minweight_perfect_matching{
	std::vector<TSPEdge> operator()(const TSPGraph& graph, const std::vector<TSPNode>& nodes);
};

struct gredy_perfect_matching{
	std::vector<TSPEdge> operator()(const TSPGraph& graph, const std::vector<TSPNode>& nodes);
};


std::vector<TSPEdge> prim_mst(const TSPGraph& graph); 
std::vector<TSPNode> filter_even_degrees(const TSPGraph& graph, const std::vector<TSPEdge>& edges);
std::vector<TSPEdge> euler_circuit(const TSPGraph& graph, const std::vector<TSPEdge>& edges);
std::vector<TSPEdge> transform_to_hamiltonian_circuit(const TSPGraph& graph, std::vector<TSPEdge>& edges);
void merge_edges(const TSPGraph& graph, std::vector<TSPEdge>& prim_edges, const std::vector<TSPEdge>& pf_edges);
bool visits_all(const TSPGraph& graph, const std::vector<TSPEdge>& edges);

template<typename PerfectMatchingStrategy>
size_t tsp_aprox_christofides(const TSPGraph& graph){
	PerfectMatchingStrategy match_strategy;

	auto edges = prim_mst(graph);
	auto odd_nodes = filter_even_degrees(graph, edges);
	auto matching_edges = match_strategy(graph, odd_nodes);

	merge_edges(graph, edges, matching_edges);

	auto euler_circuit_edges = euler_circuit(graph, edges);
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