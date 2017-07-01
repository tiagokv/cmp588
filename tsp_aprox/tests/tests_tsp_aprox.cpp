#include "gtest/gtest.h"

#include "tsp_aprox_christofides.hpp"

using namespace boost;
using namespace std;

TEST(TSPAproxChristofidesTests, FiveVertices){
	TSPGraph graph(5);

	vector<TSPEdge> edges;
	EdgeInformation edgeProp1{1};

	edges.push_back(add_edge(0, 1, EdgeInformation{24}, graph).first);
	edges.push_back(add_edge(0, 2, EdgeInformation{13}, graph).first);
	edges.push_back(add_edge(0, 3, EdgeInformation{13}, graph).first);
	edges.push_back(add_edge(0, 4, EdgeInformation{22}, graph).first);

	edges.push_back(add_edge(1, 2, EdgeInformation{22}, graph).first);
	edges.push_back(add_edge(1, 3, EdgeInformation{13}, graph).first);
	edges.push_back(add_edge(1, 4, EdgeInformation{13}, graph).first);

	edges.push_back(add_edge(2, 3, EdgeInformation{19}, graph).first);
	edges.push_back(add_edge(2, 4, EdgeInformation{14}, graph).first);

	edges.push_back(add_edge(4, 3, EdgeInformation{19}, graph).first);

	auto path = tsp_aprox_christofides<minweight_perfect_matching>(graph);
	ASSERT_EQ(66, path);
}

TEST(TSPAproxChristofidesTests, subsetTriangle){


}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}