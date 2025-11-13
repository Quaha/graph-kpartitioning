#pragma once

#include "utils.hpp"

namespace ProgramConfig {
    // --- Coarsening methods ---
    enum class CoarseningMethod {
        RandomMatching,
        LightEdgeMatching,
        HeavyEdgeMatching,
        HeavyCliqueMatching,
    };

    // --- Bipartitioning methods ---
    enum class BipartitioningMethod {
        GraphGrowingAlgorithm,
        GreedyGraphGrowingAlgorithm,
    };

    // --- Uncoarsening methods ---
    enum class UncoarseningMethod {
        DirectMapping,
        KernighanLin
    };

    // --- Global parameters ---
    inline real_t accuracy = 0.05_r;

    // --- Coarsening parameters ---
    inline CoarseningMethod coarsening_method = CoarseningMethod::HeavyEdgeMatching;

    inline int_t coarsening_itarations_limit = 40_i;
    inline int_t coarsening_vertix_count_limit = 100_i;

    inline bool coarsening_clusterization_prohibition = false;

    // --- Bipartitioning parameters ---
    inline BipartitioningMethod bipartitioning_method = BipartitioningMethod::GraphGrowingAlgorithm;

    inline int_t bipartitioning_GraphGrowingAlgorithm_launches_count = 10_i;
    inline int_t bipartitioning_GreedyGraphGrowingAlgorithm_launches_count = 10_i;

    // --- Uncoarsening parameters ---
	inline UncoarseningMethod uncoarsening_method = UncoarseningMethod::DirectMapping;   

	// --- Statistics parameters ---
	inline bool collect_mathing_statistics = false;
}
