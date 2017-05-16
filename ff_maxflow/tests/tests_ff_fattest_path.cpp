
#include "gtest/gtest.h"
#include "FordFulkersonFattestPath.hpp"
#include "DimacsReader.hpp"

TEST(FFFattestPathTests, SimpleGraph){
    // ResidualGraph resg(10);

    // resg.connect(0, 1, 10);
    // resg.connect(1, 2, 6);

    // FordFulkersonFattestPath fffat(resg, 0, 2);

    // ASSERT_EQ(6, fffat.get_max_flow());
    // ASSERT_EQ(1, fffat.get_iterations());
}

// TEST(FFFattestPathTests, SimpleGraph1){
//     ResidualGraph resg(4);

//     resg.connect(0, 1, 10);
//     resg.connect(1, 2, 1);
//     resg.connect(0, 3, 5);
//     resg.connect(3, 2, 4);
//     resg.connect(1, 3, 6);

//     FordFulkersonFattestPath fffat(resg, 0, 2);

//     ASSERT_EQ(5, fffat.get_max_flow());
// }

// TEST(FFFattestPathTests, SimpleGraph2){
//     ResidualGraph resg(4);

//     resg.connect(1, 0, 10);
//     resg.connect(1, 2, 1);
//     resg.connect(0, 3, 5);
//     resg.connect(3, 2, 4);
//     resg.connect(3, 1, 6);

//     FordFulkersonFattestPath fffat(resg, 0, 2);

//     ASSERT_EQ(5, fffat.get_max_flow());    
// }

TEST(FFFattestPathTests, AssertionCorrectValue){
    DimacsReader direader;

    size_t source, target;
    auto graph = direader.read_max_flow_graph("mesh_4_4_fake.gr", source, target);

    FordFulkersonFattestPath fffat(*graph, source, target);

    ASSERT_EQ(130, fffat.get_max_flow());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}