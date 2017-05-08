#include <limits>

#include "gtest/gtest.h"
#include "ResidualGraph.hpp"
#include "DijkstraFattestPath.hpp"

using namespace std;

TEST(ResidualGraphTest, NotConnected) { 
    ResidualGraph resg(2);

    DijkstraFattestPath fat(resg, 0);

    ASSERT_EQ(0.0, fat.get_fattest_capacity(1) );
}

TEST(ResidualGraphTest, ConnectedSimple) { 
    ResidualGraph resg(3);

    resg.connect(0, 1, 5.0);
    resg.connect(1, 2, 1.0);

    DijkstraFattestPath fat(resg, 0);

    ASSERT_EQ( 5.0 , fat.get_fattest_capacity(1) );
    ASSERT_EQ( 1.0 , fat.get_fattest_capacity(2) );

    auto fattest_path = fat.get_fattest_path(2);

    ASSERT_EQ( 1.0 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 5.0 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
}

TEST(ResidualGraphTest, ConnectedSimple2) { 
    ResidualGraph resg(4);

    resg.connect(0, 1, 10.0);
    resg.connect(1, 2, 1.0);
    resg.connect(0, 3, 5.0);
    resg.connect(3, 2, 4.0);

    DijkstraFattestPath fat(resg, 0);

    EXPECT_EQ( 4 , fat.get_pushes() );
    EXPECT_EQ( 4 , fat.get_pops() );
    EXPECT_GE( 4 , fat.get_updates() );

    ASSERT_EQ( 4.0 , fat.get_fattest_capacity(2) );

    auto fattest_path = fat.get_fattest_path(2);
    ASSERT_EQ(2, fattest_path.size());

    ASSERT_EQ( 4.0 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 5.0 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
}

TEST(ResidualGraphTest, ConnectedSimple3) { 
    ResidualGraph resg(4);

    resg.connect(0, 1, 10.0);
    resg.connect(1, 2, 1.0);
    resg.connect(0, 3, 5.0);
    resg.connect(3, 2, 4.0);
    resg.connect(1, 3, 6.0);

    DijkstraFattestPath fat(resg, 0);

    EXPECT_EQ( 4 , fat.get_pushes() );
    EXPECT_EQ( 4 , fat.get_pops() );
    EXPECT_GE( 5 , fat.get_updates() );

    ASSERT_EQ( 4.0 , fat.get_fattest_capacity(2) );

    auto fattest_path = fat.get_fattest_path(2);
    ASSERT_EQ(3, fattest_path.size());

    ASSERT_EQ( 4.0 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 6.0 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
    ASSERT_EQ( 10.0 , fattest_path[2]->get_capacity(fattest_path[2]->get_from()) );
}

TEST(ResidualGraphTest, ConnectedSimple3WithUpdate) { 
    ResidualGraph resg(4);

    resg.connect(0, 1, 10.0);
    resg.connect(1, 2, 1.0);
    resg.connect(0, 3, 5.0);
    resg.connect(3, 2, 4.0);
    resg.connect(1, 3, 6.0);

    DijkstraFattestPath fat(resg, 0);

    EXPECT_EQ( 4 , fat.get_pushes() );
    EXPECT_EQ( 4 , fat.get_pops() );
    EXPECT_GE( 5 , fat.get_updates() );

    ASSERT_EQ( 4.0 , fat.get_fattest_capacity(2) );

    auto fattest_path = fat.get_fattest_path(2);
    ASSERT_EQ(3, fattest_path.size());

    ASSERT_EQ( 4.0 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 6.0 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
    ASSERT_EQ( 10.0 , fattest_path[2]->get_capacity(fattest_path[2]->get_from()) );

    auto capacity = fat.get_fattest_capacity(2);
    for(auto& edge: fattest_path){
        edge->add_flow( capacity );
    }

    DijkstraFattestPath fat1(resg, 0);

    EXPECT_EQ( 4 , fat1.get_pushes() );
    EXPECT_EQ( 4 , fat1.get_pops() );
    EXPECT_GE( 5 , fat1.get_updates() );

    ASSERT_EQ( 1.0 , fat1.get_fattest_capacity(2) );

    fattest_path = fat1.get_fattest_path(2);
    ASSERT_EQ(2, fattest_path.size());

    ASSERT_EQ( 1.0 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 6.0 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}