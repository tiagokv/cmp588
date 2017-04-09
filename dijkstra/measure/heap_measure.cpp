#include <iostream>
#include <cmath>
#include <chrono>

#include "BinaryHeap.hpp"

using namespace std;

int execute(BinaryHeap<unsigned int>& bh, unsigned int& top, unsigned int& qt_numbers){

	while(qt_numbers--){
		bh.push( top , top );
		top--;
	}

	return bh.get_nro_swaps();
}

int main(int argc, char** argv){
	const int max_repetitions = 5;
	const int max_iterations = 20;
	// format of output 
	unsigned int top = pow(2, max_iterations);

	BinaryHeap<unsigned int> bh(top);
	cout << "# i R R*T(i) I(i)" << endl;
	top--;

	for(int iteration = 0; iteration < max_iterations; iteration++){
		
		bh.reset_swaps();
		unsigned long int swaps = 0;
		chrono::milliseconds aggregated_time(0);
		unsigned int qt_numbers = pow(2, iteration + 1) - pow(2, iteration);
		
		chrono::system_clock::time_point t = chrono::system_clock::now();

		for(int repetition = 0; repetition < max_repetitions - 1; repetition++){
			BinaryHeap<unsigned int> bh_save(bh);
			auto top_save = top;
			auto qt_numbers_save = qt_numbers;
			swaps = execute( bh_save, top_save, qt_numbers_save); // doesn't it swap (2^i)*i?
		}

		swaps = execute(bh, top , qt_numbers);
		aggregated_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
		// medição
		cout << iteration << " " << max_repetitions << " " << aggregated_time.count() << " " << swaps << endl;
	}

}	