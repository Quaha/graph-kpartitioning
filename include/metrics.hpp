#pragma once

#include "graph.hpp"

class PartitionMetrics {
public:

	/*
	 * Calculates the total edge cut of a given graph partition.
	 *
	 * This function iterates over all edges in the graph and sums the weights
	 * of edges that connect vertices belonging to different partitions.
	 * Each undirected edge is counted only once.
	 *
	 * Parameters:
	 * - graph - the input graph for which the edge cut is computed								               | ex: ...(|V| = 3)
	 * - partition - a vector of size |V| where partition[i] indicates the part of vertex i (may be any int_t) | ex: {0, 1, 2}
	 *
	 * Returns:
	 * - EdgeWeight_t - total weight of all edges crossing partition boundaries					               | ex: ...
	 */
	template <typename VertexWeight_t, typename EdgeWeight_t>
	static EdgeWeight_t getEdgeCut(
		const Graph<VertexWeight_t, EdgeWeight_t>& graph,
		const Vector<int_t> partition
	) {
		EdgeWeight_t edge_cut = 0;

		for (int_t curr_V = 0; curr_V < graph.getVerticesCount(); ++curr_V) {
			for (auto [next_V, w]: graph[curr_V]) {
				if (curr_V < next_V && partition[curr_V] != partition[next_V]) {
					edge_cut += w;
				}
			}
		}

		return edge_cut;
	}

	/*
	 * Computes the relative balance (weight proportion) of each partition.
	 *
	 * This function calculates the total weight of all vertices in the graph
     * and then determines what fraction of that weight belongs to each part.
	 *
	 * Parameters:
	 * - graph - the input graph whose vertex weights are used for balance computation			               | ex: ...(|V| = 6);
	 * - k - the number of partitions to evaluate (equal to the number of different values in the partition)   | ex: 4
	 * - partition - a vector of size |V| where partition[i] indicates the part of vertex i (may be any int_t) | ex: {0, 1, 0, 2, 3, 1}
	 *
	 * Returns:
	 * - Vector<real_t> - output vector where i-th element stores the fraction of total weight				   | ex: {0.33, 0.33, 0.16, 0.16}
	 */
	template <typename EdgeWeight_t, typename VertexWeight_t>
	static Vector<real_t> getBalances(
		const Graph<EdgeWeight_t, VertexWeight_t>& graph,
		const int_t k,
		const Vector<int_t>& partition
	) {
		Vector<real_t> balances(k, 0.0);

		VertexWeight_t total_W = 0;
		for (int_t curr_V = 0; curr_V < graph.getVerticesCount(); curr_V++) {
			total_W += graph.vertex_weights[curr_V];
		}

		for (int_t curr_V = 0; curr_V < graph.getVerticesCount(); curr_V++) {
			balances[partition[curr_V]] += static_cast<real_t>(graph.vertex_weights[curr_V]);
		}

		for (int_t curr_V = 0; curr_V < k; curr_V++) {
			balances[curr_V] = balances[curr_V] / total_W;
		}

		return balances;
	}

	/*
	 * Computes the imbalance (accuracy) of a k-way graph partition.
	 *
	 * This function checks how evenly the vertex weights are split between
	 * parts by comparing the heaviest part to the ideal equal share (1 / k).
	 *
	 * Parameters:
	 * - graph - the input graph whose partition balance is being evaluated										   | ex: ... (|V| = 6)
	 * - k - the number of partitions used in the graph (equal to the number of different values in the partition) | ex: 4
	 * - partition - a vector of size |V| where partition[i] indicates the part of vertex i	(may be any int)	   | ex: {0, 1, 0, 2, 3, 1}
	 *
	 * Returns:
	 * - real_t - the imbalance value (difference between the heaviest part and 1/k)							   | ex: 0.0833  -> 8.33% imbalance
	 */
	template <typename VertexWeight_t, typename EdgeWeight_t>
	static real_t getAccuracy(
		const Graph<VertexWeight_t, EdgeWeight_t>& graph,
		const int_t k,
		const Vector<int_t>& partition
	) {

		Vector<real_t> balances = getBalances(graph, k, partition);

		real_t accuracy = balances[0] - 1.0 / k;
		for (int_t curr_V = 1; curr_V < k; curr_V++) {
			if (balances[curr_V] - 1.0 / k > accuracy) {
				accuracy = balances[curr_V] - 1.0 / k;
			}
		}

		return accuracy;
	}
};