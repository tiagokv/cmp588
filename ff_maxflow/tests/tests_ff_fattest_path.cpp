
#include <string>

#include "gtest/gtest.h"
#include "FordFulkersonFattestPath.hpp"
#include "DimacsReader.hpp"

const std::string test_data_path = "..//tests//data//";

using ::testing::Values;
using ::testing::tuple;

TEST(FFFattestPathTests, SimpleGraph){
    ResidualGraph resg(10);

    resg.connect(0, 1, 10);
    resg.connect(1, 2, 6);

    FordFulkersonFattestPath fffat(resg, 0, 2);

    ASSERT_EQ(6, fffat.get_max_flow());
    ASSERT_EQ(1, fffat.get_iterations());
}

TEST(FFFattestPathTests, SimpleGraph1){
    ResidualGraph resg(4);

    resg.connect(0, 1, 10);
    resg.connect(1, 2, 1);
    resg.connect(0, 3, 5);
    resg.connect(3, 2, 4);
    resg.connect(1, 3, 6);

    FordFulkersonFattestPath fffat(resg, 0, 2);

    ASSERT_EQ(5, fffat.get_max_flow());
}

TEST(FFFattestPathTests, SimpleGraph2){
    ResidualGraph resg(4);

    resg.connect(1, 0, 10);
    resg.connect(1, 2, 1);
    resg.connect(0, 3, 5);
    resg.connect(3, 2, 4);
    resg.connect(3, 1, 6);

    FordFulkersonFattestPath fffat(resg, 0, 2);

    ASSERT_EQ(5, fffat.get_max_flow());    
}


typedef tuple<std::string, size_t> test_file;

class FFFatestPathTest : public ::testing::TestWithParam<test_file> {
};

TEST_P(FFFatestPathTest, AssertMaxFlowFromFile){

    auto name = ::testing::get<0>(GetParam());
    auto max_flow = ::testing::get<1>(GetParam());
    DimacsReader direader;

    size_t source, target;
    auto graph = direader.read_max_flow_graph(test_data_path + name, source, target);

    FordFulkersonFattestPath fffat(*graph, source, target);

    ASSERT_EQ(max_flow, fffat.get_max_flow());
}

INSTANTIATE_TEST_CASE_P(FFFattestPathTests, FFFatestPathTest,
                        Values(test_file("mesh_4_4_130.gr", 130),
                               test_file("mesh_4_4_438.gr", 438),
                               // test_file("basicLine_100_100_459122.gr", 459122)
                               // test_file("DExpLine_100_100_10_1000000.gr", 1000000),
                               test_file("dinicBad_100_101.gr", 101),
                               test_file("goldBad_100_100.gr", 100),
                               test_file("matching_100_100_100.gr", 100)
                               // test_file("random2Level_100_100_73099.gr", 73099)
                               // test_file("randomLevel_100_100_73099.gr", 73099)
                               // test_file("squareMesh_100_100_300000.gr", 300000) takes too long to test :)
                               ));

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}