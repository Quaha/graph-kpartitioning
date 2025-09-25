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

    std::string file_name = GetParam();

    spMtx<real_t> matrix(file_name.c_str(), "mtx");

    EXPECT_NO_THROW((Graph<real_t, int_t>(matrix)));
}

TEST_P(GraphTest, canCreateGraphFromSPMTXWithoutEdges) {

    std::string file_name = GetParam();

    spMtx<real_t> matrix(file_name.c_str(), "mtx");

    EXPECT_NO_THROW((Graph<real_t, int_t>(matrix, true)));
}

TEST_P(GraphTest, canCreateGraphFromMTXFileWithEdges) {

    std::string file_name = GetParam();

    EXPECT_NO_THROW((Graph<real_t, int_t>(file_name, "mtx")));
}

TEST_P(GraphTest, canCreateGraphFromMTXFileWithoutEdges) {

    std::string file_name = GetParam();

    EXPECT_NO_THROW((Graph<real_t, int_t>(file_name, "mtx", true)));
}