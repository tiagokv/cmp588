#include "gtest/gtest.h"

#include "tsp_aprox_christofides.hpp"

using namespace boost;
using namespace std;

TEST(GreedyPerfMatachingTests, TwoVertices){
	TSPGraph graph(2);

	EdgeInformation edgeProp {10};
	add_edge(0, 1, edgeProp, graph);

	vector<TSPNode> vertices;
	vertices.push_back(vertex(0, graph));
	vertices.push_back(vertex(1, graph));

	greedy_perfect_matching gpm;
	auto edges = gpm(graph, vertices);

	ASSERT_EQ(1, edges.size());
	ASSERT_EQ(0, source(edges[0], graph));
	ASSERT_EQ(1, target(edges[0], graph));
	ASSERT_EQ(10, graph[edges[0]].weight);
}

TEST(GreedyPerfMatachingTests, FourVertices){
	TSPGraph graph(4);

	EdgeInformation edgeProp1{10},
					edgeProp2{5},
					edgeProp3{20},
					edgeProp4{10},
					edgeProp5{90},
					edgeProp6{90};

	add_edge(0, 1, edgeProp1, graph);
	add_edge(0, 2, edgeProp2, graph);
	add_edge(0, 3, edgeProp5, graph);

	add_edge(2, 1, edgeProp6, graph);
	add_edge(2, 3, edgeProp4, graph);
	
	add_edge(1, 3, edgeProp3, graph);

	vector<TSPNode> vertices;
	vertices.push_back(vertex(0, graph));
	vertices.push_back(vertex(1, graph));
	vertices.push_back(vertex(2, graph));
	vertices.push_back(vertex(3, graph));

	greedy_perfect_matching gpm;
	auto edges = gpm(graph, vertices);

	ASSERT_EQ(2, edges.size());

	ASSERT_EQ(0, source(edges[0], graph));
	ASSERT_EQ(2, target(edges[0], graph));
	ASSERT_EQ(5, graph[edges[0]].weight);

	ASSERT_EQ(1, source(edges[1], graph));
	ASSERT_EQ(3, target(edges[1], graph));
	ASSERT_EQ(20, graph[edges[1]].weight);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}