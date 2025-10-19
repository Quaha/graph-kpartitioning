#pragma once

#include "utils.hpp"

struct ProgramConfig {
    // --- Coarsening options ---
    enum class CoarseningMethod {
        RandomMatching,
        HeavyEdgeMatching,
        LightEdgeMatching,
    };

    // --- Partitioning options ---
    enum class PartitioningMethod {
        GGA,
    };

    // --- Global parameters ---
    inline static CoarseningMethod coarsening_method = CoarseningMethod::HeavyEdgeMatching;
    inline static PartitioningMethod partitioning_method = PartitioningMethod::GGA;

    inline static real_t accuracy = 0.05;

    inline static int_t coarsening_itarations_limit = 40;
    inline static int_t coarsening_vertix_count_limit = 16;
};
