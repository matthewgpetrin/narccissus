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

        /*template<typename T>
        Vec3<std::complex<T>> linear = {{0, 0},
                                        {0, 0},
                                        {1, 0}};*/


        Vec3<std::complex<double>> linear = {{0, 0},
                                             {0, 0},
                                             {1, 0}};
    }

    enum Interactions {
        emission,
        reflection,
        refraction,
        diffraction,
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

    std::vector<Vec3<double>> icosphere(int subdivs) {
        const double X = 0.525731112119133606;
        const double Z = 0.850650808352039932;

        std::vector<Vec3<double>> vertices{
                {-X, 0,  Z},
                {X,  0,  Z},
                {-X, 0,  -Z},
                {X,  0,  -Z},
                {0,  Z,  X},
                {0,  Z,  -X},
                {0,  -Z, X},
                {0,  -Z, -X},
                {Z,  X,  0},
                {-Z, X,  0},
                {Z,  -X, 0},
                {-Z, -X, 0}
        };

        std::vector<Vec3<int>> faces{
                {0,  4,  1},
                {0,  9,  4},
                {9,  5,  4},
                {4,  5,  8},
                {4,  8,  1},
                {8,  10, 1},
                {8,  3,  10},
                {5,  3,  8},
                {5,  2,  3},
                {2,  7,  3},
                {7,  10, 3},
                {7,  6,  10},
                {7,  11, 6},
                {11, 0,  6},
                {0,  1,  6},
                {6,  1,  10},
                {9,  0,  11},
                {9,  11, 2},
                {9,  2,  5},
                {7,  2,  11}
        };

        for (int i = 0; i < subdivs; ++i) {
            std::vector<Vec3<int>> fs;
            std::vector<Vec3<double>> vs = vertices;

            for (const auto &face: faces) {
                int v1 = face.x;
                int v2 = face.y;
                int v3 = face.z;
                uint64_t v12 = vs.size();
                uint64_t v23 = v12 + 1;
                uint64_t v31 = v12 + 2;

                vs.push_back((vs[v1] * 0.5 + vs[v2] * 0.5).unit());
                vs.push_back((vs[v2] * 0.5 + vs[v3] * 0.5).unit());
                vs.push_back((vs[v3] * 0.5 + vs[v1] * 0.5).unit());

                fs.emplace_back(v1, v12, v31);
                fs.emplace_back(v2, v23, v12);
                fs.emplace_back(v3, v31, v23);
                fs.emplace_back(v12, v23, v31);
            }
            faces = fs;
            vertices = vs;
        }
        return vertices;
    }

    template<typename T>
    type intersectionDistance(const Vec3<T> &origin, const Vec3<T> &direct, const Vec3<T> &center, const T &radius) {
        Vec3 length = origin - center;

        T a = dot(direct, direct);
        T b = 2 * dot(direct, length);
        T c = dot(length, length) - radius * radius;

        T d = b * b - 4 * a * c;

        T t;
        T u;

        if (d < 0) return -1;

        else if (d == 0) return -0.5 * b / a;

        else {
            T q = (b > 0) ? -0.5 * (b + std::sqrt(d)) : -0.5 * (b - std::sqrt(d));
            t = q / a;
            u = c / q;

            if (t < u && t > 0) return t;

            else if (u > 0) return u;

            else return -1;
        }
    }
}

#endif //NARCCISSUS_UTIL_HPP