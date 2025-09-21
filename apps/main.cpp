#include "graph.hpp"

int main() {

    spMtx<real_t> mt("../data/add20.mtx", "mtx");
    
    Graph<real_t, int_t> g(mt);

    return 0;
}