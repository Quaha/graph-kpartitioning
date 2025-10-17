#include <gtest/gtest.h>

#include "utils.hpp" 
#include "graph.hpp"

const std::string DATA_BASE_PATH = "..\\..\\tests\\data\\";

class GraphTest : public ::testing::TestWithParam<std::string> {};

INSTANTIATE_TEST_SUITE_P(
    AllMtxFiles,
    GraphTest,
    ::testing::ValuesIn(getFileNames(DATA_BASE_PATH, "mtx"))
);

TEST_P(GraphTest, canCreateGraphFromSPMTXWithEdges) {

    String file_name = GetParam();

    spMtx<real_t> matrix(file_name.c_str(), "mtx");

    EXPECT_NO_THROW((Graph<int_t, real_t>(matrix)));
}

TEST_P(GraphTest, canCreateGraphFromSPMTXWithoutEdges) {

    String file_name = GetParam();

    spMtx<real_t> matrix(file_name.c_str(), "mtx");

    EXPECT_NO_THROW((Graph<int_t, real_t>(matrix, true)));
}

TEST_P(GraphTest, canCreateGraphFromMTXFileWithEdges) {

    String file_name = GetParam();

    EXPECT_NO_THROW((Graph<int_t, real_t>(file_name, "mtx")));
}

TEST_P(GraphTest, canCreateGraphFromMTXFileWithoutEdges) {

    String file_name = GetParam();

    EXPECT_NO_THROW((Graph<int_t, real_t>(file_name, "mtx", true)));
}

TEST(GraphTest, equalOperator) {

    Vector<int_t> weights(5, 1);

    Vector<std::tuple<int_t, int_t, int_t>> edges1;
    edges1.push_back({ 1, 2, 1 });
    edges1.push_back({ 4, 3, 1 });

    Vector<std::tuple<int_t, int_t, int_t>> edges2;
    edges2.push_back({ 3, 4, 1 });
    edges2.push_back({ 1, 2, 1 });

    Graph<int_t, int_t> g1(weights, edges1);
    Graph<int_t, int_t> g2(weights, edges2);

    EXPECT_TRUE(g1 == g2);
}