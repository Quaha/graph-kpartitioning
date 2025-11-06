#pragma once

#include <queue>

#include "utils.hpp"
#include "graph.hpp"

class Bipartitioner {
public:

    template <typename vw_t, typename ew_t>
    static void GetGraphBipartition(
        const Graph<vw_t, ew_t>& graph,
        Vector<int_t>& partition
    ) {
        switch (ProgramConfig::bipartitioning_method) {
        case ProgramConfig::BipartitioningMethod::GraphGrowingAlgorithm:
            partition = GraphGrowingAlgorithm(graph);
            break;

        default:
            throw std::runtime_error("Unknown bipartitioning method in ProgramConfig.");
        }

	}

    template <typename vw_t, typename ew_t>
    static Vector<int_t> GraphGrowingAlgorithm(
        const Graph<vw_t, ew_t>& graph
    ) {
        const int_t n = graph.n;

        vw_t total_weight = graph.getSumOfVertexWeights();

        vw_t ideal_weight = total_weight / c<vw_t>(2);
        vw_t max_allowed = (ProgramConfig::accuracy + 1.0_r) * ideal_weight;

        Vector<int_t> best_partition;
        ew_t best_edge_cut;

        bool found = false;

        for (int_t i = 0_i; i < ProgramConfig::bipartitioning_GraphGrowingAlgorithm_launches_count; ++i) {

            Vector<int_t> partition(n, 0_i);
            Vector<bool> visited(n, false);

            std::queue<int_t> q;

            Vector<int_t> order = GetRandomPermutation(n);

            for (int_t start_V : order) {
                if (graph.vertex_weights[start_V] <= max_allowed) {
                    q.push(start_V);
                    visited[start_V] = true;
                    break;
                }
            }

            vw_t current_weight = c<vw_t>(0);

            while (!q.empty()) {
                int_t curr_V = q.front(); q.pop();

                if (current_weight + graph.vertex_weights[curr_V] > max_allowed) {
                    continue;
                }

                partition[curr_V] = 1_i;
                current_weight += graph.vertex_weights[curr_V];

                for (auto [next_V, w] : graph[curr_V]) {
                    if (!visited[next_V]) {
                        visited[next_V] = true;
                        q.push(next_V);
                    }
                }
            }

            ew_t edge_cut = PartitionMetrics::GetEdgeCut(graph, partition);

            if (!found || edge_cut < best_edge_cut) {
                found = true;
                best_partition = partition;
                best_edge_cut = edge_cut;
            }
        }
        return best_partition;
    }
};