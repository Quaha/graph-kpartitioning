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
	void getCoarseLevels(
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

		levels.resize(total_iterations + 1);

		levels[0] = std::move(start_level);

		int_t iteration = 1;

		for (; iteration <= total_iterations && levels[iteration - 1].coarsed_graph.n >= vertices_count; iteration++) {

			CoarseLevel<VertexWeight_t, EdgeWeight_t> new_level;
			randomMatching(levels[iteration - 1].coarsed_graph, new_level);

			levels[iteration] = std::move(new_level);
		}

		levels.resize(iteration);
	}

	template <typename EdgeWeight_t, typename VertexWeight_t>
	void randomMatching(
		const Graph<VertexWeight_t, EdgeWeight_t>& graph,
		CoarseLevel<VertexWeight_t, EdgeWeight_t>& new_level
	) {

		Vector<int_t> permutation = getRandomPermutation(graph.n);

		// 1. Creating matching

		Vector<int_t> matching(graph.n, -1);
		for (int_t curr_V: permutation) {
			if (matching[curr_V] != -1) continue;
			for (int_t i = graph.xadj[curr_V]; i < graph.xadj[curr_V + 1]; i++) {
				int_t next_V = graph.adjncy[i];

				if (matching[next_V] == -1) {
					matching[next_V] = curr_V;
					matching[curr_V] = next_V;
					break;
				}
			}
		}

		// 2. Filling coarse vectors

		Vector<int_t> uncoarse_to_coarse(graph.n, -1);

		int_t vertex_count = 0;

		for (int_t curr_V = 0; curr_V < graph.n; curr_V++) {
			if (uncoarse_to_coarse[curr_V] != -1) {
				continue;
			}

			int_t next_V = matching[curr_V];
			if (next_V == -1 || next_V < curr_V) {
				uncoarse_to_coarse[curr_V] = vertex_count;
			}
			else {
				uncoarse_to_coarse[curr_V] = vertex_count;
				uncoarse_to_coarse[next_V] = vertex_count;
			}
			vertex_count++;
		}

		Vector<Vector<int_t>> coarse_to_uncoarse(vertex_count);
		Vector<int_t> size_of_components(vertex_count, 0);

		uncoarse_to_coarse.assign(graph.n, -1);

		int_t coarse_idx = 0;

		for (int_t curr_V = 0; curr_V < graph.n; curr_V++) {
			if (uncoarse_to_coarse[curr_V] != -1) {
				continue;
			}

			int_t next_V = matching[curr_V];
			if (next_V == -1 || next_V < curr_V) {
				uncoarse_to_coarse[curr_V] = coarse_idx;
				size_of_components[coarse_idx] = 1;
			}
			else {
				uncoarse_to_coarse[curr_V] = coarse_idx;
				uncoarse_to_coarse[next_V] = coarse_idx;
				size_of_components[coarse_idx] = 2;
			}
			coarse_idx++;
		}

		uncoarse_to_coarse.assign(graph.n, -1);
		coarse_idx = 0;

		for (int_t i = 0; i < vertex_count; i++) {
			coarse_to_uncoarse[i].resize(size_of_components[i]);
		}

		for (int_t curr_V = 0; curr_V < graph.n; curr_V++) {
			if (uncoarse_to_coarse[curr_V] != -1) {
				continue;
			}

			int_t next_V = matching[curr_V];
			if (next_V == -1 || next_V < curr_V) {
				uncoarse_to_coarse[curr_V] = coarse_idx;
				coarse_to_uncoarse[coarse_idx][0] = curr_V;
			}
			else {
				uncoarse_to_coarse[curr_V] = coarse_idx;
				uncoarse_to_coarse[next_V] = coarse_idx;
				coarse_to_uncoarse[coarse_idx][0] = curr_V;
				coarse_to_uncoarse[coarse_idx][1] = next_V;
			}
			coarse_idx++;
		}

		// 3. Building graph

		Graph<VertexWeight_t, EdgeWeight_t> coarsed_graph;
		coarsed_graph.n = coarse_idx;
		coarsed_graph.vertex_weights.resize(coarsed_graph.n, 0);

		for (int_t curr_V = 0; curr_V < coarsed_graph.n; curr_V++) {
			for (int_t next_V : coarse_to_uncoarse[curr_V]) {
				coarsed_graph.vertex_weights[curr_V] += graph.vertex_weights[next_V];
			}
		}

		// 4. Edges
		Vector<std::unordered_map<int_t, EdgeWeight_t>> tmp_edges(coarsed_graph.n);

		for (int_t u = 0; u < coarsed_graph.n; ++u) {
			for (int_t curr_V : coarse_to_uncoarse[u]) {
				for (int_t i = graph.xadj[curr_V]; i < graph.xadj[curr_V + 1]; ++i) {
					int_t next_V = graph.adjncy[i];
					int_t v = uncoarse_to_coarse[next_V];

					if (v != u) {
						tmp_edges[u][v] += graph.edge_weights[i];
					}
				}
			}
		}

		int_t total_edges = 0;
		Vector<int_t> edge_count(coarsed_graph.n, 0);
		for (int_t u = 0; u < coarsed_graph.n; ++u) {
			edge_count[u] = tmp_edges[u].size();
			total_edges += edge_count[u];
		}

		coarsed_graph.m = total_edges;
		coarsed_graph.xadj.resize(coarsed_graph.n + 1);
		coarsed_graph.adjncy.resize(total_edges);
		coarsed_graph.edge_weights.resize(total_edges);

		int_t pos = 0;
		for (int_t curr_V = 0; curr_V < coarsed_graph.n; ++curr_V) {
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
};