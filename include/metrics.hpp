#include "graph.hpp"

class PartitionMetrics {

	/*
	 * This class makes it possible to obtain the characteristics of a partition.
	*/

public:
	template <typename EWeightType, typename VWeightType>
	void getEdgeCut(
		const Graph<EWeightType, VWeightType>& graph,
		const idx_t* partition,
		EWeightType& edge_cut
	) {

	}

	template <typename EWeightType, typename VWeightType>
	void getImbalance(
		const Graph<EWeightType, VWeightType>& graph,
		const idx_t number_of_parts,
		const real_t* required_ratio,
		const idx_t* partition,
		real_t* imbalance
	) {

	}

	template <typename EWeightType, typename VWeightType>
	void getMaxImbalance(
		const Graph<EWeightType, VWeightType>& graph,
		const idx_t number_of_parts,
		const real_t* required_ratio,
		const idx_t* partition,
		real_t& max_imbalance
	) {

	}
};