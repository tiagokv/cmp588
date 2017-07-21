
#include "MaximumMatching.hpp"

#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

bool MaximumMatching::dfs(const size_t& v){
	bool found = false;
	for(const auto& adj: graph->adjacents(v)){
		if( is_vert_free(adj) == false ){
			if( dist[get_mate(adj)] != numeric_limits<size_t>::max() && 
				dist[get_mate(adj)] == dist[v] + 2 ){
				found = true;
				if( dfs(get_mate(adj)) ){
					mates[v] = adj + 1;
					mates[adj] = v + 1;

					dist[v] = numeric_limits<size_t>::max();
					dist[adj] = numeric_limits<size_t>::max();					
					return true;
				}
			}
		} 
	}

	if( !found && v < graph->number_vertices() / 2 ){ 
		// if didn't find a adjacent that has a mate
		// find one that is free
		for(const auto& adj: graph->adjacents(v)){
			if( is_vert_free(adj) == true && dist[adj] == dist[v] + 1 ){
				mates[v] = adj + 1;
				mates[adj] = v + 1;

				dist[v] = numeric_limits<size_t>::max();
				dist[adj] = numeric_limits<size_t>::max();	
				return true;
			}
		}
	}

	dist[v] = numeric_limits<size_t>::max();
	return false;
}

vector<size_t> MaximumMatching::get_free_vert_left(){
	vector<size_t> left;
	for(size_t i = 0; i < mates.size() / 2; i++){
		if(is_vert_free(i)){
			left.push_back(i);
			dist[i] = 0;
		}
	}

	return left;
}

vector<size_t> MaximumMatching::select_from_right(const vector<size_t>& left, vector<bool>& visited){
	vector<size_t> right;
	for(const auto& u: left){
		visited[u] = true;
		for(const auto& v: graph->adjacents(u)){
			if( visited[v] == false && get_mate(u) != v ){
				visited[u] = true;
				dist[v] = dist[u] + 1;
				right.push_back(v);
			}
		}
	}
	return right;
}

vector<size_t> MaximumMatching::select_from_left(const vector<size_t>& right, vector<bool>& visited, bool& found){
	vector<size_t> left;
	found = false;
	for(const auto& u: right){
		if( visited[u] == false ){
			visited[u] = true;
			if( is_vert_free(u) ){
				found = true;
			}else{
				if( visited[get_mate(u)] == false ){
					dist[get_mate(u)] = dist[u] + 1;
					left.push_back(get_mate(u));
				}
			}
		}
	}

	if( found ){
		for(const auto& l : left){ // adjust dist of lefts if found the end
			dist[l]--;
		}
	}
	return left;
} 

bool MaximumMatching::search_paths(){
	vector<bool> visited( graph->number_vertices() , false);
	vector<size_t> left = get_free_vert_left();

	bool found = false;
	do{
		auto right = select_from_right(left, visited);
		left = select_from_left(right, visited, found);
	}while(found == false && !left.empty());

	return found;
}

bool MaximumMatching::check_mates_sanity(){
	vector<bool> visited( graph->number_vertices() , false);

	for(size_t i = 0; i < mates.size()/2; i++){
		if( mates[i] == 0 ) continue;
		auto mate = get_mate(i);
		if( visited[i] == false && visited[mate] == false ){
			visited[i] = true;
			visited[mate] = true;
		}else{
			return false;
		}
	}

	return true;
}

void MaximumMatching::extract_paths(){
	while( search_paths() ){
		phases++;
		auto card = 0;
		for(size_t v = 0; v < graph->number_vertices() / 2; v++){
			if( is_vert_free(v) ){
				if( dfs(v) ) 
					card++;
			}
		}
		cardinality += card;
		assert( card >= 1 );
		assert( check_mates_sanity() );
	}
};