#include <gtest/gtest.h>

#include <numeric>

#include "utils.hpp" 
#include "graph.hpp"
#include "partitioner.hpp"
#include "metrics.hpp"

const String DATA_BASE_PATH = "..\\..\\tests\\data\\";

class MetricsCrashTest : public ::testing::TestWithParam<String> {};

INSTANTIATE_TEST_SUITE_P(
	AllMtxFiles,
	MetricsCrashTest,
	::testing::ValuesIn(GetFileNames(DATA_BASE_PATH, ".mtx"))
);

TEST_P(MetricsCrashTest, canCountEdgeCut) {

	String file_name = GetParam();

	Graph<int_t, int_t> g(DATA_BASE_PATH + file_name, "mtx", true);

	Vector<int_t> partition(g.getVerticesCount(), 0);

	EXPECT_NO_THROW(PartitionMetrics::GetEdgeCut(g, partition));
}

TEST(MetricsCountTest, getEdgeCutFullGraph) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx", true);

	Vector<int_t> partition(g.getVerticesCount(), 0);
	int_t edge_cut = PartitionMetrics::GetEdgeCut(g, partition);

	EXPECT_EQ(edge_cut, 0);
}

TEST(MetricsCountTest, getEdgeCutFullGraph2) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx", true);

	Vector<int_t> partition(g.getVerticesCount(), 0);

	partition[0] = 1;
	partition[1] = 1;

	int_t edge_cut = PartitionMetrics::GetEdgeCut(g, partition);

	EXPECT_EQ(edge_cut, 6);
}

TEST(MetricsCountTest, getEdgeCutFullGraph3) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx", true);

	Vector<int_t> partition(g.getVerticesCount(), 0);
	partition[0] = 1;

	int_t edge_cut = PartitionMetrics::GetEdgeCut(g, partition);

	EXPECT_EQ(edge_cut, 4);
}

TEST(MetricsCountTest, getEdgeCutFullGraph4) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx", true);

	Vector<int_t> partition(g.getVerticesCount());
	std::iota(partition.begin(), partition.end(), 0);

	int_t edge_cut = PartitionMetrics::GetEdgeCut(g, partition);

	EXPECT_EQ(edge_cut, 10);
}

TEST_P(MetricsCrashTest, canCountBalances) {

	std::string file_name = GetParam();

	Graph<int_t, int_t> g(DATA_BASE_PATH + file_name, "mtx");

	int_t k = 1;
	Vector<int_t> partition(g.getVerticesCount(), 0);

	EXPECT_NO_THROW(PartitionMetrics::GetBalances(g, 1, partition));
}

TEST(MetricsCountTest, getBalancesFullGraph1) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx");

	int_t k = 1;
	Vector<int_t> partition(g.getVerticesCount(), 0);
	Vector<real_t> balances = PartitionMetrics::GetBalances(g, k, partition);

	EXPECT_NEAR(1.0L, balances[0], EPS);
}