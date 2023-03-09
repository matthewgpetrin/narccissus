// Copyright(c) 2023, Matthew, All rights reserved.

#ifndef NARCCISSUS_RAY_HPP
#define NARCCISSUS_RAY_HPP

#include "Nrcc.hpp"
#include "Face.hpp"

template<typename type>
class Ray {
    using vect = Vector<type>;
public:
    const vect origin;
    const vect direction;

    const type azimuth;
    const type altitude;

    type intersectionDistance(const Face<type> &f) const {
        vect pvec = cross(direction, f.edges[1]);

        type det = dot(f.edges[0], pvec);
        if (fabs(det) < nrcc::epsilon) return -1;

        vect tvec = origin - f.points[0];

        type u = dot(tvec, pvec) * (1 / det);
        if (u < 0 || u > 1) return -1;

        vect qvec = cross(tvec, f.edges[0]);

        type v = dot(direction, qvec) * (1 / det);
        if (v < 0 || u + v > 1) return -1;

        return dot(f.edges[1], qvec) * (1 / det);
    }

    vect intersectionVector(const Face<type> &f) const {
        return direction * intersectionDistance(f) + origin;
    }

    vect reflectionVector(const Face<type> &f) const {
        return direction - f.normal() * 2 * dot(direction, f.normal());
    }

    Ray(const vect &o, const vect &d) : origin(o), direction(d.unit()), azimuth(atan2(d.y, d.x)), altitude(asin(d.z)) {}
};

template<class type>
std::ostream &operator<<(std::ostream &os, const Ray<type> &r) {
    os << "[" << r.origin << ", " << r.direction << "]" << ";    {" << r.azimuth << ", " << r.altitude << "}";
    return os;
}

#endif //NARCCISSUS_RAY_HPP