#pragma once

#include "utils.hpp"

#include "graph.hpp"

class Partitioner {
public:

	template <typename EdgeWeight_t, typename VertexWeight_t>
	static void getGraphKPartition(
		const Graph<EdgeWeight_t, VertexWeight_t>& graph,
		const int_t k,
		const real_t accuracy,
		Vector<int_t>& partition,
		EdgeWeight_t& edge_cut
	) {

		

	}
};