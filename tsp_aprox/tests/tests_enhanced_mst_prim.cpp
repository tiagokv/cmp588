#include "gtest/gtest.h"

#include "tspaprox_christofides_enhanced.hpp"

using namespace std;

/*
	OneByOne: Two vertices connected by one edge
	ThreeByThree: Three vertices, full connected
	FourByFour: Four vertices, full connected 
*/

TEST(MSTEnhancedPrimTest, OneByOne){
	GeometricGraph graph(2);

	enum {A, B};
	graph.add_vertex({A, 0.0, 0.0});
	graph.add_vertex({B, 10.0, 0.0});

	auto parents = prim_mst(graph);

	vector<size_t> answer{0,0};
	ASSERT_TRUE( parents == answer );
}

TEST(MSTEnhancedPrimTest, ThreeByThree){
	GeometricGraph graph(3);

	enum {A, B, C};
	graph.add_vertex({A, 0.0, 0.0});
	graph.add_vertex({B, 6.0, 0.0});
	graph.add_vertex({C, 6.0, 5.0});

	auto parents = prim_mst(graph);

	vector<size_t> answer{A, A, B};
	ASSERT_TRUE( parents == answer );
}

TEST(MSTEnhancedPrimTest, FiveByFive){
	GeometricGraph graph(5);

	enum { A, B, C, D, E };
	graph.add_vertex({A, 0.0, 0.0});
	graph.add_vertex({B, 8.0, 7.0});
	graph.add_vertex({C, 13.0, 12.0});
	graph.add_vertex({D, 15.0, 0.0});
	graph.add_vertex({E, 24.0, 11.0});

	auto parents = prim_mst(graph);

	vector<size_t> answer{A, A, B, B, D};
	ASSERT_TRUE( parents == answer );
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}