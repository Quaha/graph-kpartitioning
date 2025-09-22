#pragma once

#include "graph.hpp"

class Partitioner {

	/*
	 * This class finds the partition of a graph into a given number of parts.
	*/

public:

	template <typename EWeightType, typename VWeightType>
	static void getGraphKPartition(
		const Graph<EWeightType, VWeightType>& graph,
		const idx_t number_of_parts,
		const real_t* required_ratios,
		const real_t* acceptable_deviation,
		idx_t* partition,
		EWeightType& edge_cut
	) {

		// code

	}
};