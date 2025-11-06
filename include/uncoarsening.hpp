#pragma once

#include <numeric>

#include "config.hpp"

#include "utils.hpp"
#include "graph.hpp"

#include "coarse_level.hpp"

class Uncoarser {
public:

	template <typename vw_t, typename ew_t>
	static void RestorePartition(
		const Vector<CoarseLevel<vw_t, ew_t>>& levels,
		Vector<int_t>& partition
	) {
		switch (ProgramConfig::uncoarsening_method) {
		case ProgramConfig::UncoarseningMethod::DirectMapping:
			for (int_t i = levels.size() - 1_i; i > 0_i; --i) {
				partition = Uncoarser::DirectMapping<vw_t, ew_t>(levels[i], partition);
			}
			break;

		default:
			throw std::runtime_error("Unknown uncoarsening method in ProgramConfig.");
		}
	}

	template <typename vw_t, typename ew_t>
	static Vector<int_t> DirectMapping(
		const CoarseLevel<vw_t, ew_t>& level,
		const Vector<int_t>& coarse_partition
	) {
		const int_t n = level.uncoarse_to_coarse.size();
		Vector<int_t> prev_partition(n);

		for (int_t i = 0_i; i < n; ++i) {
			prev_partition[i] = coarse_partition[level.uncoarse_to_coarse[i]];
		}

		return prev_partition;
	}
};