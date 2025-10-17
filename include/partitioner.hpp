#pragma once

#include "utils.hpp"

#include "graph.hpp"
#include "coarsening.hpp"
#include "metrics.hpp"

#include <queue>

class Partitioner {
public:

	template <typename VertexWeight_t, typename EdgeWeight_t>
	static void getGraphKPartition(
		const Graph<VertexWeight_t, EdgeWeight_t>& graph,
		const int_t k,
		const real_t accuracy,
		Vector<int_t>& partition,
		EdgeWeight_t& edge_cut,
        const int_t VERTICES_COUNT_BORDER = 16,
        const int_t TOTAL_ITERATIONS = 40
	) {

		partition.resize(graph.n, -1);
		recursivePartition<VertexWeight_t, EdgeWeight_t>(graph, k, accuracy, partition, 0, VERTICES_COUNT_BORDER, TOTAL_ITERATIONS);

        PartitionMetrics::getEdgeCut(graph, partition, edge_cut);
	}

    template <typename VertexWeight_t, typename EdgeWeight_t>
    static void recursivePartition(
        const Graph<VertexWeight_t, EdgeWeight_t>& graph,
        const int_t k,
        const real_t accuracy,
        Vector<int_t>& partition,
        int_t offset,
        const int_t VERTICES_COUNT_BORDER,
        const int_t TOTAL_ITERATIONS
    ) {
        if (k == 1) {
            std::fill(partition.begin(), partition.end(), offset);
            return;
        }

        Vector<Coarser::CoarseLevel<VertexWeight_t, EdgeWeight_t>> levels;
        Coarser::getCoarseLevels(graph, VERTICES_COUNT_BORDER, TOTAL_ITERATIONS, levels);

        const Graph<VertexWeight_t, EdgeWeight_t>& coarse_graph = levels.back().coarsed_graph;
        Vector<int_t> coarse_partition = bisectGraphBFS(coarse_graph, accuracy);

        for (int_t i = levels.size() - 1; i > 0; i--) {
            coarse_partition = Coarser::propagatePartition<VertexWeight_t, EdgeWeight_t>(levels[i], coarse_partition);
        }

        Vector<int_t> left_part_vertices, right_part_vertices;
        for (int_t i = 0; i < graph.n; i++) {
            if (coarse_partition[i] == 0) {
                left_part_vertices.push_back(i);
            }
            else {
                right_part_vertices.push_back(i);
            }
        }

        Graph<VertexWeight_t, EdgeWeight_t> left_graph = graph.selectSubgraph(left_part_vertices);
        Graph<VertexWeight_t, EdgeWeight_t> right_graph = graph.selectSubgraph(right_part_vertices);

        int_t left_k = k / 2;
        int_t right_k = k - left_k;

        if (left_k > right_k && left_graph.n < right_graph.n) {
            std::swap(left_k, right_k);
        }

        if (left_k < right_k && left_graph.n > right_graph.n) {
            std::swap(left_k, right_k);
        }

        Vector<int_t> left_part(left_graph.n, -1);
        Vector<int_t> right_part(right_graph.n, -1);

        recursivePartition<VertexWeight_t, EdgeWeight_t>(left_graph, left_k, accuracy, left_part, offset, VERTICES_COUNT_BORDER, TOTAL_ITERATIONS);
        recursivePartition<VertexWeight_t, EdgeWeight_t>(right_graph, right_k, accuracy, right_part, offset + left_k, VERTICES_COUNT_BORDER, TOTAL_ITERATIONS);

        for (int_t i = 0; i < left_part_vertices.size(); i++) {
            partition[left_part_vertices[i]] = left_part[i];
        }

        for (int_t i = 0; i < right_part_vertices.size(); i++) {
            partition[right_part_vertices[i]] = right_part[i];
        }
    }
     
    template <typename VertexWeight_t, typename EdgeWeight_t>
    static Vector<int_t> bisectGraphBFS(
        const Graph<VertexWeight_t, EdgeWeight_t>& graph,
        real_t accuracy
    ) {
        const int_t n = graph.n;
        Vector<int_t> part(n, 0);
        Vector<bool> visited(n, false);

        real_t total_weight = 0;
        for (EdgeWeight_t w : graph.vertex_weights) {
            total_weight += w;
        }

        real_t ideal_weight = total_weight / 2.0;
        real_t max_allowed = (accuracy + 1.0) * ideal_weight;

        std::queue<int_t> q;

        for (int_t start_V = 0; start_V < n; start_V++) {
            if (graph.vertex_weights[start_V] <= max_allowed) {
                q.push(start_V);
                visited[start_V] = true;
                break;
            }
        }

        real_t current_weight = 0;

        while (!q.empty()) {
            int_t curr_V = q.front(); q.pop();

            if (current_weight + graph.vertex_weights[curr_V] > max_allowed) {
                continue;
            }

            part[curr_V] = 1;
            current_weight += graph.vertex_weights[curr_V];

            for (auto [next_V, w] : graph[curr_V]) {
                if (!visited[next_V]) {
                    visited[next_V] = true;
                    q.push(next_V);
                }
            }
        }

        return part;
    }
};