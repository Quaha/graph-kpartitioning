#pragma once

#include <numeric>

#include "utils.hpp"
#include "graph.hpp"

class Coarser {
public:

	template <typename VertexWeight_t, typename EdgeWeight_t>
	struct CoarseLevel {
		Vector<int_t> uncoarse_to_coarse;
		Vector<Vector<int_t>> coarse_to_uncoarse;
		Graph<VertexWeight_t, EdgeWeight_t> coarsed_graph;
	};

	template <typename VertexWeight_t, typename EdgeWeight_t>
	void static getCoarseLevels(
		const Graph<VertexWeight_t, EdgeWeight_t>& graph,
		const int_t vertices_count,
		const int_t total_iterations,
		Vector<CoarseLevel<VertexWeight_t, EdgeWeight_t>>& levels
	) {
		levels.clear();

		Vector<int_t> base_uncoarse_to_coarse(graph.n);
		std::iota(base_uncoarse_to_coarse.begin(), base_uncoarse_to_coarse.end(), 0);

		Vector<Vector<int_t>> base_coarse_to_uncoarse(graph.n);
		for (int_t i = 0; i < graph.n; i++) {
			base_coarse_to_uncoarse[i] = Vector<int_t>(1, i);
		}

		CoarseLevel<VertexWeight_t, EdgeWeight_t> start_level(base_uncoarse_to_coarse, base_coarse_to_uncoarse, graph);

		levels.reserve(total_iterations + 1);
		levels.push_back(start_level);

		for (int_t i = 0; i < total_iterations && levels[i].coarsed_graph.n > vertices_count; i++) {

			CoarseLevel<VertexWeight_t, EdgeWeight_t> new_level;
			randomMatching(levels[i].coarsed_graph, new_level);
			levels.push_back(new_level);
		}
	}

	template <typename EdgeWeight_t, typename VertexWeight_t>
	void static randomMatching(
		const Graph<VertexWeight_t, EdgeWeight_t>& graph,
		CoarseLevel<VertexWeight_t, EdgeWeight_t>& new_level
	) {

		Vector<int_t> permutation = getRandomPermutation(graph.n);

		// 1. Creating matching

		Vector<int_t> matching(graph.n, -1);
		for (int_t curr_V: permutation) {
			if (matching[curr_V] != -1) continue;
			for (auto [next_V, w]: graph[curr_V]) {
				if (matching[next_V] == -1) {
					matching[next_V] = curr_V;
					matching[curr_V] = next_V;
					break;
				}
			}
		}

		// 2. Filling coarse vectors

		Vector<int_t> uncoarse_to_coarse(graph.n, -1);

		Vector<Vector<int_t>> coarse_to_uncoarse;
		coarse_to_uncoarse.reserve(graph.n / 2 + 1);

		int_t vertex_count = 0;

		for (int_t curr_V = 0; curr_V < graph.n; curr_V++) {
			if (uncoarse_to_coarse[curr_V] != -1) continue;

			int_t next_V = matching[curr_V];
			Vector<int_t> component;

			if (next_V == -1) {
				uncoarse_to_coarse[curr_V] = vertex_count;
				component.push_back(curr_V);
			}
			else if (curr_V < next_V) {
				uncoarse_to_coarse[curr_V] = vertex_count;
				uncoarse_to_coarse[next_V] = vertex_count;
				component.push_back(curr_V);
				component.push_back(next_V);
			}

			coarse_to_uncoarse.push_back(std::move(component));
			vertex_count++;
		}

		// 3. Building graph

		Graph<VertexWeight_t, EdgeWeight_t> coarsed_graph;
		coarsed_graph.n = coarse_to_uncoarse.size();
		coarsed_graph.vertex_weights.resize(coarsed_graph.n, 0);

		for (int_t curr_V = 0; curr_V < coarsed_graph.n; curr_V++) {
			for (int_t next_V : coarse_to_uncoarse[curr_V]) {
				coarsed_graph.vertex_weights[curr_V] += graph.vertex_weights[next_V];
			}
		}

		// 4. Edges
		Vector<std::unordered_map<int_t, EdgeWeight_t>> tmp_edges(coarsed_graph.n);

		for (int_t c_curr_V = 0; c_curr_V < coarsed_graph.n; c_curr_V++) {
			for (int_t u_curr_V : coarse_to_uncoarse[c_curr_V]) {
				for (auto [u_next_V, w] : graph[u_curr_V]) {
					int_t c_next_V = uncoarse_to_coarse[u_next_V];

					if (c_next_V != c_curr_V) {
						tmp_edges[c_curr_V][c_next_V] += w;
					}
				}
			}
		}

		int_t total_edges = 0;
		Vector<int_t> edge_count(coarsed_graph.n, 0);
		for (int_t i = 0; i < coarsed_graph.n; i++) {
			edge_count[i] = tmp_edges[i].size();
			total_edges += edge_count[i];
		}

		coarsed_graph.m = total_edges;
		coarsed_graph.xadj.resize(coarsed_graph.n + 1);
		coarsed_graph.adjncy.resize(total_edges);
		coarsed_graph.edge_weights.resize(total_edges);

		int_t pos = 0;
		for (int_t curr_V = 0; curr_V < coarsed_graph.n; curr_V++) {
			coarsed_graph.xadj[curr_V] = pos;
			for (auto& [next_V, weight] : tmp_edges[curr_V]) {
				coarsed_graph.adjncy[pos] = next_V;
				coarsed_graph.edge_weights[pos] = weight;
				pos++;
			}
		}
		coarsed_graph.xadj[coarsed_graph.n] = pos;

		// 5. Results

		new_level.uncoarse_to_coarse = std::move(uncoarse_to_coarse);
		new_level.coarse_to_uncoarse = std::move(coarse_to_uncoarse);
		new_level.coarsed_graph = std::move(coarsed_graph);
	}

	template <typename VertexWeight_t, typename EdgeWeight_t>
	static Vector<int_t> propagatePartition(
		const CoarseLevel<VertexWeight_t, EdgeWeight_t>& level,
		const Vector<int_t>& coarse_partition
	) {
		const int_t n = level.uncoarse_to_coarse.size();
		Vector<int_t> prev_partition(n);

		for (int_t i = 0; i < n; i++) {
			prev_partition[i] = coarse_partition[level.uncoarse_to_coarse[i]];
		}

		return prev_partition;
	}
};