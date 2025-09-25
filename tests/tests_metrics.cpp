#include <gtest/gtest.h>

#include <numeric>

#include "utils.hpp" 
#include "graph.hpp"
#include "partitioner.hpp"
#include "metrics.hpp"

const std::string DATA_BASE_PATH = "..\\..\\tests\\data\\";

class MetricsCrashTest : public ::testing::TestWithParam<std::string> {};

INSTANTIATE_TEST_SUITE_P(
	AllMtxFiles,
	MetricsCrashTest,
	::testing::ValuesIn(getFileNames(DATA_BASE_PATH, "mtx"))
);

TEST_P(MetricsCrashTest, canCountEdgeCut) {

	std::string file_name = GetParam();

	Graph<int_t, int_t> g(DATA_BASE_PATH + file_name, "mtx", true);

	int_t* partition = new int_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	int_t edge_cut;

	EXPECT_NO_THROW(PartitionMetrics::getEdgeCut(g, partition, edge_cut));

	delete[] partition;
}

TEST(MetricsCountTest, getEdgeCutFullGraph) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx", true);

	int_t* partition = new int_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	int_t edge_cut;

	PartitionMetrics::getEdgeCut(g, partition, edge_cut);

	EXPECT_EQ(edge_cut, 0);

	delete[] partition;
}

TEST(MetricsCountTest, getEdgeCutFullGraph2) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx", true);

	int_t* partition = new int_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	partition[0] = 1;
	partition[1] = 1;

	int_t edge_cut;

	PartitionMetrics::getEdgeCut(g, partition, edge_cut);

	EXPECT_EQ(edge_cut, 6);

	delete[] partition;
}

TEST(MetricsCountTest, getEdgeCutFullGraph3) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx", true);

	int_t* partition = new int_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	partition[0] = 1;

	int_t edge_cut;

	PartitionMetrics::getEdgeCut(g, partition, edge_cut);

	EXPECT_EQ(edge_cut, 4);

	delete[] partition;
}

TEST(MetricsCountTest, getEdgeCutFullGraph4) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx", true);

	int_t* partition = new int_t[g.getVerticesCount()];
	std::iota(partition, partition + g.getVerticesCount(), 0);

	int_t edge_cut;

	PartitionMetrics::getEdgeCut(g, partition, edge_cut);

	EXPECT_EQ(edge_cut, 10);

	delete[] partition;
}

TEST_P(MetricsCrashTest, canCountBalances) {

	std::string file_name = GetParam();

	Graph<int_t, int_t> g(DATA_BASE_PATH + file_name, "mtx");

	int_t number_of_parts = 1;

	int_t* partition = new int_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	real_t* balances = new real_t[number_of_parts];

	EXPECT_NO_THROW(PartitionMetrics::getBalances(g, 1, partition, balances));

	delete[] balances;
	delete[] partition;
}

TEST(MetricsCountTest, getBalancesFullGraph1) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx");

	int_t number_of_parts = 1;

	int_t* partition = new int_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	real_t* balances = new real_t[number_of_parts];

	PartitionMetrics::getBalances(g, number_of_parts,partition, balances);

	EXPECT_NEAR(0.0L, balances[0], EPS);

	delete[] balances;
	delete[] partition;
}

TEST(MetricsCountTest, getBalancesFullGraph2) {

	Graph<int_t, int_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx");

	int_t number_of_parts = 2;

	int_t* partition = new int_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	partition[0] = 1;

	real_t* balances = new real_t[number_of_parts];

	PartitionMetrics::getBalances(g, number_of_parts, partition, balances);

	EXPECT_NEAR(1.0L / 3.0L, balances[0], EPS);
	EXPECT_NEAR(- 2.0L / 3.0L, balances[1], EPS);

	delete[] balances;
	delete[] partition;
}