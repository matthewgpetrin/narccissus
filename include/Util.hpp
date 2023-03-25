// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_UTIL_HPP
#define NARCCISSUS_UTIL_HPP

#include <cmath>
#include <array>
#include <complex>
#include <iostream>
#include "Vec3.hpp"

namespace nrcc {
    // MATHEMATICAL
    double epsilon = 1e-7;

    double pi = std::numbers::pi;

    double infinity = std::numeric_limits<double>::infinity();

    std::complex<double> j = std::complex<double>(0, 1);

    double golden_angle = pi * (3 - sqrt(5));

    double golden_ratio = (1 + sqrt(5)) / 2;

    // FREESPACE CONSTANTS
    double impedance = 377;

    double lightspeed = 299792458;

    double permeability = 1.25663706e-6;

    // VECTOR UTILITIES

    template<typename T>
    Vec3<std::complex<T>> linear = {{0, 0},
                                    {0, 0},
                                    {1, 0}};

    Vec3<double> randomVector() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::default_random_engine generator(seed);

        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        double u = distribution(generator);
        double v = distribution(generator);

        double EL = std::acos(1 - 2 * u) - (pi / 2);
        double AZ = 2 * pi * v;

        return {EL, AZ};
    }
}

#endif //NARCCISSUS_UTIL_HPP