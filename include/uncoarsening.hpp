#pragma once

#include <numeric>

#include "config.hpp"

#include "utils.hpp"
#include "graph.hpp"

#include "coarse_level.hpp"

class Uncoarser {
public:
	template <typename VertexWeight_t, typename EdgeWeight_t>
	static Vector<int_t> propagatePartition(
		const CoarseLevel<VertexWeight_t, EdgeWeight_t>& level,
		const Vector<int_t>& coarse_partition
	) {
		const int_t n = level.uncoarse_to_coarse.size();
		Vector<int_t> prev_partition(n);

		for (int_t i = 0; i < n; i++) {
			prev_partition[i] = coarse_partition[level.uncoarse_to_coarse[i]];
		}

		return prev_partition;
	}
};