
#include <sstream>
#include <map>
#include <stack>
#include <memory>

using namespace std;

#include <boost/heap/fibonacci_heap.hpp>
#include <boost/unordered_map.hpp>

using namespace boost;

#include "GEOM/GeomPerfectMatching.h"

#include "tspaprox_christofides_enhanced.hpp"

using payload = pair<size_t, size_t>;

namespace std{
	template<>
	struct less<payload>{
		bool operator()(const payload& lhs, const payload& rhs) const{
			return lhs.second < rhs.second;
		}
	};

	template<>
	struct greater<payload>{
		bool operator()(const payload& lhs, const payload& rhs) const{
			return lhs.second > rhs.second;
		}
	};
}

using heap_queue = heap::fibonacci_heap<payload, heap::compare<std::greater<payload>>>;

vector<size_t> prim_mst(const GeometricGraph& graph){
	vector<bool> visited(graph.number_vertices(), false);
	vector<size_t> came_from(graph.number_vertices());
	vector<size_t> distance_to(graph.number_vertices(), numeric_limits<size_t>::max());
	heap_queue pq;
	vector<heap_queue::handle_type> handles(graph.number_vertices());
	
	for(size_t u = 0; u < graph.number_vertices(); u++) came_from[u] = u;

	auto vertices = graph.get_vertices();

	handles[0] = pq.push(make_pair(0,0));
	distance_to[0] = 0;

	while(!pq.empty()){
		auto v = pq.top();
		pq.pop();
		visited[v.first] = true;

		for(size_t u = 1; u < graph.number_vertices(); u++){
			if(u == v.first) continue;
			if(visited[u]) continue;

			auto distance = (vertices[u] - vertices[v.first]).distance;
			if( distance_to[u] == numeric_limits<size_t>::max() ){
				came_from[u] = v.first;
				distance_to[u] = distance;
				handles[u] = pq.push(make_pair(u, distance_to[u]));
			}else if( distance_to[u] > distance ){
				came_from[u] = v.first;
				distance_to[u] = distance;
				(*handles[u]).second = distance;
				pq.increase(handles[u]);
			}
		}
	}

	return came_from;
}

std::vector<size_t> get_odd_vertices(const vector<size_t>& parent_map){

	vector<size_t> vertices_degree(parent_map.size());

	for(size_t node = 0; node < parent_map.size(); node++){
		if( parent_map[node] != node ){
			vertices_degree[node]++;
			vertices_degree[parent_map[node]]++;
		}
	}

	vector<size_t> odd_nodes;
	for(size_t node = 0; node < vertices_degree.size(); node++){
		if( vertices_degree[node] % 2 == 1 ){
				odd_nodes.push_back(node);
		}
	}

	assert(odd_nodes.size() % 2 == 0);
	return odd_nodes;
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

GeometricGraph::GeometricGraph(std::istream& in){
	const string dimension_keyword = "DIMENSION";
	const string eof_keyword = "EOF";
	const string node_section_keyword = "NODE_COORD_SECTION";

	size_t size;
	while(true){

		string line = get_next<string>(in);

		if( line.compare(0, dimension_keyword.size(), dimension_keyword) == 0 ){
			size = get_next<size_t>(in);
		}else if(line.compare(0, node_section_keyword.size(), node_section_keyword) == 0 ){
			for(size_t i=0; i < size; i++) {
               auto j = get_next<size_t>(in);
               auto x = get_next<double>(in);
               auto y = get_next<double>(in);

               vertices.push_back(Vertex(j - 1, x, y));
             }
             break;
		}else if( line.compare(0, eof_keyword.size(), eof_keyword) == 0 ){
			break;
		}
	}

}


vector<Edge> minweight_pm::operator()(const GeometricGraph& graph, const vector<size_t>& nodes){
	const int dimension = 2;
	GeomPerfectMatching gpm(nodes.size(), dimension);
	gpm.options.verbose = false;

	for(const auto& node: nodes){
		double d[dimension];
		d[0] = graph.vertices[node].x;
		d[1] = graph.vertices[node].y;
		gpm.AddPoint(d);
	}

	gpm.Solve();

	vector<Edge> edges;
	vector<bool> visited(nodes.size(), false);
	for(size_t u = 0; u < nodes.size(); u++){
		auto other_point = gpm.GetMatch(u);
		if( visited[u] == false && visited[other_point] == false){
			edges.push_back(graph.vertices[nodes[u]] - graph.vertices[nodes[other_point]]);	
			visited[u] = true;
			visited[other_point] = true;
		}
	}

	return edges;
}

vector<Edge> minweight_geo_compl_pm::operator()(const GeometricGraph& graph, const vector<size_t>& nodes){
	const int dimension = 2;
	GeomPerfectMatching gpm(nodes.size(), dimension);
	gpm.options.verbose = false;

	for(const auto& node: nodes){
		double d[dimension];
		d[0] = graph.vertices[node].x;
		d[1] = graph.vertices[node].y;
		gpm.AddPoint(d);
	}

	gpm.SolveComplete();

	vector<Edge> edges;
	vector<bool> visited(nodes.size(), false);
	for(size_t u = 0; u < nodes.size(); u++){
		auto other_point = gpm.GetMatch(u);
		if( visited[u] == false && visited[other_point] == false){
			edges.push_back(graph.vertices[nodes[u]] - graph.vertices[nodes[other_point]]);	
			visited[u] = true;
			visited[other_point] = true;
		}
	}

	return edges;
}

vector<Edge> greedy_perfect_matching::operator()(const GeometricGraph& graph, const vector<size_t>& nodes){

	vector<Edge> edges_pf;
	vector<bool> visited(nodes.size(), false);
	for(size_t u = 0; u < nodes.size(); u++){
		if(visited[u] == true) continue;
		auto min_pos = u;
		auto min_distance = numeric_limits<decltype(Edge::distance)>::max();
		visited[u] = true;

		for(size_t v = u + 1; v < nodes.size(); v++){
			if(visited[v] == true) continue;

			auto distance = (graph.vertices[nodes[u]] - graph.vertices[nodes[v]]).distance;
			if( distance < min_distance ){
				min_distance = distance;
				min_pos = v;
			}
		}

		visited[min_pos] = true;
		edges_pf.push_back(graph.vertices[nodes[u]] - graph.vertices[nodes[min_pos]]);
	}

	return edges_pf;
}

bool only_even_degree(const GeometricGraph& graph, const vector<Edge>& edges){
	vector<int> degree_vertices(graph.number_vertices(), 0);
	for(const auto& edge: edges){
		degree_vertices[edge.from]++;
		degree_vertices[edge.to]++;
	}

	for(const auto& degree: degree_vertices){
		if( degree % 2 == 1 ) return false;
	}

	return true;
}
void create_multigraph(const GeometricGraph& graph, std::vector<Edge>& edges_pf, const std::vector<size_t>& parents){
	for(size_t u = 0; u < parents.size(); u++){
		if(parents[u] != u){
			edges_pf.push_back(graph.vertices[parents[u]] - graph.vertices[u]);
		}
	}

	assert( only_even_degree(graph, edges_pf) == true );
}

bool visits_all_vertices(const GeometricGraph& graph, const vector<Edge> edges){

	vector<bool> visited(graph.number_vertices(), false);
	for(const auto& edge: edges){
		if(visited[edge.to] == true) return false;
		visited[edge.to] = true;
	}

	return find(visited.begin(), visited.end(), false) == visited.end();
}

vector<Edge> get_short_path(const GeometricGraph& graph, const vector<size_t>& circuit, size_t start){
	vector<Edge> edges_circuit;
	vector<bool> visited(graph.number_vertices());

	queue<size_t> q;
	auto ref = circuit[start];
	for(size_t u = start + 1; u != start; u = ( u + 1 ) % circuit.size() ){
		if( visited[circuit[u]] == true ) continue;
		auto edge = (graph.vertices[ref] - graph.vertices[circuit[u]]);
		edges_circuit.push_back(edge);
		visited[ref] = true;
		ref = circuit[u];
	}

	edges_circuit.push_back(graph.vertices[ref] - graph.vertices[circuit[start]]);

	return edges_circuit;
}

size_t calculate_accu(const GeometricGraph& graph, const vector<size_t>& circuit, size_t start){
	auto edges_circuit = get_short_path(graph, circuit, start);
	return std::accumulate(edges_circuit.begin(), 
						   edges_circuit.end(), 
						   0, 
							[=](size_t a, const Edge& b){
								return a + b.distance;
							});
}

vector<Edge> euler_circuit_shortcutting(const GeometricGraph& graph, const vector<Edge>& edges){

	vector< vector<std::shared_ptr<pair<Edge, int>>> > connected(graph.number_vertices());

	for(const auto& edge: edges){
		auto edge_counter = std::make_shared<pair<Edge, int>>(edge, 1);
		connected[edge.from].push_back( edge_counter );
		connected[edge.to].push_back( edge_counter );
	}

	// Maintain a stack to keep vertices
    stack<size_t> curr_path;
    vector<size_t> circuit;
	
	auto current = edges[0].from;

	curr_path.push(current);
	while( !curr_path.empty() ){
		if( connected[current].size() > 0 ){
			
			auto edge_counter = connected[current].back();
			connected[current].pop_back();
			if( edge_counter->second == 0 ){
				continue;
			}

			curr_path.push(current);
			auto edge = edge_counter->first;
			edge_counter->second--;
			auto other = edge.from == current ? edge.to : edge.from; 

			current = other;
		}else{
			circuit.push_back(current);
			current = curr_path.top();
			curr_path.pop();
		}
	}

	auto min_distance = numeric_limits<size_t>::max();
	auto min_node = 0;

	for(size_t i = 0; i < circuit.size(); i++){
		auto distance = calculate_accu(graph, circuit, i);
		if( distance < min_distance ){
			min_distance = distance;
			min_node = i;
		}
	}

	return get_short_path(graph, circuit, min_node);

	// vector<Edge> edges_circuit;
	// vector<bool> visited(graph.number_vertices());
	// auto ref = circuit.front();
	// for(size_t u = 1; u < circuit.size() - 1; u++){
	// 	if( visited[circuit[u]] == true ) continue;
	// 	auto edge = (graph.vertices[ref] - graph.vertices[circuit[u]]);
	// 	edges_circuit.push_back(edge);
	// 	visited[ref] = true;
	// 	ref = circuit[u];
	// }

	// edges_circuit.push_back(graph.vertices[ref] - graph.vertices[circuit.front()]);

	// assert(visits_all_vertices(graph, edges_circuit) == true);

	//return edges_circuit;
}