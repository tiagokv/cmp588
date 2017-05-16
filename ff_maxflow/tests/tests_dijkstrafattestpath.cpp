#include <limits>

#include "gtest/gtest.h"
#include "ResidualGraph.hpp"
#include "DijkstraFattestPath.hpp"

using namespace std;

TEST(DijkstraFattestPathTest, NotConnected) { 
    ResidualGraph resg(2);

    DijkstraFattestPath fat(resg, 0);

    ASSERT_EQ(0, fat.get_fattest_capacity(1) );
    ASSERT_EQ(0, fat.get_fattest_path(1).size());
}

TEST(DijkstraFattestPathTest, ConnectedSimple) { 
    ResidualGraph resg(3);

    resg.connect(0, 1, 5);
    resg.connect(1, 2, 1);

    DijkstraFattestPath fat(resg, 0);

    ASSERT_EQ( 5 , fat.get_fattest_capacity(1) );
    ASSERT_EQ( 1 , fat.get_fattest_capacity(2) );

    auto fattest_path = fat.get_fattest_path(2);

    ASSERT_EQ( 1 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 5 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
}

TEST(DijkstraFattestPathTest, ConnectedSimple2) { 
    ResidualGraph resg(4);

    resg.connect(0, 1, 10);
    resg.connect(1, 2, 1);
    resg.connect(0, 3, 5);
    resg.connect(3, 2, 4);

    DijkstraFattestPath fat(resg, 0);

    EXPECT_EQ( 4 , fat.get_pushes() );
    EXPECT_EQ( 4 , fat.get_pops() );
    EXPECT_GE( 4 , fat.get_updates() );

    ASSERT_EQ( 4, fat.get_fattest_capacity(2) );

    auto fattest_path = fat.get_fattest_path(2);
    ASSERT_EQ(2, fattest_path.size());

    ASSERT_EQ( 4 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 5 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
}

TEST(DijkstraFattestPathTest, ConnectedSimple3) { 
    ResidualGraph resg(4);

    resg.connect(0, 1, 10);
    resg.connect(1, 2, 1);
    resg.connect(0, 3, 5);
    resg.connect(3, 2, 4);
    resg.connect(1, 3, 6);

    DijkstraFattestPath fat(resg, 0);

    EXPECT_EQ( 4 , fat.get_pushes() );
    EXPECT_EQ( 4 , fat.get_pops() );
    EXPECT_GE( 5 , fat.get_updates() );

    ASSERT_EQ( 4 , fat.get_fattest_capacity(2) );

    auto fattest_path = fat.get_fattest_path(2);
    ASSERT_EQ(3, fattest_path.size());

    ASSERT_EQ( 4 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 6 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
    ASSERT_EQ( 10 , fattest_path[2]->get_capacity(fattest_path[2]->get_from()) );
}

TEST(DijkstraFattestPathTest, ConnectedSimple3WithUpdate) { 
    ResidualGraph resg(4);

    resg.connect(0, 1, 10);
    resg.connect(1, 2, 1);
    resg.connect(0, 3, 5);
    resg.connect(3, 2, 4);
    resg.connect(1, 3, 6);

    DijkstraFattestPath fat(resg, 0);

    EXPECT_EQ( 4 , fat.get_pushes() );
    EXPECT_EQ( 4 , fat.get_pops() );
    EXPECT_GE( 5 , fat.get_updates() );

    ASSERT_EQ( 4 , fat.get_fattest_capacity(2) );

    auto fattest_path = fat.get_fattest_path(2);
    ASSERT_EQ(3, fattest_path.size());

    ASSERT_EQ( 4 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 6 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
    ASSERT_EQ( 10 , fattest_path[2]->get_capacity(fattest_path[2]->get_from()) );

    auto capacity = fat.get_fattest_capacity(2);
    for(auto& edge: fattest_path){
        edge->add_flow( capacity );
    }

    DijkstraFattestPath fat1(resg, 0);

    EXPECT_EQ( 4 , fat1.get_pushes() );
    EXPECT_EQ( 4 , fat1.get_pops() );
    EXPECT_GE( 5 , fat1.get_updates() );

    ASSERT_EQ( 1 , fat1.get_fattest_capacity(2) );

    fattest_path = fat1.get_fattest_path(2);
    ASSERT_EQ(2, fattest_path.size());

    ASSERT_EQ( 1 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 6 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
}

TEST(DijkstraFattestPathTest, StopAtToConnectedSimple) { 
    ResidualGraph resg(3);

    resg.connect(0, 1, 5);
    resg.connect(1, 2, 1);

    DijkstraFattestPath fat(resg, 0, 2);

    ASSERT_EQ( 5 , fat.get_fattest_capacity(1) );
    ASSERT_EQ( 1 , fat.get_fattest_capacity() );

    auto fattest_path = fat.get_fattest_path();

    ASSERT_EQ( 1 , fattest_path[0]->get_capacity(fattest_path[0]->get_from()) );
    ASSERT_EQ( 5 , fattest_path[1]->get_capacity(fattest_path[1]->get_from()) );
}

TEST(DijkstraFattestPathTest, StopAtFinalConnectedSimple1) { 
    ResidualGraph resg(4);

    resg.connect(0, 1, 10);
    resg.connect(1, 2, 1);
    resg.connect(0, 3, 5);
    resg.connect(3, 2, 4);
    resg.connect(3, 1, 6);

    DijkstraFattestPath fat(resg, 1, 2);

    ASSERT_EQ(1, fat.get_fattest_capacity());
    ASSERT_EQ(2, fat.get_pushes());
    ASSERT_EQ(2, fat.get_pops());
    ASSERT_EQ(0, fat.get_updates());
}

TEST(DijkstraFattestPathTest, StopAtFinalConnectSimple2){
    ResidualGraph resg(4);

    resg.connect(1, 0, 10);
    resg.connect(1, 2, 1);
    resg.connect(0, 3, 5);
    resg.connect(3, 2, 4);
    resg.connect(3, 1, 6);

    DijkstraFattestPath fat(resg, 1, 2);

    ASSERT_EQ(4, fat.get_fattest_capacity());
    ASSERT_EQ(4, fat.get_pushes());
    ASSERT_EQ(4, fat.get_pops());
    ASSERT_EQ(1, fat.get_updates());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}