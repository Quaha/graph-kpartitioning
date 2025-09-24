#include <gtest/gtest.h>

#include "utils.hpp" 
#include "graph.hpp"

const std::string DATA_BASE_PATH = "..\\..\\tests\\data\\";

class GraphTest : public ::testing::TestWithParam<std::string> {};

INSTANTIATE_TEST_SUITE_P(
    AllMtxFiles,
    GraphTest,
    ::testing::ValuesIn(getMtxFileNames(DATA_BASE_PATH))
);

TEST_P(GraphTest, canCreateGraphFromSPMTX) {

    std::string file_name = GetParam();

    spMtx<real_t> matrix(file_name.c_str(), "mtx");

    EXPECT_NO_THROW((Graph<real_t, idx_t>(matrix)));
}

TEST_P(GraphTest, canCreateGraphFromMTXFile) {

    std::string file_name = GetParam();

    EXPECT_NO_THROW((Graph<real_t, idx_t>(file_name, "mtx")));
}