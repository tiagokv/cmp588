#ifndef MAXIMUM_MATCHING_HPP
#define MAXIMUM_MATCHING_HPP

#include <memory>

#include "MatchingGraph.hpp"

class MaximumMatching{

	// Matching Graph, the left side goes from [0, number_vertices()/2) and 
	// the right [number_vertices()/2, number_vertices()) 
	std::shared_ptr<MatchingGraph> graph;

	//Stores all mates, with 0 being free and 1 being vertex 0, etc...
	std::vector<size_t> mates;
	size_t cardinality;

public:
	MaximumMatching(std::shared_ptr<MatchingGraph> graph):graph(graph), cardinality(0){

		//Starts with everyone free
		mates.resize(graph->number_vertices()); 
		extract_paths();
	};

	void extract_paths(){
		while(cardinality < graph->number_vertices() / 2){
			auto visited = search_paths();
			for(const auto& v: visited){
				
			}
		}
	};

	auto end_left(){
		return begin(mates) + graph->number_vertices() / 2;
	};

	auto is_vert_free(const size_t& i){
		return mates[i] > 0;
	}

	vector<bool> search_paths(){
		vector<bool> visited( graph->number_vertices() , false);
		vector<size_t> distance(graph->number_vertices());

		vector<size_t> u1;

		for(size_t i = 0; i < mates.size(); i++){
			if(is_vert_free(i)) u1.push_back(i);
		}

		bool found = false;
		do{
			vector<size_t> u2;
			for(const auto& u: u1){
				visited[u] = true;
				for(const auto& v: graph->adjacents(u)){
					if( visited[v] == false ){
						distance[v] = distance[u] + 1;
						u2.push_back(v);
					}
				}
			}

			found = false;
			u1.clear();
			for(const auto& u: u2){
				visited[u] = true;
				if( is_vert_free(i) ){
					found = true;
					break;
				}else{
					auto mate = mates[u] - 1;
					if( visited[mate] == false ){
						distance[mate] = distance[u] + 1;
						u1.push_back(mate);
					}
				}
			}
		}while(found == true);
	}

};

#endif