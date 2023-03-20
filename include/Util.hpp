// Copyright(c) 2023, Matthew Petrin, All rights reserved.
//

#ifndef NARCCISSUS_UTIL_HPP
#define NARCCISSUS_UTIL_HPP

#include <cmath>
#include <array>
#include <complex>
#include <iostream>

namespace nrcc {

    //double epsilon = 1e-9;

    template<typename type>
    type epsilon = 1e-7;

    double lightspeed = 299792458;

    double infinity = std::numeric_limits<double>::infinity();

    double pi = std::numbers::pi;

    double impedence = 377;

    double permeability = 1.25663706e-6;

    std::complex<double> j = std::complex<double>(0, 1);

    double golden_angle = pi * (3 - sqrt(5));

    double ratio = (1 + sqrt(5)) / 2;

}

#endif //NARCCISSUS_UTIL_HPP
