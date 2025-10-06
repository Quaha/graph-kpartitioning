#pragma once

#include "matrix.hpp"
#include "utils.hpp"

#include <unordered_map>

class Partitioner;
class PartitionMetrics;
class Coarser;

class CoarseTest;

template <typename VertexWeight_t, typename EdgeWeight_t> class GraphTester;

// Graph stored in Compressed Row Storage (CRS/CSR) format.
//
// Template parameters:
//   VertexWeight_t — type of vertex weights
//   EdgeWeight_t - type of edge weights
//
template <typename VertexWeight_t, typename EdgeWeight_t>
class Graph {
	friend class Partitioner;
	friend class PartitionMetrics;
	friend class Coarser;

	friend class CoarseTest;
	friend class GraphTester<VertexWeight_t, EdgeWeight_t>;

private:
	int_t n = 0; // Number of vertices
	int_t m = 0; // Number of edges

	// Adjacency list:
	//   adjncy[xadj[u] .. xadj[u+1]-1] contains neighbors of vertex u.
	Vector<int_t> adjncy;

	// Row pointer array:
	//   xadj[u] = index in `adjncy` where adjacency of vertex u begins.
	//   Size = n + 1, with xadj[n] = m.
	Vector<int_t> xadj;

	// Vertex weights (size = n).
	Vector<VertexWeight_t> vertex_weights;

	// Edge weights (size = m).
	Vector<EdgeWeight_t> edge_weights;

private:

	void buildGraph(const spMtx<EdgeWeight_t>& matrix, bool ignore_eweights) {
		n = static_cast<int_t>(matrix.m);
		m = static_cast<int_t>(matrix.nz);

		adjncy.resize(m);
		for (int_t i = 0; i < m; i++) {
			adjncy[i] = static_cast<int_t>(matrix.Col[i]);
		}

		xadj.resize(n + 1);
		for (int_t i = 0; i < n + 1; i++) {
			xadj[i] = static_cast<int_t>(matrix.Rst[i]);
		}

		vertex_weights.resize(n);
		for (int_t i = 0; i < n; i++) {
			vertex_weights[i] = 1;
		}

		edge_weights.resize(m);
		if (matrix.Val != nullptr && !ignore_eweights) {
			for (int_t i = 0; i < m; i++) {
				edge_weights[i] = matrix.Val[i];
			}
		}
		else {
			for (int_t i = 0; i < m; i++) {
				edge_weights[i] = 1;
			}
		}
	}

	Graph() {

	}

public:

	// Requires a matrix corresponding to an undirected graph
	Graph(const spMtx<EdgeWeight_t>& matrix, bool ignore_eweights = false) {
		buildGraph(matrix, ignore_eweights);
	}

	// Requires a matrix corresponding to an undirected graph
	Graph(const String& file_name, const String& format, bool ignore_eweights = false) {
		spMtx<EdgeWeight_t> matrix(file_name.c_str(), format);
		buildGraph(matrix, ignore_eweights);
	}

	int_t getVerticesCount() const noexcept {
		return n;
	}

	int_t getEdgesCount() const noexcept {
		return m;
	}

	// This function returns a subgraph of the current graph, where
	// the vertices were mapped according to the order in vertices.
	Graph<VertexWeight_t, EdgeWeight_t> selectSubgraph(const Vector<int_t>& vertices) {
		Graph<VertexWeight_t, EdgeWeight_t> subgraph;

		std::unordered_map<int_t, int_t> original_to_sub;
		for (int_t i = 0; i < vertices.size(); i++) {
			original_to_sub[vertices[i]] = i;
		}

		subgraph.n = vertices.size();

		subgraph.vertex_weights.resize(subgraph.n);
		for (int_t i = 0; i < vertices.size(); i++) {
			subgraph.vertex_weights[i] = vertex_weights[vertices[i]];
		}

		Vector<bool> is_exist(n, false);

		for (int_t curr_V : vertices) {
			is_exist[curr_V] = true;
		}

		for (int_t curr_V = 0; curr_V < n; curr_V++) {
			for (int_t i = xadj[curr_V]; i < xadj[curr_V + 1]; i++) {
				int_t next_V = adjncy[i];

				if (is_exist[curr_V] && is_exist[next_V]) {
					subgraph.m++;
				}
			}
		}

		subgraph.adjncy.resize(subgraph.m);
		subgraph.edge_weights.resize(subgraph.m);

		subgraph.xadj.resize(subgraph.n + 1);
		subgraph.xadj[0] = 0;

		int_t edge_pos = 0;

		for (int_t i = 0; i < vertices.size(); i++) {
			int_t curr_V = vertices[i];
			subgraph.xadj[i + 1] = subgraph.xadj[i];
			for (int_t k = xadj[curr_V]; k < xadj[curr_V + 1]; k++) {
				int_t next_V = adjncy[k];

				if (is_exist[curr_V] && is_exist[next_V]) {

					int_t j = original_to_sub[next_V];

					EdgeWeight_t weight = edge_weights[k];

					subgraph.xadj[i + 1]++;
					subgraph.adjncy[edge_pos] = j;
					subgraph.edge_weights[edge_pos] = weight;

					edge_pos++;
				}
			}
		}

		return subgraph;
	}

	void printEdges() const {
		for (int_t curr_V = 0; curr_V < n; curr_V++) {
			for (int_t i = xadj[curr_V]; i < xadj[curr_V + 1]; i++) {
				int_t next_V = adjncy[i];
				EdgeWeight_t w = edge_weights[i];
				std::cout << curr_V << " " << next_V << " " << w << "\n";
			}
		}
	}
};

template <typename VertexWeight_t, typename EdgeWeight_t>
class GraphTester {
public:

	static const Vector<int_t>& getAdjncy(const Graph<VertexWeight_t, EdgeWeight_t>& g) {
		return g.adjncy;
	}

	static const Vector<int_t>& getXadj(const Graph<VertexWeight_t, EdgeWeight_t>& g) {
		return g.xadj;
	}

	static const Vector<VertexWeight_t>& getVertexWeights(const Graph<VertexWeight_t, EdgeWeight_t>& g) {
		return g.vertex_weights;
	}

	static const Vector<VertexWeight_t>& getEdgeWeights(const Graph<VertexWeight_t, EdgeWeight_t>& g) {
		return g.edge_weights;
	}

};