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
	::testing::ValuesIn(getMtxFileNames(DATA_BASE_PATH))
);

TEST_P(MetricsCrashTest, canCountEdgeCut) {

	std::string file_name = GetParam();

	Graph<idx_t, idx_t> g(DATA_BASE_PATH + file_name, "mtx");

	idx_t* partition = new idx_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	idx_t edge_cut;

	EXPECT_NO_THROW(PartitionMetrics::getEdgeCut(g, partition, edge_cut));

	delete[] partition;
}

TEST(MetricsCountTest, getEdgeCutFullGraph) {

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

TEST(MetricsCountTest, getEdgeCutFullGraph3) {

	Graph<idx_t, idx_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx");

	idx_t* partition = new idx_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	partition[0] = 1;

	idx_t edge_cut;

	PartitionMetrics::getEdgeCut(g, partition, edge_cut);

	EXPECT_EQ(edge_cut, 4);

	delete[] partition;
}

TEST(MetricsCountTest, getEdgeCutFullGraph4) {

	Graph<idx_t, idx_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx");

	idx_t* partition = new idx_t[g.getVerticesCount()];
	std::iota(partition, partition + g.getVerticesCount(), 0);

	idx_t edge_cut;

	PartitionMetrics::getEdgeCut(g, partition, edge_cut);

	EXPECT_EQ(edge_cut, 10);

	delete[] partition;
}

TEST_P(MetricsCrashTest, canCountBalances) {

	std::string file_name = GetParam();

	Graph<idx_t, idx_t> g(DATA_BASE_PATH + file_name, "mtx");

	idx_t number_of_parts = 1;

	real_t* required_ratios = new real_t[number_of_parts];
	required_ratios[0] = 1.0;

	idx_t* partition = new idx_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	real_t* balances = new real_t[number_of_parts];

	EXPECT_NO_THROW(PartitionMetrics::getBalances(g, 1, required_ratios, partition, balances));

	delete[] balances;
	delete[] partition;
	delete[] required_ratios;
}

TEST(MetricsCountTest, getBalancesFullGraph1) {

	Graph<idx_t, idx_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx");

	idx_t number_of_parts = 1;

	real_t* required_ratios = new real_t[number_of_parts];
	required_ratios[0] = 1.0;

	idx_t* partition = new idx_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	real_t* balances = new real_t[number_of_parts];

	PartitionMetrics::getBalances(g, number_of_parts, required_ratios, partition, balances);

	EXPECT_NEAR(1.0L, balances[0], EPS);

	delete[] balances;
	delete[] partition;
	delete[] required_ratios;
}

TEST(MetricsCountTest, getBalancesFullGraph2) {

	Graph<idx_t, idx_t> g(DATA_BASE_PATH + "test_matrix1.mtx", "mtx");

	idx_t number_of_parts = 2;

	real_t* required_ratios = new real_t[number_of_parts];
	required_ratios[0] = 0.8;
	required_ratios[1] = 0.2;

	idx_t* partition = new idx_t[g.getVerticesCount()];
	std::fill(partition, partition + g.getVerticesCount(), 0);

	partition[0] = 1;

	real_t* balances = new real_t[number_of_parts];

	PartitionMetrics::getBalances(g, number_of_parts, required_ratios, partition, balances);

	EXPECT_NEAR(1.0L, balances[0], EPS);
	EXPECT_NEAR(1.0L, balances[1], EPS);

	delete[] balances;
	delete[] partition;
	delete[] required_ratios;
}