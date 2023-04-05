// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_UTIL_HPP
#define NARCCISSUS_UTIL_HPP

#include <map>
#include "Vec3.hpp"

namespace nrcc {
    double epsilon = 1e-7;

    double pi = std::numbers::pi;

    double infinity = std::numeric_limits<double>::infinity();

    std::complex<double> j = std::complex<double>(0, 1);

    double golden_angle = pi * (3 - sqrt(5));

    double golden_ratio = (1 + sqrt(5)) / 2;

    double impedance = 377;

    double lightspeed = 299792458;

    double permeability = 1.25663706e-6;

    namespace polarization {
        template<typename T>
        Vec3<std::complex<T>> null = {{-7, -7},
                                      {-7, -7},
                                      {-7, -7}};

        template<typename T>
        Vec3<std::complex<T>> circular = {{0, 0},
                                          {1, 0},
                                          {0, 1}};

        template<typename T>
        Vec3<std::complex<T>> linear = {{0, 0},
                                        {0, 0},
                                        {1, 0}};
    }

    enum Interactions {
        emission,
        reflection,
        diffraction,
        transmission,
    };

    enum Materials {
        vacuum,
        concrete,
        brick,
        wood,
        glass,
        metal,
        desert,
        ground,
        swamp,
    };

    // These are relative permittivities. Please note that these are relative to free space.
    // https://www.itu.int/dms_pubrec/itu-r/rec/p/R-REC-P.2040-1-201507-S!!PDF-E.pdf
    std::map<nrcc::Materials, std::array<double, 2>> permittivity = {
            {nrcc::Materials::vacuum,   {1.00, 0.0}},
            {nrcc::Materials::concrete, {5.31, 0.0}},
            {nrcc::Materials::brick,    {3.75, 0.0}},
            {nrcc::Materials::wood,     {1.99, 0.0}},
            {nrcc::Materials::glass,    {6.27, 0.0}},
            {nrcc::Materials::metal,    {1.00, 0.0}},
            {nrcc::Materials::desert,   {3.00, 0.0}},
            {nrcc::Materials::ground,   {15.0, -0.1}},
            {nrcc::Materials::swamp,    {30.0, -0.4}},
    };

    std::map<nrcc::Materials, std::array<double, 2>> conductivity = {
            {nrcc::Materials::vacuum,   {0.0000,  0.0000}},
            {nrcc::Materials::concrete, {0.0326,  0.8095}},
            {nrcc::Materials::brick,    {0.0380,  0.0000}},
            {nrcc::Materials::wood,     {0.0047,  1.0718}},
            {nrcc::Materials::glass,    {0.0043,  1.1925}},
            {nrcc::Materials::metal,    {10.0e7,  0.0000}},
            {nrcc::Materials::desert,   {0.00015, 2.5200}},
            {nrcc::Materials::ground,   {0.0350,  1.6300}},
            {nrcc::Materials::swamp,    {0.1500,  1.3000}},
    };
}

#endif //NARCCISSUS_UTIL_HPP