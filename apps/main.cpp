#include <iostream>

#include "config.hpp"

#include "utils.hpp"

#include "graph.hpp"
#include "partitioner.hpp"
#include "metrics.hpp"

#include "benchmark.hpp"

using namespace std;

int main() {

    ProgramStatistics::InitMatchingStatistics();

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ProgramConfig::coarsening_method = ProgramConfig::CoarseningMethod::RandomMatching;

    PrintBenchmark();

    //ProgramStatistics::PrintMatchingStatistics();

    return 0;
}