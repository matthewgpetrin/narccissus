#ifndef NARCCISSUS_NRCC_HPP
#define NARCCISSUS_NRCC_HPP

#include <cmath>
#include <iostream>
#include <complex>

namespace nrcc {
    double lightspeed = 299792458;

    double infinity = std::numeric_limits<double>::infinity();

    double pi = std::numbers::pi;

    double epsilon = 1e-9;

    std::complex<double> j = std::complex<double>(0, 1);
}

#endif //NARCCISSUS_NRCC_HPP