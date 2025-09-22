#include <iostream>

#include "graph.hpp"

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    spMtx<real_t> mt("../data/b1_ss.mtx", "mtx");
    
    Graph<real_t, idx_t> g(mt);

    g.print();

    return 0;
}