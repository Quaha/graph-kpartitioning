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
		const int_t* adjncy_ptr = graph.adjncy.data();
		const int_t* xadj_ptr = graph.xadj.data();
		const EdgeWeight_t* edge_weights_ptr = graph.edge_weights.data();

		const int_t* partition_ptr = partition.data();

		edge_cut = 0;

		for (int_t curr_V = 0; curr_V < graph.getVerticesCount(); ++curr_V) {
			for (int_t i = xadj_ptr[curr_V]; i < xadj_ptr[curr_V + 1]; ++i) {
				int_t next_V = adjncy_ptr[i];

				if (curr_V < next_V && partition_ptr[curr_V] != partition_ptr[next_V]) {
					edge_cut += edge_weights_ptr[i];
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

		const int_t* adjncy_ptr = graph.adjncy.data();
		const int_t* xadj_ptr = graph.xadj.data();
		const VertexWeight_t* vertex_weights_ptr = graph.vertex_weights.data();

		const int_t* partition_ptr = partition.data();
		real_t* balances_ptr = balances.data();

		VertexWeight_t total_W = 0;
		for (int_t curr_V = 0; curr_V < graph.getVerticesCount(); ++curr_V) {
			total_W += vertex_weights_ptr[curr_V];
		}

		real_t ideal_size = getIdealSize(total_W, k);

		for (int_t curr_V = 0; curr_V < graph.getVerticesCount(); ++curr_V) {
			balances_ptr[partition_ptr[curr_V]] += static_cast<real_t>(vertex_weights_ptr[curr_V]);
		}

		for (int_t curr_V = 0; curr_V < k; ++curr_V) {
			balances_ptr[curr_V] = (balances_ptr[curr_V] - ideal_size) / ideal_size;
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

		const real_t* balances_ptr = balances.data();

		accuracy = balances_ptr[0];
		for (int_t curr_V = 1; curr_V < k; ++curr_V) {
			if (balances_ptr[curr_V] > accuracy) {
				accuracy = balances_ptr[curr_V];
			}
		}
	}
};