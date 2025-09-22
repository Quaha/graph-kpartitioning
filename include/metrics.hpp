#pragma once

#include "graph.hpp"

class PartitionMetrics {

	/*
	 * This class makes it possible to obtain the characteristics of a partition.
	*/

public:
	template <typename EWeightType, typename VWeightType>
	static void getEdgeCut(
		const Graph<EWeightType, VWeightType>& graph,
		const idx_t* partition,
		EWeightType& edge_cut
	) {
		edge_cut = 0;

		for (idx_t u = 0; u < graph.n; ++u) {
			for (idx_t i = graph.xadj[u]; i < graph.xadj[u + 1]; ++i) {
				idx_t v = graph.adjncy[i];

				if (u < v && partition[u] != partition[v]) {
					edge_cut += graph.eweights[i];
				}
			}
		}
	}

	template <typename EWeightType, typename VWeightType>
	static void getBalances(
		const Graph<EWeightType, VWeightType>& graph,
		const idx_t number_of_parts,
		const real_t* required_ratios,
		const idx_t* partition,
		real_t* balances
	) {
		for (idx_t i = 0; i < number_of_parts; ++i) {
			balances[i] = 0;
		}

		VWeightType total_W = 0;
		for (idx_t u = 0; u < graph.n; ++u) {
			total_W += graph.vweights[u];
		}

		for (idx_t u = 0; u < graph.n; ++u) {
			balances[partition[u]] += static_cast<real_t>(graph.vweights[u]);
		}

		for (idx_t i = 0; i < number_of_parts; ++i) {
			balances[i] /= (required_ratios[i] * static_cast<real_t>(total_W)); 
		}
	}

	template <typename EWeightType, typename VWeightType>
	static void getImbalance(
		const Graph<EWeightType, VWeightType>& graph,
		const idx_t number_of_parts,
		const real_t* required_ratios,
		const idx_t* partition,
		real_t& max_imbalance,
		real_t& min_imbalance
	) {

		real_t* balances = new real_t[number_of_parts];

		getBalances(graph, number_of_parts, required_ratios, partition, balances);

		max_imbalance = balances[0];
		for (idx_t i = 1; i < number_of_parts; ++i) {
			if (balances[i] > max_imbalance) {
				max_imbalance = balances[i];
			}
		}

		min_imbalance = balances[0];
		for (idx_t i = 1; i < number_of_parts; ++i) {
			if (balances[i] < max_imbalance) {
				max_imbalance = balances[i];
			}
		}
	}
};