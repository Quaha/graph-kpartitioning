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
    };

    // --- Uncoarsening methods ---
    enum class UncoarseningMethod {
        DirectMapping,
    };

    // --- Global parameters ---
    inline real_t accuracy = 0.05_r;

    // --- Coarsening parameters ---
    inline CoarseningMethod coarsening_method = CoarseningMethod::HeavyEdgeMatching;

    inline int_t coarsening_itarations_limit = 40_i;
    inline int_t coarsening_vertix_count_limit = 50_i;

    // --- Bipartitioning parameters ---
    inline BipartitioningMethod bipartitioning_method = BipartitioningMethod::GraphGrowingAlgorithm;

    inline int_t bipartitioning_GraphGrowingAlgorithm_launches_count = 10_i;

    // --- Uncoarsening parameters ---
	inline UncoarseningMethod uncoarsening_method = UncoarseningMethod::DirectMapping;   
}
