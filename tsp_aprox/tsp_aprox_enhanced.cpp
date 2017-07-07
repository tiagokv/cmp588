#include <iostream>

using namespace std;

#include "tspaprox_christofides_enhanced.hpp"

int main(){

	GeometricGraph gg(cin);

	cout << "Graph contains " << gg.number_vertices() << " vertices" << endl;

	cout << "The minimum circuit costs " << tsp_aproximation_christofides<minweight_pm, false>(gg) << endl;

	return 0;
}