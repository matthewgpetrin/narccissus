// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_FACE_HPP
#define NARCCISSUS_FACE_HPP

#include "Vec3.hpp"
#include "Util.hpp"

template<typename type>
class Face {
    using Vec3 = Vec3<type>;
public:
    // VARIABLES
    const std::array<Vec3, 3> points;
    const std::array<Vec3, 2> bounds;

    nrcc::Material material;

    // METHODS
    Vec3 normal() const {
        return cross(bounds[0], bounds[1]).unit();
    }

    std::complex<type> permittivity() {
        //complex valued permittivity. make map and pull values from matlab
    }


    // CONSTRUCTORS
    Face(const std::array<Vec3, 3> &ps) : points(ps), bounds{ps[2] - ps[0], ps[2] - ps[1]} {}

    Face(const Vec3 &p, const Vec3 &q, const Vec3 &r) : points{p, q, r}, bounds{q - p, r - p},
                                                        material(nrcc::concrete) {}


    std::complex<type> refractiveIndex(const type &frequency) {
        type r = nrcc::permittivity[material][0] * std::pow(frequency, nrcc::permittivity[material][1]);

        type c = nrcc::conductivity[material][0] * std::pow(frequency, nrcc::conductivity[material][1]);

        type i = c / (2 * nrcc::pi * nrcc::electric_constant * frequency);

        return {r, i};
    }
};

// OSTREAM OVERRIDE
template<typename type>
std::ostream &operator<<(std::ostream &os, const Face<type> &face) {
    os << "[" << face.points[0] << ", " << face.points[1] << ", " << face.points[2] << "];   " << face.normal();
    return os;
}

#endif //NARCCISSUS_FACE_HPP