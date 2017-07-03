
#include <string>
#include <sstream>
#include <memory>
#include <iostream>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

#include <boost/algorithm/string/classification.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

using namespace boost;

#include "PerfectMatching.h"

#include "tsp_aprox_christofides.hpp"

using Point2d = pair<double, double>;

int get_euclidian_dist2d(const Point2d& v, const Point2d& u){
	double xd = v.first - u.first;
    double yd = v.second - u.second;
    return static_cast<int>(sqrt(xd*xd+yd*yd));
}

template<typename T>
T get_next(istream& f){
	string line;
	while( line == " " || line.empty() || line == ":") f >> line;
	stringstream s(line);
	T value;
	s >> value;
	return value;
}

TSPGraph read_tsp(std::istream& f){
	const string dimension_keyword = "DIMENSION";
	const string eof_keyword = "EOF";
	const string node_section_keyword = "NODE_COORD_SECTION";

	size_t size;
	vector<Point2d> vertices;
	while(true){

		string line = get_next<string>(f);

		if( line.compare(0, dimension_keyword.size(), dimension_keyword) == 0 ){
			size = get_next<size_t>(f);
			vertices.resize(size);
		}else if(line.compare(0, node_section_keyword.size(), node_section_keyword) == 0 ){
			for(size_t i=0; i < size; i++) {
               auto j = get_next<size_t>(f);
               auto x = get_next<double>(f);
               auto y = get_next<double>(f);

               vertices[j-1] = std::make_pair(x, y);
             }
		}else if( line.compare(0, eof_keyword.size(), eof_keyword) == 0 ){
			break;
		}
	}

	cout << "Read whole file" << endl;

	TSPGraph graph(size);
	for(size_t i = 0; i < size; i++){
		for(size_t j = i + 1; j < size; j++ ){
			if( i != j ){
				EdgeInformation edgeProp {get_euclidian_dist2d(vertices[i], vertices[j])};
				add_edge(i, j, edgeProp, graph);
			}
		}
	}

	cout << "Computed whole graph" << endl;

	return graph;
}


vector<TSPEdge> minweight_perfect_matching::operator()(const TSPGraph& graph, const vector<TSPNode>& nodes){
	assert( nodes.size() % 2 == 0 );
	PerfectMatching perf_match(nodes.size(), (nodes.size()*nodes.size() - nodes.size()) / 2);

	for(size_t u = 0; u < nodes.size(); u++ ){
		for(size_t v = u + 1; v < nodes.size(); v++){
			if( v != u ){
				perf_match.AddEdge(u, v, graph[edge(nodes[u], nodes[v], graph).first].weight);
			}
		}
	}

	perf_match.Solve();

	vector<TSPEdge> edges;
	vector<bool> visited(nodes.size(), false);
	for(size_t v = 0; v < nodes.size(); v++){
		visited[v] = true;
		auto match = perf_match.GetMatch(v);

		if( visited[match] == false){
			edges.push_back(edge(nodes[v], nodes[match], graph).first);	
			visited[match] = true;
		}
	}

	return edges;
}

vector<TSPEdge> greedy_perfect_matching::operator()(const TSPGraph& graph, const vector<TSPNode>& nodes){

	const auto max_value = numeric_limits<decltype(EdgeInformation::weight)>::max();
	vector<bool> visited(nodes.size(), false);
	vector<TSPEdge> edges;

	for(size_t u = 0; u < nodes.size(); u++){

		if( visited[u] ) continue;
		auto min = max_value;
		auto min_node = u;

		for(size_t v = u + 1; v < nodes.size(); v++){
			auto weight = graph[edge(nodes[u], nodes[v], graph).first].weight;
			if( u != v && visited[v] == false && weight < min){
				min = weight;
				min_node = v;
			}
		}

		visited[u] = true;
		visited[min_node] = true;

		edges.push_back( edge(nodes[u], nodes[min_node], graph).first );
	}

	return edges;

	// auto cmp = [=](const TSPEdge& lhs, const TSPEdge& rhs){ return graph[lhs].weight > graph[rhs].weight; };
	// priority_queue<TSPEdge, vector<TSPEdge>, decltype(cmp)> pq(cmp);

	// for(size_t u = 0; u < nodes.size(); u++ ){
	// 	for(size_t v = u + 1; v < nodes.size(); v++){
	// 		pq.push(edge(nodes[u], nodes[v], graph).first);
	// 	}
	// }

	// vector<bool> visited(nodes.size(), false);
	// vector<TSPEdge> edges;
	// auto quantity_edges = nodes.size() / 2;
	// while(edges.size() < quantity_edges && !pq.empty()){
	// 	auto edge = pq.top();
	// 	auto s = source(edge, graph);
	// 	auto t = target(edge, graph);
	// 	if( visited[s] == false && visited[t] == false ){
	// 		edges.push_back(edge);
	// 		visited[s] = true;
	// 		visited[t] = true;				
	// 	}
	// 	pq.pop();
	// }

	return edges;
}

vector<TSPEdge> prim_mst(const TSPGraph& graph){
	vector<TSPNode> p(num_vertices(graph));
	vector<TSPEdge> edges;

	prim_minimum_spanning_tree(graph, &p[0], weight_map(get(&EdgeInformation::weight, graph)));

	for (size_t i = 0; i != p.size(); ++i){
    	if (p[i] != i){
    		edges.push_back(edge(p[i], i, graph).first);
		}
	}

	return edges;
}
vector<TSPNode> filter_even_degrees(const TSPGraph& graph, const vector<TSPEdge>& edges){

	vector<size_t> degree(num_vertices(graph), 0);

	for(const auto& edge: edges){
		auto u = source(edge, graph);
		auto v = target(edge, graph);
		degree[u]++;
		degree[v]++;
	}

	vector<TSPNode> odd_nodes;

	for(size_t i = 0; i < num_vertices(graph); i++){
		if(degree[i] > 0 && degree[i] % 2 == 1){
			odd_nodes.push_back(vertex(i, graph));
		}
	}

	assert( odd_nodes.size() % 2 == 0 );
	return odd_nodes;
}

void backtrack_euler_circuit(const TSPGraph& graph, TSPNode& current, vector<vector<int>>& visited, vector<TSPNode>& circuit){
	auto adjacent_pair = adjacent_vertices(current, graph);
	for(auto it = adjacent_pair.first; it != adjacent_pair.second; it++){
		if(visited[current][*it] > 0){
			visited[current][*it]--;
			visited[*it][current]--;
			TSPNode next = *it;
			backtrack_euler_circuit(graph, next, visited, circuit);
		}
	}
	circuit.push_back(current);
}

vector<TSPEdge> euler_circuit(const TSPGraph& graph, const vector<TSPEdge>& edges){
	//we can start from any node as there are only even nodes
	// vector<vector<int>> visited(num_vertices(graph));
	// for(auto& v: visited){
	// 	v.resize(num_vertices(graph), 0);
	// }

	// size_t quantity_edges = 0;
	// for(const auto& edge: edges){
	// 	auto s = source(edge, graph);
	// 	auto t = target(edge, graph);
	// 	//as this is a multigraph, parallel edges are allowed
	// 	visited[s][t]++; 
	// 	visited[t][s]++;
	// 	quantity_edges++;
	// }

	// vector<TSPNode> euler_circuit_nodes;
	// TSPNode s = source(edges[0], graph);
	// backtrack_euler_circuit(graph, s, visited, euler_circuit_nodes);

	// vector<TSPEdge> edges_out;
	// auto rit = euler_circuit_nodes.rbegin();
	// TSPNode	nodeBef = *rit;
	// for(rit++; rit != euler_circuit_nodes.rend(); rit++){
	// 	edges_out.push_back(edge(nodeBef, *rit, graph).first);
	// 	nodeBef = *rit;
	// }

	// return edges_out;

	vector<vector<int>> visited(num_vertices(graph));
	for(auto& v: visited){
		v.resize(num_vertices(graph), 0);
	}

	for(const auto& edge: edges){
		auto s = source(edge, graph);
		auto t = target(edge, graph);
		//as this is a multigraph, parallel edges are allowed
		visited[s][t]++; 
		visited[t][s]++;
	}

	// Maintain a stack to keep vertices
    stack<TSPNode> curr_path;
 
    // vector to store final circuit
    vector<TSPNode> circuit;
	
	auto current = source(edges[0], graph);

	curr_path.push(current);
	while( !curr_path.empty() ){

		auto to_be_visited = numeric_limits<size_t>::max();
		for(size_t i = 0; i < visited.size(); i++){
			if(visited[current][i] > 0){
				to_be_visited = i;
				break;
			}
		}

		if( to_be_visited != numeric_limits<size_t>::max()){
			curr_path.push(current);

			visited[current][to_be_visited]--;
			visited[to_be_visited][current]--;

			current = to_be_visited;
		}else{
			circuit.push_back(current);
			current = curr_path.top();
			curr_path.pop();
		}
	}

	vector<TSPEdge> edges_out;
	auto rit = circuit.rbegin();
	TSPNode	nodeBef = *rit;
	for(rit++; rit != circuit.rend(); rit++){
		edges_out.push_back(edge(nodeBef, *rit, graph).first);
		nodeBef = *rit;
	}

	return edges_out;
}
vector<TSPEdge> transform_to_hamiltonian_circuit(const TSPGraph& graph, vector<TSPEdge>& edges){

	vector<bool> visited(num_vertices(graph));
	vector<TSPEdge> hamiltonian_circuit;
	const TSPNode null_node = graph_traits<TSPGraph>::null_vertex();
	TSPNode ref = null_node;
	for(const auto& e: edges){
		auto s = source(e, graph);
		auto t = target(e, graph);
		if( ref == null_node ){
			if( visited[t] == false ){
				hamiltonian_circuit.push_back(e);
				visited[t] = true;
			}else{
				ref = s;
			}
		}else{
			if( visited[t] == false ){
				hamiltonian_circuit.push_back(edge(ref, vertex(t, graph), graph).first);
				visited[ref] = true;
				ref = null_node;
			}else{
				// let it be the first ref the source, continue till find another feasible target
			}
		}
		visited[s] = true;
	}

	hamiltonian_circuit.push_back( edge( target(hamiltonian_circuit.back(), graph), source(edges.front(), graph), graph ).first );

	return hamiltonian_circuit;
}

void merge_edges(const TSPGraph& graph, vector<TSPEdge>& prim_edges, const vector<TSPEdge>& pf_edges){
	// vector<vector<bool>> visited(num_vertices(graph));
	// for(auto& v: visited){
	// 	v.resize(num_vertices(graph), false);
	// }

	// std::vector<TSPEdge> edges_merged;
	// for(const auto& edge: prim_edges){
	// 	auto s = source(edge, graph);
	// 	auto t = target(edge, graph);
	// 	visited[s][t] = true;
	// 	visited[t][s] = true;
	// }

	// for(const auto& edge: pf_edges){
	// 	auto s = source(edge, graph);
	// 	auto t = target(edge, graph);
	// 	if( visited[s][t] == false && visited[t][s] == false ){
	// 		prim_edges.push_back( edge );
	// 	}
	// }

	prim_edges.insert(prim_edges.end(), pf_edges.begin(), pf_edges.end());

	assert( only_even_degree(graph, prim_edges) );
}

bool visits_all(const TSPGraph& graph, const std::vector<TSPEdge>& edges){
	vector<bool> visited(num_vertices(graph), false);

	size_t vertices_to_visit = visited.size();
	for(const auto& e: edges){
		auto s = source(e, graph);
		auto t = target(e, graph);
		if(visited[t]) return false;

		visited[t] = true;
		vertices_to_visit--;
	}

	return vertices_to_visit == 0;
}

bool only_even_degree(const TSPGraph& graph, const std::vector<TSPEdge>& edges){

	vector<size_t> degrees(num_vertices(graph), 0);

	for(const auto& edge: edges){
		auto s = source(edge, graph);
		auto t = target(edge, graph);
		degrees[t]++;
		degrees[s]++;
	}

	for(const auto& degree: degrees){
		if( degree % 2 == 1 ){
			return false;
		}
	}

	return true;
}