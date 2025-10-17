#pragma once

#include "graph.hpp"

class PartitionMetrics {
public:
	template <typename VertexWeight_t, typename EdgeWeight_t>
	static void getEdgeCut(
		const Graph<VertexWeight_t, EdgeWeight_t>& graph,
		const Vector<int_t> partition,
		EdgeWeight_t& edge_cut
	) {
		edge_cut = 0;

		for (int_t curr_V = 0; curr_V < graph.getVerticesCount(); ++curr_V) {
			for (auto [next_V, w]: graph[curr_V]) {
				if (curr_V < next_V && partition[curr_V] != partition[next_V]) {
					edge_cut += w;
				}
			}
		}
	}

	template <typename EdgeWeight_t, typename VertexWeight_t>
	static void getBalances(
		const Graph<EdgeWeight_t, VertexWeight_t>& graph,
		const int_t k,
		const Vector<int_t>& partition,
		Vector<real_t>& balances
	) {
		balances.assign(k, 0);

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
	}

	template <typename VertexWeight_t, typename EdgeWeight_t>
	static void getAccuracy(
		const Graph<VertexWeight_t, EdgeWeight_t>& graph,
		const int_t k,
		const Vector<int_t>& partition,
		real_t& accuracy
	) {

		Vector<real_t> balances(k);
		getBalances(graph, k, partition, balances);

		accuracy = balances[0] - 1.0 / k;
		for (int_t curr_V = 1; curr_V < k; curr_V++) {
			if (balances[curr_V] - 1.0 / k > accuracy) {
				accuracy = balances[curr_V] - 1.0 / k;
			}
		}
	}
};