#include <iostream>

#include "utils.hpp"

#include "graph.hpp"
#include "partitioner.hpp"
#include "metrics.hpp"

#include "benchmark.hpp"

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //const int_t n = 5;

    //Vector<int_t> vertex_weights(n, 1);
    //Vector<tuple<int_t, int_t, int_t>> edges;
    //for (int_t i = 0; i < n; i++) {
    //    for (int_t j = i + 1; j < n; j++) {
    //        edges.push_back({ i, j, 1 });
    //    }
    //}

    //Graph<int_t, int_t> g(vertex_weights, edges);

    //Vector<int_t> partition;
    //int_t edge_cut;

    //Partitioner::getGraphKPartition(g, 4, 0.1, partition, edge_cut);

    //cout << "Parts: ";
    //for (int_t part : partition) {
    //    cout << part << " ";
    //}
    //cout << "\n";
    //cout << "Edge cut: " << edge_cut << "\n";

    printBenchmark(0.05);

    return 0;
}