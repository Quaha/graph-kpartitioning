#pragma once

#include "graph.hpp"

class PartitionMetrics {

	/*
	 * This class makes it possible to obtain the characteristics of a partition.
	*/

private:

	static real_t getIdealSize(const int_t total_W, const int_t number_of_parts) {
		return static_cast<real_t>((total_W + number_of_parts - 1) / number_of_parts);
	}

	static real_t getIdealSize(const real_t total_W, const int_t number_of_parts) {
		return total_W / static_cast<real_t>(number_of_parts);
	}

public:
	template <typename EWeightType, typename VWeightType>
	static void getEdgeCut(
		const Graph<EWeightType, VWeightType>& graph,
		const int_t* k,
		EWeightType& edge_cut
	) {
		edge_cut = 0;

		for (int_t u = 0; u < graph.n; ++u) {
			for (int_t i = graph.xadj[u]; i < graph.xadj[u + 1]; ++i) {
				int_t v = graph.adjncy[i];

				if (u < v && k[u] != k[v]) {
					edge_cut += graph.eweights[i];
				}
			}
		}
	}

	template <typename EWeightType, typename VWeightType>
	static void getBalances(
		const Graph<EWeightType, VWeightType>& graph,
		const int_t number_of_parts,
		const int_t* partition,
		real_t* balances
	) {
		for (int_t i = 0; i < number_of_parts; ++i) {
			balances[i] = 0;
		}

		VWeightType total_W = 0;
		for (int_t u = 0; u < graph.n; ++u) {
			total_W += graph.vweights[u];
		}

		real_t ideal_size = getIdealSize(total_W, number_of_parts);

		for (int_t u = 0; u < graph.n; ++u) {
			balances[partition[u]] += static_cast<real_t>(graph.vweights[u]);
		}

		for (int_t i = 0; i < number_of_parts; ++i) {
			balances[i] = (balances[i] - ideal_size) / ideal_size;
		}
	}

	template <typename EWeightType, typename VWeightType>
	static void getAccuracy(
		const Graph<EWeightType, VWeightType>& graph,
		const int_t number_of_parts,
		const int_t* partition,
		real_t& accuracy
	) {

		real_t* balances = new real_t[number_of_parts];

		getBalances(graph, number_of_parts, partition, balances);

		accuracy = balances[0];
		for (int_t i = 1; i < number_of_parts; ++i) {
			if (balances[i] > accuracy) {
				accuracy = balances[i];
			}
		}

		delete[] balances;
	}
};