#pragma once

#include <iostream>

#include "graph.hpp"
#include "partitioner.hpp"
#include "metrics.hpp"

#include "utils.hpp"

void printBenchmark(const real_t accuracy) {

    const String base_folder = "../data";
    const String format = ".mtx";
    const Vector<String> files = getFileNames(base_folder, format);

    Vector<int_t> ks;

    ks.push_back(2);
    ks.push_back(4);
    ks.push_back(8);
    ks.push_back(16);
    ks.push_back(32);
    ks.push_back(64);

    std::cout << "accuracy (imbalance): " << accuracy * 100 << "%" << "\n";

    for (const auto& path : files) {
        String filename = std::filesystem::path(path).filename().string();

        std::cout << "==============================================\n";
        std::cout << "Graph: " << filename << "\n";

        Graph<int_t, real_t> g(path, "mtx", true);

        for (int_t k : ks) {
            Vector<int_t> partition;
            real_t edge_cut = 0;

            Partitioner::getGraphKPartition(g, k, 0.05, partition, edge_cut);
            real_t real_accuracy = PartitionMetrics::getAccuracy(g, k, partition);

            std::cout << "k = " << k << " | edge cut = " << edge_cut << " | real imbalance = " << real_accuracy * 100 << "%" << "\n";
        }
    }
}
