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
		const int_t k,
		const real_t accuracy,
		int_t* partition,
		EWeightType& edge_cut
	) {

		// code

	}
};