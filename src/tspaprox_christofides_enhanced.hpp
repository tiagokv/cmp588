#ifndef TSPAPROX_CHRIS_ENHANCED_HPP
#define TSPAPROX_CHRIS_ENHANCED_HPP

#include <vector>
#include <utility>
#include <iostream>
#include <cmath>
#include <algorithm>

#include <boost/functional/hash.hpp>

class Edge{
public:

	size_t from;
	size_t to;
	unsigned int distance;

	Edge(size_t from, size_t to, unsigned int distance): from(from), to(to), distance(distance){
	};

	bool operator>(const Edge& other){
		return this->distance > other.distance;
	}

	bool operator<(const Edge& other){
		return this->distance < other.distance;
	}

	// friend std::size_t hash_value(const Edge& e)
 //    {
 //        std::size_t seed = 0;
 //        boost::hash_combine(seed, e.x);
 //        boost::hash_combine(seed, e.y);

 //        return seed;
 //    }
};

class Vertex{
public:
	size_t index;
	double x;
	double y;

	Vertex(){};
	Vertex(size_t index, double x, double y):index(index), x(x), y(y){};

	Edge operator-(const Vertex& v) const{
		double xd = this->x - v.x;
	    double yd = this->y - v.y;
	    return Edge(this->index, v.index, static_cast<unsigned int>(sqrt(xd*xd+yd*yd))); 
	}
};

class GeometricGraph{
public:	
	std::vector<Vertex> vertices;

	GeometricGraph(size_t vertices_size){
		vertices.resize(vertices_size);
	}

	GeometricGraph(std::istream& in);

	void add_vertex(Vertex v){
		vertices[v.index] = v;
	}

	size_t number_vertices() const{
		return vertices.size();
	}

	const std::vector<Vertex>& get_vertices() const{
		return vertices;
	}
};

std::vector<size_t> prim_mst(const GeometricGraph& graph);
std::vector<size_t> get_odd_vertices(const std::vector<size_t>& parent_map);

struct minweight_pm{
	std::vector<Edge> operator()(const GeometricGraph& graph, const std::vector<size_t>& nodes);
};

struct greedy_perfect_matching{
	std::vector<Edge> operator()(const GeometricGraph& graph, const std::vector<size_t>& nodes);
};

struct minweight_geo_compl_pm{
	std::vector<Edge> operator()(const GeometricGraph& graph, const std::vector<size_t>& nodes);
};

template<typename perf_match_strategy, bool verbose = true>
size_t tsp_aproximation_christofides(const GeometricGraph& graph){
	perf_match_strategy pms;

	auto parent = prim_mst(graph);
	auto odd_nodes = get_odd_vertices(parent);
	if( verbose ){
		std::cout << "Calculate " << odd_nodes.size() << " odd nodes" << std::endl;
		std::cout << "Will start from node " << odd_nodes[0] << 
					 " with coord " << graph.vertices[odd_nodes[0]].x << " " << graph.vertices[odd_nodes[0]].y << std::endl; 
	}

	auto edges = pms(graph, odd_nodes);
	assert( odd_nodes.size() / 2 == edges.size() );

	create_multigraph(graph, edges, parent);

	auto hamiltonian_edges = euler_circuit_shortcutting(graph, edges);

	return std::accumulate(hamiltonian_edges.begin(), 
						   hamiltonian_edges.end(), 
						   0, 
							[=](size_t a, const Edge& b){
								return a + b.distance;
							});
}

void create_multigraph(const GeometricGraph& graph, std::vector<Edge>& edges_pf, const std::vector<size_t>& parents);

std::vector<Edge> euler_circuit_shortcutting(const GeometricGraph& graph, const std::vector<Edge>& edges);

#endif