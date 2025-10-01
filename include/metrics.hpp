#pragma once

#include "graph.hpp"

class PartitionMetrics {
private:

	static real_t getIdealSize(const int_t total_W, const int_t number_of_parts) {
		return static_cast<real_t>((total_W + number_of_parts - 1) / number_of_parts);
	}

	static real_t getIdealSize(const real_t total_W, const int_t number_of_parts) {
		return total_W / static_cast<real_t>(number_of_parts);
	}

public:
	template <typename EdgeWeight_t, typename VertexWeight_t>
	static void getEdgeCut(
		const Graph<EdgeWeight_t, VertexWeight_t>& graph,
		const Vector<int_t> partition,
		EdgeWeight_t& edge_cut
	) {
		edge_cut = 0;

		for (int_t curr_V = 0; curr_V < graph.getVerticesCount(); ++curr_V) {
			for (int_t i = graph.xadj[curr_V]; i < graph.xadj[curr_V + 1]; ++i) {
				int_t next_V = graph.adjncy[i];

				if (curr_V < next_V && partition[curr_V] != partition[next_V]) {
					edge_cut += graph.edge_weights[i];
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

		real_t ideal_size = getIdealSize(total_W, k);

		for (int_t curr_V = 0; curr_V < graph.getVerticesCount(); curr_V++) {
			balances[partition[curr_V]] += static_cast<real_t>(graph.vertex_weights[curr_V]);
		}

		for (int_t curr_V = 0; curr_V < k; curr_V++) {
			balances[curr_V] = (balances[curr_V] - ideal_size) / ideal_size;
		}
	}

	template <typename EdgeWeight_t, typename VertexWeight_t>
	static void getAccuracy(
		const Graph<EdgeWeight_t, VertexWeight_t>& graph,
		const int_t k,
		const Vector<int_t>& partition,
		real_t& accuracy
	) {

		Vector<real_t> balances(k);
		getBalances(graph, k, partition, balances);

		accuracy = balances[0];
		for (int_t curr_V = 1; curr_V < k; curr_V++) {
			if (balances[curr_V] > accuracy) {
				accuracy = balances[curr_V];
			}
		}
	}
};