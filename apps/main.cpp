#include <iostream>

#include "graph.hpp"
#include "partitioner.hpp"
#include "metrics.hpp"

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    spMtx<real_t> mt("../data/b1_ss.mtx", "mtx");
    
    Graph<real_t, idx_t> g(mt);

    g.print();

    real_t mb, lb;

    real_t* ratios = new real_t[1]; ratios[0] = 1.0;
    idx_t* parts = new idx_t[g.getVerticesCount()];
    for (idx_t i = 0; i < g.getVerticesCount(); ++i) {
        parts[i] = 0;
    }

    PartitionMetrics::getImbalance(g, 1, ratios, parts, mb, lb);

    std::cout << mb << " " << lb << "\n";

    return 0;
}