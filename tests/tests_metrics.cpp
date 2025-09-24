#include <gtest/gtest.h>

#include "io_utils.hpp" 
#include "graph.hpp"
#include "partitioner.hpp"
#include "metrics.hpp"

const std::string DATA_BASE_PATH = "..\\..\\tests\\data\\";

class MetricsCrashTest : public ::testing::TestWithParam<std::string> {};

INSTANTIATE_TEST_SUITE_P(
	AllMtxFiles,
	MetricsCrashTest,
	::testing::ValuesIn(getMtxFileNames(DATA_BASE_PATH))
);

TEST_P(MetricsCrashTest, canCountEdgeCut1) {

	std::string file_name = GetParam();

	Graph<idx_t, idx_t> g(DATA_BASE_PATH + file_name, "mtx");

	idx_t* partition = new idx_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	idx_t edge_cut;

	EXPECT_NO_THROW(PartitionMetrics::getEdgeCut(g, partition, edge_cut));

	delete[] partition;
}

TEST(MetricsCountTest, getEdgeCutFullGraph1) {

	Graph<idx_t, idx_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx");

	idx_t* partition = new idx_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	idx_t edge_cut;

	PartitionMetrics::getEdgeCut(g, partition, edge_cut);

	EXPECT_EQ(edge_cut, 0);

	delete[] partition;
}

TEST(MetricsCountTest, getEdgeCutFullGraph2) {

	Graph<idx_t, idx_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx");

	idx_t* partition = new idx_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	partition[0] = 1;
	partition[1] = 1;

	idx_t edge_cut;

	PartitionMetrics::getEdgeCut(g, partition, edge_cut);

	EXPECT_EQ(edge_cut, 6);

	delete[] partition;
}