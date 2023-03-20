
#include "include/Wave.hpp"

int main() {

    Wave<double> w1 = {{0, 0, 0}, {0, 1, 1}, 1, nrcc::pi / 4, 2.4e9};

    std::cout << "{" << w1.eField(5)[0] << "," << w1.eField(5)[1] << ", " << w1.eField(5)[2] << "}\n";
    std::cout << "{" << w1.mField(6)[0] << "," << w1.mField(6)[1] << ", " << w1.mField(6)[2] << "}\n";
}