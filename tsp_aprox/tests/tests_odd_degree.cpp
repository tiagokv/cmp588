#include "gtest/gtest.h"

#include "tsp_aprox_christofides.hpp"

using namespace boost;
using namespace std;

TEST(FilterForOddDegreeVertices, TwoVertices){
	TSPGraph graph(2);

	EdgeInformation edgeProp {10};
	auto edge = add_edge(0, 1, edgeProp, graph);
	auto edges = prim_mst(graph);

	EXPECT_EQ(1, edges.size());
	EXPECT_EQ(0, source(edges[0], graph));
	EXPECT_EQ(1, target(edges[0], graph));

	auto vertices = filter_even_degrees(graph, edges);

	ASSERT_EQ(2, vertices.size());
	ASSERT_EQ(0, vertices[0]);
	ASSERT_EQ(1, vertices[1]);
}

TEST(FilterForOddDegreeVertices, ThreeVertices){
	TSPGraph graph(3);

	EdgeInformation edgeProp1{1}, edgeProp2{5}, edgeProp3{2};
	add_edge(0, 1, edgeProp1, graph);
	add_edge(1, 2, edgeProp3, graph);
	add_edge(0, 2, edgeProp2, graph);

	auto edges = prim_mst(graph);

	EXPECT_EQ(2, edges.size());
	EXPECT_EQ(0, source(edges[0], graph));
	EXPECT_EQ(1, target(edges[0], graph));

	EXPECT_EQ(1, source(edges[1], graph));
	EXPECT_EQ(2, target(edges[1], graph));

	auto vertices = filter_even_degrees(graph, edges);

	ASSERT_EQ(2, vertices.size());
	ASSERT_EQ(0, vertices[0]);
	ASSERT_EQ(2, vertices[1]);
}

TEST(FilterForOddDegreeVertices, FiveVertices){
	TSPGraph graph(5);

	EdgeInformation edgeProp1{1}, 
					edgeProp2{5}, 
					edgeProp3{2},
					edgeProp4{1},
					edgeProp5{3},
					edgeProp6{2},
					edgeProp7{1};

	add_edge(0, 1, edgeProp1, graph);
	add_edge(1, 2, edgeProp3, graph);
	add_edge(0, 2, edgeProp2, graph);

	add_edge(2, 3, edgeProp4, graph);
	add_edge(1, 3, edgeProp5, graph);
	add_edge(2, 4, edgeProp7, graph);
	add_edge(3, 4, edgeProp6, graph);

	auto edges = prim_mst(graph);

	EXPECT_EQ(4, edges.size());
	EXPECT_EQ(0, source(edges[0], graph));
	EXPECT_EQ(1, target(edges[0], graph));

	EXPECT_EQ(1, source(edges[1], graph));
	EXPECT_EQ(2, target(edges[1], graph));

	EXPECT_EQ(2, source(edges[2], graph));
	EXPECT_EQ(3, target(edges[2], graph));

	EXPECT_EQ(2, source(edges[3], graph));
	EXPECT_EQ(4, target(edges[3], graph));

	auto vertices = filter_even_degrees(graph, edges);

	ASSERT_EQ(4, vertices.size());
	ASSERT_EQ(0, vertices[0]);
	ASSERT_EQ(2, vertices[1]);
	ASSERT_EQ(3, vertices[2]);
	ASSERT_EQ(4, vertices[3]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}