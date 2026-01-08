#include <gtest/gtest.h>

#include "utils.hpp" 
#include "graph.hpp"
#include "coarsening.hpp"

const std::string DATA_BASE_PATH = "..\\..\\tests\\data\\";

class CoarseTest : public ::testing::TestWithParam<std::string> {};

INSTANTIATE_TEST_SUITE_P(
    AllMtxFiles,
    CoarseTest,
    ::testing::ValuesIn(GetFileNames(DATA_BASE_PATH, ".mtx"))
);

TEST_P(CoarseTest, CoarseLevelsCompressionDecompression) {

    String file_name = GetParam();
    Graph<int_t, real_t> g(file_name, "mtx");


    Vector<CoarseLevel<int_t, real_t>> levels = Coarser::GetCoarseLevels(g, 2_i);

    EXPECT_GE(levels.size(), 1);

    for (size_t lvl = 1; lvl < levels.size(); ++lvl) {
        auto& coarse = levels[lvl].coarsed_graph;

        real_t sum_orig = 0;
        for (int_t v : GraphTester<int_t, real_t>::getVertexWeights(levels[lvl - 1].coarsed_graph)) {
            sum_orig += v;
        }

        real_t sum_coarse = 0;
        for (int_t v : GraphTester<int_t, real_t>::getVertexWeights(coarse)) {
            sum_coarse += v;
        }

        EXPECT_TRUE(std::abs(sum_orig - sum_coarse) < EPS);

        EXPECT_EQ(levels[lvl].uncoarse_to_coarse.size(), levels[lvl - 1].coarsed_graph.getVerticesCount());

        int_t total_uncoarse = 0;
        for (auto& vec : levels[lvl].coarse_to_uncoarse) {
            total_uncoarse += vec.size();
        }
        EXPECT_EQ(total_uncoarse, levels[lvl - 1].coarsed_graph.getVerticesCount());
    }
}