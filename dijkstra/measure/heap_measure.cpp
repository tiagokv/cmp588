#include <iostream>
#include <cmath>
#include <chrono>
#include <cassert>
#include <random>
#include <string>
#include <fstream>

#include "NAryHeap.hpp"

using namespace std;

int execute_push(NAryHeap<unsigned int>& bh, unsigned int& top, size_t& qt_numbers){

	while(qt_numbers--){
		bh.push( top , top );
		top--;
	}

	return bh.get_nro_swaps();
}

void measure_push(){
	const int max_repetitions = 5;
	const int max_iterations = 30;
	// format of output
	cout << "i R R*T(i) I(i)" << endl;

	unsigned int top = pow(2, max_iterations);

	NAryHeap<unsigned int> bh(2, top);

	top--;

	for(int iteration = 0; iteration < max_iterations; iteration++){
		
		bh.reset_swaps();
		unsigned long swaps = 0;
		chrono::milliseconds aggregated_time(0);
		size_t qt_numbers = pow(2, iteration + 1) - pow(2, iteration);
		
		chrono::system_clock::time_point t = chrono::system_clock::now();

		for(int repetition = 0; repetition < max_repetitions - 1; repetition++){
			NAryHeap<unsigned int> bh_save(bh);
			auto top_save = top;
			auto qt_numbers_save = qt_numbers;
			swaps = execute_push( bh_save, top_save, qt_numbers_save); // doesn't it swap (2^i)*i?
		}

		swaps = execute_push(bh, top , qt_numbers);
		aggregated_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
		// medição
		cout << iteration << " " << max_repetitions << " " << aggregated_time.count() << " " << swaps << endl;
	}
}

void measure_update(){
	const int max_repetitions = 1;
	const int max_iterations = 21;
	// format of output
	cout << "i R R*T(i) S(i)" << endl;

	for(int iteration = 1; iteration < max_iterations; iteration++){
		NAryHeap<unsigned int> bh(2, 2*pow(2, iteration)-1);
		unsigned long swaps = 0;
		chrono::milliseconds aggregated_time(0);
		
		int i = 0;
		for(; i < pow(2,iteration) - 1; i++){
			bh.push(i, static_cast<unsigned int>(pow(2,iteration) + 1));
		}

		int init_update = i;
		//cout << i << endl;
		for(; i < init_update + pow(2,iteration); i++){
			bh.push(i, static_cast<unsigned int>(pow(2,iteration) + 2));
		}
		//cout << i << endl;

		unsigned int top = static_cast<unsigned int>(pow(2,iteration));
		chrono::system_clock::time_point t = chrono::system_clock::now();

		//bh.print_heap();

		for(i = init_update; i < init_update + pow(2,iteration); i++){
			//cout << "updating " << i << " with " << top << endl; 
			bh.update(i, top--);
		}
		aggregated_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
		// medição
		cout << iteration << " " << max_repetitions << " " << aggregated_time.count() << " " << bh.get_nro_swaps() << endl;
		//bh.print_heap();
	}
}

void measure_delete(){
	random_device rd;		
	mt19937 mt(rd());

	cout << "i T(i) D(i)" << endl;

	const int max_iterations = 31;

	for(int i = 1; i < max_iterations; i++){
		uniform_int_distribution<size_t> pick(0,pow(2,i)-1);
		NAryHeap<unsigned int> bh(2, pow(2,i)-1);

		for(int x = 0; x < pow(2,i)-1; x++){
			bh.push(x, pick(mt));
		}

		bh.reset_swaps();
		unsigned int remove = pow(2,i) - 1;
		chrono::milliseconds aggregated_time(0);
		chrono::system_clock::time_point t = chrono::system_clock::now();
		while(remove--) bh.pop();
		aggregated_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
		cout << i << " " << aggregated_time.count() << " " << bh.get_nro_swaps() << endl;
	}
}

int main(int argc, char** argv){

	string prefix;
	if(argc > 1) prefix.append(argv[1]);

	ofstream push_file(prefix + "push");
	ofstream update_file(prefix + "update");
	ofstream delete_file(prefix + "delete");

	switch(argv[1][0]){
		case 'p':
			measure_push();
			break;
		case 'u':
			measure_update();
			break;
		case 'd':
			measure_delete();
			break;				
		default:
			break;
	}

	push_file.close();
	update_file.close();
	delete_file.close();
}	