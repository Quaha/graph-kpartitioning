#include "matrix.hpp"

int main() {

    spMtx<long double> mt("../data/add20.mtx", "mtx");
    
    mt.print_crs();

    

    return 0;
}