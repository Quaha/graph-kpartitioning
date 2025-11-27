#include <iostream>

#include "config.hpp"

#include "utils.hpp"

#include "graph.hpp"
#include "partitioner.hpp"
#include "metrics.hpp"

#include "benchmark.hpp"

using namespace std;

int main() {

    //ProgramStatistics::InitMatchingStatistics();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ProgramConfig::coarsening_method = ProgramConfig::CoarseningMethod::HeavyCliqueMatching;
	ProgramConfig::bipartitioning_method = ProgramConfig::BipartitioningMethod::GreedyGraphGrowingAlgorithm;
	ProgramConfig::uncoarsening_method = ProgramConfig::UncoarseningMethod::KernighanLin;

	ProgramConfig::coarsening_clusterization_prohibition = false;
	ProgramConfig::coarsening_clusterization_size_factor = 0.15_r;

    ProgramConfig::coarsening_vertix_count_limit = 500_i;
    ProgramConfig::coarsening_itarations_limit = 40_i;


    ProgramConfig::accuracy = 0.01_r;

    PrintBenchmark();

    //ProgramStatistics::PrintMatchingStatistics();

    return 0;
}