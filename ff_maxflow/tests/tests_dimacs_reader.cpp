
#include <string>
#include <sstream>

#include "gtest/gtest.h"
#include "ResidualGraph.hpp"
#include "DimacsReader.hpp"

using namespace std;

TEST(DimacsReaderTests,NoComments){
	string input = "p max 2 1\n" 
				   "n 1 s\n"
				   "n 2 t\n"
				   "a 1 2 10\n";

	istringstream linestr;
	linestr.str(input);

	DimacsReader dr;

	size_t source, target;
	auto resg = dr.read_max_flow_graph(linestr, source, target);

	ASSERT_EQ(0, source);
	ASSERT_EQ(1, target);
	ASSERT_EQ(2, resg->number_vertices());
	ASSERT_EQ(1, resg->number_edges());
	
	auto edge = resg->adjacents(0)[0];
	ASSERT_EQ(10.0, edge->get_capacity(0));
}

TEST(DimacsReaderTests,WithComments){
	string input = "c define problem\n" 
				   "p max 3 3\n"
				   "c source\n" 
				   "n 1 s\n"
				   "c target\n"
				   "n 3 t\n"
				   "c comes edges\n"
				   "a 1 2 10\n"
				   "a 2 3 1\n"
				   "a 3 1 5\n";

	istringstream linestr;
	linestr.str(input);

	DimacsReader dr;

	size_t source, target;
	auto resg = dr.read_max_flow_graph(linestr, source, target);

	ASSERT_EQ(0, source);
	ASSERT_EQ(2, target);
	ASSERT_EQ(3, resg->number_vertices());
	ASSERT_EQ(3, resg->number_edges());
	
	auto edge = resg->adjacents(0)[0];
	ASSERT_EQ(10.0, edge->get_capacity(0));

	edge = resg->adjacents(1)[1];
	ASSERT_EQ(1.0, edge->get_capacity(1));

	edge = resg->adjacents(2)[1];
	ASSERT_EQ(5.0, edge->get_capacity(2));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}