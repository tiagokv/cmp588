#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <memory>

class Edge
{
public:
	unsigned int from;
	unsigned int to;
	unsigned int weight;

	Edge(unsigned int from, unsigned int to, unsigned int weight):from(from),to(to),weight(weight){};
};

class Graph{
	private:
		std::vector<std::vector<std::shared_ptr<Edge>>> edges;

	public:
		void resize(int newSize);
		void connect(unsigned int from,unsigned int to,unsigned int weight);
		std::vector<std::shared_ptr<Edge>> adjacents(int vertex) const;
		int number_vertexes() const { return edges.size(); };
};

#endif
	