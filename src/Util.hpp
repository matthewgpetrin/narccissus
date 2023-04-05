// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_UTIL_HPP
#define NARCCISSUS_UTIL_HPP

#include <map>
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

    double electric_constant = 8.8541878128e-12;

    template<typename T>
    Vec3<std::complex<T>> linear = {{0, 0},
                                    {0, 0},
                                    {1, 0}};

    namespace polarization {
        template<typename T>
        Vec3<std::complex<T>> null = {{-7, -7},
                                      {-7, -7},
                                      {-7, -7}};

        template<typename T>
        Vec3<std::complex<T>> circular = {{0, 0},
                                          {1, 0},
                                          {0, 1}};
    }
    enum Interaction {
        emission,
        reflection,
        diffraction,
        transmission,
    };

    enum Material {
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

    // These are relative permittivities. Please note that these are relative to free space. These should be complex
    // values. These assume relatively small imaginary components.
    std::map<nrcc::Material, std::array<double, 2>> permittivity = {
            {nrcc::Material::vacuum,   {1.00, 0.0}},
            {nrcc::Material::concrete, {5.31, 0.0}},
            {nrcc::Material::brick,    {3.75, 0.0}},
            {nrcc::Material::wood,     {1.99, 0.0}},
            {nrcc::Material::glass,    {6.27, 0.0}},
            {nrcc::Material::metal,    {1.00, 0.0}},
            {nrcc::Material::desert,   {3.00, 0.0}},
            {nrcc::Material::ground,   {15.0, -0.1}},
            {nrcc::Material::swamp,    {30.0, -0.4}},
    };

    std::map<nrcc::Material, std::array<double, 2>> conductivity = {
            {nrcc::Material::vacuum,   {0.0000,  0.0000}},
            {nrcc::Material::concrete, {0.0326,  0.8095}},
            {nrcc::Material::brick,    {0.0380,  0.0000}},
            {nrcc::Material::wood,     {0.0047,  1.0718}},
            {nrcc::Material::glass,    {0.0043,  1.1925}},
            {nrcc::Material::metal,    {10.0e7,  0.0000}},
            {nrcc::Material::desert,   {0.00015, 2.5200}},
            {nrcc::Material::ground,   {0.0350,  1.6300}},
            {nrcc::Material::swamp,    {0.1500,  1.3000}},
    };


}

#endif //NARCCISSUS_UTIL_HPP