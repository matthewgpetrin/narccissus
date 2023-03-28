// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_UTIL_HPP
#define NARCCISSUS_UTIL_HPP

#include "Vec3.hpp"

namespace nrcc {

    // MATHEMATICAL
    double epsilon = 1e-7;

    double pi = std::numbers::pi;

    double infinity = std::numeric_limits<double>::infinity();

    std::complex<double> j = std::complex<double>(0, 1);

    double golden_angle = pi * (3 - sqrt(5));

    double golden_ratio = (1 + sqrt(5)) / 2;

    double impedance = 377;

    double lightspeed = 299792458;

    double permeability = 1.25663706e-6;

    Vec3<std::complex<double>> linear = {{0, 0},
                                         {0, 0},
                                         {1, 0}};
}

#endif //NARCCISSUS_UTIL_HPP