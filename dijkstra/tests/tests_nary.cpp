
#include <functional>

#include "gtest/gtest.h"
#include "NAryHeap.hpp"

using namespace std;

TEST(BinaryHeapTestsInt, InsertDesc) { 
	NAryHeap<int> pq(2, 10);

	EXPECT_TRUE(pq.empty());

    pq.push(0, 10);
    EXPECT_FALSE( pq.empty());
    pq.push(1, 9);
    EXPECT_FALSE( pq.empty());
    pq.push(2, 8);
    EXPECT_FALSE( pq.empty());

    ASSERT_EQ(2, pq.get_nro_swaps());

    ASSERT_EQ(2, pq.pop());
    ASSERT_EQ(1, pq.pop());
    ASSERT_EQ(0, pq.pop());
    ASSERT_EQ(true, pq.empty());
}

TEST(BinaryHeapTestsInt, InsertAsc) { 
	NAryHeap<int> pq(2, 10);

	EXPECT_TRUE(pq.empty());

    pq.push(0, 8);
    EXPECT_FALSE(pq.empty());
    pq.push(1, 9);
    EXPECT_FALSE(pq.empty());
    pq.push(2, 10);
    EXPECT_FALSE(pq.empty());

    ASSERT_EQ(0, pq.get_nro_swaps());

    ASSERT_EQ(0, pq.pop());
    ASSERT_EQ(1, pq.pop());
    ASSERT_EQ(2, pq.pop());
    ASSERT_EQ(true, pq.empty());
}

TEST(BinaryHeapTestsInt, Update){
	NAryHeap<int> pq(2, 10);
	EXPECT_TRUE(pq.empty());

    pq.push(0, 8);
    EXPECT_FALSE(pq.empty());
    pq.push(1, 9);
    EXPECT_FALSE(pq.empty());
    pq.push(2, 10);
    EXPECT_FALSE(pq.empty());

    EXPECT_EQ(0, pq.get_nro_swaps());
    pq.update(0, 11);

    ASSERT_EQ(1, pq.get_nro_swaps());

    ASSERT_EQ(1, pq.pop());
    ASSERT_EQ(2, pq.pop());
    ASSERT_EQ(0, pq.pop());
    ASSERT_EQ(true, pq.empty());
}

TEST(BinaryHeapTestsInt, UsingCompareInsertAsc){
    NAryHeap<int, greater<int>> pq(2, 10);

    for(int i = 0; i < 10; i++){
        pq.push(i , i);
    }

    for(int i = 9; i >= 0; i--){
        ASSERT_EQ(i, pq.pop());
    }
}

TEST(BinaryHeapTestsInt, UsingCompareUpdate){
    NAryHeap<int, greater<int>> pq(2, 10);

    for(int i = 0; i < 10; i++){
        pq.push(i , i);
    }

    pq.update(0, 11);
    pq.update(4, 20);

    ASSERT_EQ(4, pq.pop());
    ASSERT_EQ(0, pq.pop());
    ASSERT_EQ(9, pq.pop());
    ASSERT_EQ(8, pq.pop());
    ASSERT_EQ(7, pq.pop());
    ASSERT_EQ(6, pq.pop());
    ASSERT_EQ(5, pq.pop());
    ASSERT_EQ(3, pq.pop());
    ASSERT_EQ(2, pq.pop());
    ASSERT_EQ(1, pq.pop());
}
  
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}