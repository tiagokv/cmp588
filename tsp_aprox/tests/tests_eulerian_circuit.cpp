#include "gtest/gtest.h"

#include "tsp_aprox_christofides.hpp"

using namespace boost;
using namespace std;

TEST(EulerianCircuitTests, verticesTriangle){
	TSPGraph graph(3);

	vector<TSPEdge> edges;
	EdgeInformation edgeProp{1};
	edges.push_back(add_edge(0, 1, edgeProp, graph).first);
	edges.push_back(add_edge(1, 2, edgeProp, graph).first);
	edges.push_back(add_edge(2, 0, edgeProp, graph).first);

	auto response = euler_circuit(graph, edges);
	ASSERT_EQ(3, response.size());

	ASSERT_EQ(0, source(response[0], graph));
	ASSERT_EQ(1, target(response[0], graph));

	ASSERT_EQ(1, source(response[1], graph));
	ASSERT_EQ(2, target(response[1], graph));

	ASSERT_EQ(2, source(response[2], graph));
	ASSERT_EQ(0, target(response[2], graph));
}

TEST(EulerianCircuitTests, subsetVerticesTriangle){

	TSPGraph graph(4);

	vector<TSPEdge> edges;
	EdgeInformation edgeProp{1};
	edges.push_back(add_edge(0, 1, edgeProp, graph).first);
	edges.push_back(add_edge(1, 2, edgeProp, graph).first);
	edges.push_back(add_edge(2, 0, edgeProp, graph).first);
	add_edge(0, 3, edgeProp, graph);
	add_edge(1, 3, edgeProp, graph);
	add_edge(2, 3, edgeProp, graph);

	auto response = euler_circuit(graph, edges);
	ASSERT_EQ(3, response.size());

	ASSERT_EQ(0, source(response[0], graph));
	ASSERT_EQ(1, target(response[0], graph));

	ASSERT_EQ(1, source(response[1], graph));
	ASSERT_EQ(2, target(response[1], graph));

	ASSERT_EQ(2, source(response[2], graph));
	ASSERT_EQ(0, target(response[2], graph));
}

TEST(EulerianCircuitTests, example1){

	TSPGraph graph(5);

	vector<TSPEdge> edges;
	EdgeInformation edgeProp{1};
	edges.push_back(add_edge(0, 1, edgeProp, graph).first);
	edges.push_back(add_edge(1, 3, edgeProp, graph).first);
	edges.push_back(add_edge(3, 4, edgeProp, graph).first);
	edges.push_back(add_edge(4, 1, edgeProp, graph).first);
	edges.push_back(add_edge(1, 2, edgeProp, graph).first);
	edges.push_back(add_edge(2, 0, edgeProp, graph).first);

	auto response = euler_circuit(graph, edges);
	ASSERT_EQ(6, response.size());

	ASSERT_EQ(0, source(response[0], graph));
	ASSERT_EQ(1, target(response[0], graph));

	ASSERT_EQ(1, source(response[1], graph));
	ASSERT_EQ(3, target(response[1], graph));

	ASSERT_EQ(3, source(response[2], graph));
	ASSERT_EQ(4, target(response[2], graph));

	ASSERT_EQ(4, source(response[3], graph));
	ASSERT_EQ(1, target(response[3], graph));

	ASSERT_EQ(1, source(response[4], graph));
	ASSERT_EQ(2, target(response[4], graph));

	ASSERT_EQ(2, source(response[5], graph));
	ASSERT_EQ(0, target(response[5], graph));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}