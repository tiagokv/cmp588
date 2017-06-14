
#include "MaximumMatching.hpp"

#include <vector>

using namespace std;

bool MaximumMatching::dfs(const size_t& v){
	bool free = is_vert_free(v);
	for(const auto& adj: graph->adjacents(v)){
		// if vertex adjacent was reached by vertex v
		if( dist[adj] == dist[v] + 1 ){
			if( dfs(adj) == true ){
				if( v < graph->number_vertices() / 2){
					mates[v] = adj + 1;
					mates[adj] = v + 1;
				}
				return true;
			}
		}
	}

	//if entered but no matching was found
	if( dist[v] == 0 ){
		return false;
	}
	dist[v] = numeric_limits<size_t>::max();
	return is_vert_free(v);
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

void MaximumMatching::extract_paths(){
	while( search_paths() ){
		phases++;
		for(size_t v = 0; v < graph->number_vertices() / 2; v++){
			if( is_vert_free(v) ){
				if( dfs(v) ) 
					cardinality++;;
			}
		}
	}
};