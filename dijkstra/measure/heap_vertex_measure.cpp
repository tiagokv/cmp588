#include <iostream>
#include <cmath>
#include <chrono>
#include <cassert>
#include <random>
#include <string>
#include <fstream>
#include <memory>

#include "NAryHeap.hpp"

using namespace std;

class Vertex
{
public:
	size_t index;
	unsigned int distance_to;
	size_t came_from;

	Vertex(size_t index, unsigned int distance_to, size_t came_from ):index(index), 
																	  distance_to(distance_to), 
																	  came_from(came_from){};
	bool operator<(const Vertex& rhs) const{
		std::cerr << "compared!" << std::endl;
		return this->distance_to < rhs.distance_to;
	}
};

bool operator<(const std::shared_ptr<Vertex>& lhs, const std::shared_ptr<Vertex>& rhs){
	return lhs->distance_to < rhs->distance_to;
}

int execute_push(NAryHeap<shared_ptr<Vertex>>& bh, unsigned int& top, size_t& qt_numbers){

	while(qt_numbers--){
		bh.push( top , make_shared<Vertex>(0, top , 0) );
		top--;
	}

	return bh.get_nro_swaps();
}

void measure_push(ofstream& output){
	const int max_repetitions = 5;
	const int max_iterations = 21;
	// format of output
	output << "i R R*T(i) I(i)" << endl;

	unsigned int top = pow(2, max_iterations);

	NAryHeap<shared_ptr<Vertex>> bh(2, top);

	top--;

	for(int iteration = 0; iteration < max_iterations; iteration++){
		
		bh.reset_swaps();
		unsigned long swaps = 0;
		chrono::milliseconds aggregated_time(0);
		size_t qt_numbers = pow(2, iteration + 1) - pow(2, iteration);
		
		chrono::system_clock::time_point t = chrono::system_clock::now();

		for(int repetition = 0; repetition < max_repetitions - 1; repetition++){
			NAryHeap<shared_ptr<Vertex>> bh_save(bh);
			auto top_save = top;
			auto qt_numbers_save = qt_numbers;
			swaps = execute_push( bh_save, top_save, qt_numbers_save); // doesn't it swap (2^i)*i?
		}

		swaps = execute_push(bh, top , qt_numbers);
		aggregated_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
		// medição
		output << iteration << " " << max_repetitions << " " << aggregated_time.count() << " " << swaps << endl;
	}
}

void measure_update(ofstream& output){
	const int max_repetitions = 1;
	const int max_iterations = 21;
	// format of output
	output << "i R R*T(i) S(i)" << endl;

	for(int iteration = 1; iteration < max_iterations; iteration++){
		NAryHeap<shared_ptr<Vertex>> bh(2, 2*pow(2, iteration)-1);
		chrono::milliseconds aggregated_time(0);
		
		int i = 0;
		for(; i < pow(2,iteration) - 1; i++){
			bh.push(i, make_shared<Vertex>(0, static_cast<unsigned int>(pow(2,iteration) + 1), 0)  );
		}

		int init_update = i;
		//cout << i << endl;
		for(; i < init_update + pow(2,iteration); i++){
			bh.push(i, make_shared<Vertex>(0, static_cast<unsigned int>(pow(2,iteration) + 2), 0));
		}
		//cout << i << endl;

		unsigned int top = static_cast<unsigned int>(pow(2,iteration));
		chrono::system_clock::time_point t = chrono::system_clock::now();

		//bh.print_heap();

		for(i = init_update; i < init_update + pow(2,iteration); i++){
			//cout << "updating " << i << " with " << top << endl; 
			bh.update(i, make_shared<Vertex>(0, top--,0));
		}
		aggregated_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
		// medição
		output << iteration << " " << max_repetitions << " " << aggregated_time.count() << " " << bh.get_nro_swaps() << endl;
		//bh.print_heap();
	}
}

void measure_delete(ofstream& output){
	random_device rd;		
	mt19937 mt(rd());

	output << "i T(i) D(i)" << endl;

	const int max_iterations = 21;

	for(int i = 1; i < max_iterations; i++){
		uniform_int_distribution<size_t> pick(0,pow(2,i)-1);
		NAryHeap<shared_ptr<Vertex>> bh(2, pow(2,i)-1);

		for(int x = 0; x < pow(2,i)-1; x++){
			bh.push(x, make_shared<Vertex>(0, pick(mt), 0));
		}

		bh.reset_swaps();
		unsigned int remove = pow(2,i) - 1;
		chrono::milliseconds aggregated_time(0);
		chrono::system_clock::time_point t = chrono::system_clock::now();
		while(remove--) bh.pop();
		aggregated_time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t);
		output << i << " " << aggregated_time.count() << " " << bh.get_nro_swaps() << endl;
	}
}

int main(int argc, char** argv){

	string prefix;
	if(argc > 1) prefix.append(argv[1]);

	ofstream push_file;
	ofstream update_file;
	ofstream delete_file;

	push_file.open(prefix + "push_vertex");
	update_file.open(prefix + "update_vertex");
	delete_file.open(prefix + "delete_vertex");

	cout << "Measuring push..." << endl;
	measure_push(push_file);

	cout << "Measuring update..." << endl;
	measure_update(update_file);

	cout << "Measuring deletemin..." << endl;
	measure_delete(delete_file);

	push_file.close();
	update_file.close();
	delete_file.close();
}	