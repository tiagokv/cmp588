#include "gtest/gtest.h"
#include "ResidualGraph.hpp"

TEST(ResidualGraphTest, Empty) { 
    ResidualGraph resg(10);

    ASSERT_EQ(0, resg.number_edges());
    ASSERT_EQ(10, resg.number_vertices());
}

TEST(ResidualGraphTest, Simple) { 
    ResidualGraph resg(2);

    resg.connect(0, 1, 10);

    ASSERT_EQ(1, resg.number_edges());
    ASSERT_EQ(2, resg.number_vertices());
    ASSERT_EQ(10, resg.get_total_capacities());
    ASSERT_EQ(10, resg.get_max_capacities());
}

TEST(ResidualGraphTest, SimpleFromSource) { 
    ResidualGraph resg(2);

    resg.connect(0, 1, 10);

    EXPECT_EQ(1, resg.number_edges());
    EXPECT_EQ(2, resg.number_vertices());

    auto adjs = resg.adjacents(0);
    EXPECT_EQ(1, adjs.size());

    auto edge = adjs[0];
    ASSERT_EQ(10, edge->get_capacity(0));
}

TEST(ResidualGraphTest, SimpleFromTarget) { 
    ResidualGraph resg(2);

    resg.connect(0, 1, 10);

    EXPECT_EQ(1, resg.number_edges());
    EXPECT_EQ(2, resg.number_vertices());

    auto adjs = resg.adjacents(1);
    EXPECT_EQ(1, adjs.size());

    auto edge = adjs[0];
    ASSERT_EQ(0, edge->get_capacity(1));
}

TEST(ResidualGraphTest, SimpleFromSourceUpdateFlow){
    ResidualGraph resg(2);

    resg.connect(0, 1, 10);

    auto adjs = resg.adjacents(0);

    auto edge = adjs[0];
    edge->add_flow(6);

    ASSERT_EQ(4, edge->get_capacity(0));
    ASSERT_EQ(6, edge->get_capacity(1));
}

TEST(ResidualGraphTest, CapacitiesValue){
    ResidualGraph resg(10);

    resg.connect(0, 1, 10);
    resg.connect(1, 2, 9);
    resg.connect(2, 3, 8);
    resg.connect(3, 4, 7);
    resg.connect(5, 6, 6);
    resg.connect(6, 7, 5);

    ASSERT_EQ(10, resg.get_max_capacities());
    ASSERT_EQ(45, resg.get_total_capacities());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}