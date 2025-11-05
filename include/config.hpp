#pragma once

#include "utils.hpp"

struct ProgramConfig {
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
    inline static real_t accuracy = 0.05;

    // --- Coarsening parameters ---
    inline static CoarseningMethod coarsening_method = CoarseningMethod::HeavyEdgeMatching;

    inline static int_t coarsening_itarations_limit = 40;
    inline static int_t coarsening_vertix_count_limit = 50;

    // --- Bipartitioning parameters ---
    inline static BipartitioningMethod bipartitioning_method = BipartitioningMethod::GraphGrowingAlgorithm;

    inline static int_t bipartitioning_GraphGrowingAlgorithm_launches_count = 10;

    // --- Uncoarsening parameters ---
	inline static UncoarseningMethod uncoarsening_method = UncoarseningMethod::DirectMapping;   
};
