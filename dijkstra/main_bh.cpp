#include <iostream>
#include <cmath>
#include <chrono>

#include "BinaryHeap.hpp"

using namespace std;

int main(int argc, char** argv){
	const int max_repetitions = 1;
	const int max_iterations = 5;
	// format of output 

	cout << "# i T(i) I(i)" << endl;

	for(int iteration = 0; iteration < max_iterations; iteration++){
		
		unsigned long int swaps = 0;
		
		chrono::milliseconds aggregated_time;
		for(int repetition = 0; repetition < max_repetitions; repetition++){
			unsigned int top = pow(2, iteration) - 1;
			
			BinaryHeap<unsigned int> bh(top);
			chrono::system_clock::time_point t = chrono::system_clock::now();
			
			for (unsigned int i = top - 1; top > 0 && i > 0; --i){
				bh.push( i , i );
			}

			if( top > 0 ){
				bh.push( 0 , 0 );
			} 

			aggregated_time += chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
			swaps = bh.get_nro_swaps();
		}
		// medição
		cout << iteration << " " << (aggregated_time.count() / max_repetitions)
			 << " " << swaps << endl;
	}

}	