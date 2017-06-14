#ifndef MAXIMUM_MATCHING_HPP
#define MAXIMUM_MATCHING_HPP

#include <memory>
#include <vector>
#include <limits>

#include "MatchingGraph.hpp"

class MaximumMatching{
protected:
	// Matching Graph, the left side goes from [0, number_vertices()/2) and 
	// the right [number_vertices()/2, number_vertices()) 
	std::shared_ptr<MatchingGraph> graph;

	//Stores all mates, with 0 being free and 1 being vertex 0, etc...
	std::vector<size_t> mates;
	std::vector<size_t> dist;
	size_t cardinality;
	size_t phases;
	size_t max_iterations;

	size_t get_mate(const size_t& v){
		return mates[v] - 1;
	}

	bool dfs(const size_t& v);

	auto end_left(){
		return begin(mates) + graph->number_vertices() / 2;
	};

	bool is_vert_free(const size_t& i){
		return mates[i] == 0;
	};

	bool search_paths();

	void extract_paths();

	std::vector<size_t> get_free_vert_left();

	std::vector<size_t> select_from_right(const std::vector<size_t>& left, std::vector<bool>& visited);
	std::vector<size_t> select_from_left(const std::vector<size_t>& right, std::vector<bool>& visited, bool& found);

public:
	MaximumMatching(std::shared_ptr<MatchingGraph> graph):graph(graph), 
														  cardinality(0),
														  phases(0),
														  max_iterations(0){

		//Starts with everyone free
		mates.resize(graph->number_vertices(), 0);
		dist.resize(graph->number_vertices(), std::numeric_limits<size_t>::max());
		extract_paths();
	};

	size_t get_cardinality(){
		return cardinality;
	};

	size_t get_phases(){
		return phases;
	};

};

#endif