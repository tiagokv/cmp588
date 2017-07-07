#include <iostream>
#include <chrono>
#include <limits>

using namespace std;

#include "tspaprox_christofides_enhanced.hpp"

int main(int argv, char** argc){

	
	if( argv != 2 ){
		cout << "Provide the measure mode" << endl;
		return 255;
	}

	string mode(argc[1]); 

	GeometricGraph gg(cin);
	auto min_cost = numeric_limits<size_t>::max();
	chrono::system_clock::time_point t = chrono::system_clock::now();
	if( mode == "g" ){
		min_cost = tsp_aproximation_christofides<greedy_perfect_matching, false>(gg);
	}else if(mode == "p"){
		min_cost = tsp_aproximation_christofides<minweight_pm, false>(gg);
	}else if(mode == "pg"){
		min_cost = tsp_aproximation_christofides<minweight_geo_compl_pm, false>(gg);
	}else{
		cout << "Invalid parameter" << endl;
		return 255;
	}
	chrono::milliseconds time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);

	cerr << min_cost << " " << time.count() << endl;

	return 0;
}