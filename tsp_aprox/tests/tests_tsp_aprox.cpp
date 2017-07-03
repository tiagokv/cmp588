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

TEST(TSPAproxChristofidesTests, SixVertices){

	TSPGraph graph(6);

	enum { Arlington, Medford, Everett, Cambridge, Belmont, Somerville };

	// enum { Somerville, Arlington, Medford, Everett, Cambridge, Belmont };
	add_edge(Somerville, Arlington, EdgeInformation{10}, graph);
	add_edge(Somerville, Medford, EdgeInformation{9}, graph);
	add_edge(Somerville, Everett, EdgeInformation{6}, graph);
	add_edge(Somerville, Cambridge, EdgeInformation{10}, graph);
	add_edge(Somerville, Belmont, EdgeInformation{9}, graph);

	add_edge(Arlington, Medford, EdgeInformation{11}, graph);
	add_edge(Arlington, Everett, EdgeInformation{14}, graph);
	add_edge(Arlington, Cambridge, EdgeInformation{15}, graph);
	add_edge(Arlington, Belmont, EdgeInformation{10}, graph);

	add_edge(Medford, Everett, EdgeInformation{9}, graph);
	add_edge(Medford, Cambridge, EdgeInformation{16}, graph);
	add_edge(Medford, Belmont, EdgeInformation{15}, graph);

	add_edge(Everett, Cambridge, EdgeInformation{11}, graph);
	add_edge(Everett, Belmont, EdgeInformation{13}, graph);

	add_edge(Cambridge, Belmont, EdgeInformation{8}, graph);	

	auto path = tsp_aprox_christofides<minweight_perfect_matching>(graph);
	ASSERT_EQ(55, path);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}