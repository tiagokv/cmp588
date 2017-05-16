#ifndef RES_GRAPH_HPP
#define RES_GRAPH_HPP
#include <memory>
#include <vector>

class FlowEdge{
	size_t from;
	size_t to;
	size_t total_capacity;
	size_t current_capacity;

public:
	FlowEdge(size_t from, size_t to, size_t total_capacity):from(from),
															to(to),
															total_capacity(total_capacity),
															current_capacity(0){
	};

	size_t get_capacity(size_t requester){
		return (requester == from)? total_capacity - current_capacity: current_capacity;
	};

	void add_flow(size_t flow){
		current_capacity += flow;
	};

	size_t get_from(){
		return from;
	};

	size_t get_to(){
		return to;
	};
};


class ResidualGraph{

	std::vector<std::vector<std::shared_ptr<FlowEdge>>> edges;
	size_t nro_edges;
	size_t total_capacities;
	size_t max_capacities;

public:
	ResidualGraph(size_t quantityVertices): nro_edges(0), 
											total_capacities(0),
											max_capacities(0){
		edges.resize(quantityVertices);
	};

	ResidualGraph(): nro_edges(0), 
					 total_capacities(0),
					 max_capacities(0){
	};

	void reserve(size_t quantityVertices){
		edges.resize(quantityVertices);
	}

	void connect(const size_t& from,const size_t& to, size_t max_capacity);

	const std::vector<std::shared_ptr<FlowEdge>>& adjacents(size_t from) const{
		return edges[from];
	};

	size_t number_edges() const{
		return nro_edges;
	};

	size_t number_vertices() const{
		return edges.size();
	};

	size_t get_total_capacities() const{
		return total_capacities;
	};

	size_t get_max_capacities() const{
		return max_capacities;
	};
};

#endif


