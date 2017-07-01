#include "gtest/gtest.h"

#include "tsp_aprox_christofides.hpp"

using namespace boost;
using namespace std;

/*
	OneByOne: Two vertices connected by one edge
	ThreeByThree: Three vertices, full connected
	FourByFour: Four vertices, full connected 
*/

TEST(MSTPrimTest, OneByOne){
	TSPGraph graph(2);

	EdgeInformation edgeProp {10};
	auto edge = add_edge(0, 1, edgeProp, graph);
	auto edges = prim_mst(graph);

	ASSERT_EQ(1, edges.size());
	ASSERT_EQ(0, source(edges[0], graph));
	ASSERT_EQ(1, target(edges[0], graph));
}

TEST(MSTPrimTest, ThreeByThree){
	TSPGraph graph(3);

	EdgeInformation edgeProp1{1}, edgeProp2{5}, edgeProp3{2};
	add_edge(0, 1, edgeProp1, graph);
	add_edge(1, 2, edgeProp3, graph);
	add_edge(0, 2, edgeProp2, graph);

	auto edges = prim_mst(graph);

	ASSERT_EQ(2, edges.size());
	ASSERT_EQ(0, source(edges[0], graph));
	ASSERT_EQ(1, target(edges[0], graph));

	ASSERT_EQ(1, source(edges[1], graph));
	ASSERT_EQ(2, target(edges[1], graph));
}

TEST(MSTPrimTest, FiveByFive){
	TSPGraph graph(5);

	EdgeInformation edgeProp1{1}, 
					edgeProp2{5}, 
					edgeProp3{2},
					edgeProp4{2},
					edgeProp5{3},
					edgeProp6{1},
					edgeProp7{3};

	add_edge(0, 1, edgeProp1, graph);
	add_edge(1, 2, edgeProp3, graph);
	add_edge(0, 2, edgeProp2, graph);

	add_edge(2, 3, edgeProp4, graph);
	add_edge(1, 3, edgeProp5, graph);
	add_edge(3, 4, edgeProp6, graph);
	add_edge(2, 4, edgeProp7, graph);

	auto edges = prim_mst(graph);

	ASSERT_EQ(4, edges.size());
	ASSERT_EQ(0, source(edges[0], graph));
	ASSERT_EQ(1, target(edges[0], graph));

	ASSERT_EQ(1, source(edges[1], graph));
	ASSERT_EQ(2, target(edges[1], graph));

	ASSERT_EQ(2, source(edges[2], graph));
	ASSERT_EQ(3, target(edges[2], graph));

	ASSERT_EQ(3, source(edges[3], graph));
	ASSERT_EQ(4, target(edges[3], graph));	
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}