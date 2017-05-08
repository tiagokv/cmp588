#ifndef RES_GRAPH_HPP
#define RES_GRAPH_HPP
#include <memory>
#include <vector>

class FlowEdge{
	size_t from;
	size_t to;
	double total_capacity;
	double current_capacity;

public:
	FlowEdge(size_t from, size_t to, double total_capacity):from(from),to(to),total_capacity(total_capacity),current_capacity(0){
	};

	double get_capacity(size_t requester){
		return (requester == from)? total_capacity - current_capacity: current_capacity;
	};

	void add_flow(double flow){
		current_capacity += flow;
	};

	size_t get_from(){
		return from;
	};

	size_t get_to(){
		return to;
	}
};


class ResidualGraph{

	std::vector<std::vector<std::shared_ptr<FlowEdge>>> edges;
	size_t nro_edges;

public:
	ResidualGraph(size_t quantityVertices): nro_edges(0){
		edges.resize(quantityVertices);
	}

	void connect(size_t from, size_t to, double max_capacity);

	const std::vector<std::shared_ptr<FlowEdge>>& adjacents(size_t from) const{
		return edges[from];
	};

	size_t number_edges() const{
		return nro_edges;
	};

	size_t number_vertices() const{
		return edges.size();
	}
};

#endif


