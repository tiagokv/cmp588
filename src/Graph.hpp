#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <memory>

class Edge
{
public:
	size_t from;
	size_t to;
	unsigned int weight;

	Edge(size_t from, size_t to, unsigned int weight):from(from),to(to),weight(weight){};
};

class Graph{
	private:
		std::vector<std::vector<Edge>> edges;
		size_t qtt_edges;

	public:
		Graph():qtt_edges(0){};
		void reserve(size_t newSize);
		void connect(const size_t& from, const size_t& to, unsigned int weight);
		const std::vector<Edge>& adjacents(const size_t& vertex) const;
		size_t number_vertices() const { return edges.size(); };
		size_t number_edges() const { return qtt_edges; };
		bool are_connected(const size_t& a, const size_t& b) const;
};

#endif
	