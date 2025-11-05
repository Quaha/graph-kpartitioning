#pragma once

#include "utils.hpp"
#include "graph.hpp"

template <typename VertexWeight_t, typename EdgeWeight_t>
struct CoarseLevel {
	Vector<int_t> uncoarse_to_coarse;
	Vector<Vector<int_t>> coarse_to_uncoarse;
	Graph<VertexWeight_t, EdgeWeight_t> coarsed_graph;
	Vector<EdgeWeight_t> vertex_importance;
};