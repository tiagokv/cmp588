
#include <string>
#include <memory>
#include <cmath>

#include "gtest/gtest.h"
#include "MatchingGraph.hpp"
#include "MaximumMatching.hpp"

using namespace std;

class MaxMatchTest : public MaximumMatching {
public:
	using MaximumMatching::MaximumMatching;
	using MaximumMatching::mates;
	using MaximumMatching::dist;
	using MaximumMatching::search_paths;
};

TEST(HHMatchingTest, OneOnOne){
    auto bip = make_shared<MatchingGraph>(2);
    bip->connect(0, 1);

    MaxMatchTest hh(bip);
    ASSERT_EQ(2, hh.mates[0]);
    ASSERT_EQ(1, hh.get_cardinality());
    ASSERT_GE(sqrt(bip->number_vertices()), hh.get_phases()); //>=
}

TEST(HHMatchingTest, TwoOnTwoDiagonals){
    auto bip = make_shared<MatchingGraph>(4);

    // this will force to choose first the diagonal
    bip->connect(0, 3); 
    bip->connect(0, 2);
    bip->connect(1, 2);

    MaxMatchTest hh(bip);
    ASSERT_EQ(3, hh.mates[0] - 1);
    ASSERT_EQ(2, hh.mates[1] - 1);
    ASSERT_EQ(2, hh.get_cardinality());
    ASSERT_GE(sqrt(bip->number_vertices()), hh.get_phases()); //>=
}

TEST(HHMatchingTest, TwoOnTwo_OneDiagonalFirst){
    auto bip = make_shared<MatchingGraph>(4);

    // this will force to choose first the diagonal
    bip->connect(0, 3); 
    bip->connect(0, 2);
    bip->connect(1, 3);

    MaxMatchTest hh(bip);
    ASSERT_EQ(2, hh.mates[0] - 1);
    ASSERT_EQ(3, hh.mates[1] - 1);
    ASSERT_EQ(2, hh.get_cardinality());
    ASSERT_GE(sqrt(bip->number_vertices()), hh.get_phases()); //>=
}

TEST(HHMatchingTest, ThreeOnThree_FullConnection){
    auto bip = make_shared<MatchingGraph>(6);

    // Full Connection
    bip->connect(1,4);
	bip->connect(0,5);
	bip->connect(0,3);
	bip->connect(2,3);
	bip->connect(0,4);
	bip->connect(1,3);
	bip->connect(2,5);
	bip->connect(2,4);
	bip->connect(1,5);

    MaxMatchTest hh(bip);
    ASSERT_EQ(3, hh.get_cardinality());

    ASSERT_EQ(5, hh.mates[0] - 1);
    ASSERT_EQ(4, hh.mates[1] - 1);
    ASSERT_EQ(3, hh.mates[2] - 1);

    ASSERT_GE(sqrt(bip->number_vertices()), hh.get_phases()); //>=
}

TEST(HHMatchingTest, ThreeOnThree_NotFullConnection){
    auto bip = make_shared<MatchingGraph>(6);

    // Connection from 2 -> 3 is missing
    bip->connect(1,4);
    bip->connect(0,5);
    bip->connect(0,3);
    bip->connect(0,4);
    bip->connect(1,3);
    bip->connect(2,5);
    bip->connect(2,4);
    bip->connect(1,5);

    MaxMatchTest hh(bip);
    ASSERT_EQ(3, hh.get_cardinality());

    ASSERT_EQ(3, hh.mates[0] - 1);
    ASSERT_EQ(4, hh.mates[1] - 1);
    ASSERT_EQ(5, hh.mates[2] - 1);

    ASSERT_GE(sqrt(bip->number_vertices()), hh.get_phases()); //>=
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}