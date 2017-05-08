#include <limits>

#include "gtest/gtest.h"
#include "Graph.hpp"
#include "Dijkstra.hpp"

using namespace std;

TEST(DijkstraTests, NotConnected){
	Graph g;
	g.reserve(2);

	Dijkstra d(g, 0);

	ASSERT_EQ(numeric_limits<int>::max(), d.get_shortest_distance(1));
}

TEST(DijkstraTests, Simple) { 
    Graph g;
    g.reserve(4);

    g.connect(0, 1, 5);
    g.connect(0, 2, 2);
    g.connect(1, 3, 1);
    g.connect(2, 3, 10);

    Dijkstra d(g, 0);

    ASSERT_EQ(6, d.get_shortest_distance(3));
}
 
TEST(DijkstraTests, ForceWorstCase) { 
    Graph g;
    g.reserve(4);

    g.connect(0, 1, 1);
    g.connect(0, 2, 3);
    g.connect(0, 3, 5);
    g.connect(1, 2, 1);
    g.connect(1, 3, 3);
    g.connect(2, 3, 1);

    Dijkstra d(g, 0);

    EXPECT_EQ(4, d.get_pops());
    EXPECT_EQ(4, d.get_pushes());
    EXPECT_EQ(3, d.get_updates());

    ASSERT_EQ(3, d.get_shortest_distance(3));
}
 
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}