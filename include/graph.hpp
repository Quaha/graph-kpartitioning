#pragma once

#include "matrix.hpp"
#include "utils.hpp"

class Partitioner;
class PartitionMetrics;

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
		for (int_t i = 0; i < m; ++i) {
			adjncy[i] = static_cast<int_t>(matrix.Col[i]);
		}

		xadj.resize(n + 1);
		for (int_t i = 0; i < n + 1; ++i) {
			xadj[i] = static_cast<int_t>(matrix.Rst[i]);
		}

		vertex_weights.resize(n);
		for (int_t i = 0; i < n; ++i) {
			vertex_weights[i] = 1;
		}

		edge_weights.resize(m);
		if (matrix.Val != nullptr && !ignore_eweights) {
			for (int_t i = 0; i < m; ++i) {
				edge_weights[i] = matrix.Val[i];
			}
		}
		else {
			for (int_t i = 0; i < m; ++i) {
				edge_weights[i] = 1;
			}
		}
	}

public:

	// Requires symmetric matrix
	Graph(const spMtx<EdgeWeight_t>& matrix, bool ignore_eweights = false) {
		buildGraph(matrix, ignore_eweights);
	}

	// Requires symmetric matrix
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

	void printEdges() const {
		for (int_t u = 0; u < n; ++u) {
			for (int_t i = xadj[u]; i < xadj[u + 1]; ++i) {
				int_t v = adjncy[i];
				EdgeWeight_t w = edge_weights[i];
				std::cout << u << " " << v << " " << w << "\n";
			}
		}
	}
};