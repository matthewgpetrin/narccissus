// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_VEC3_HPP
#define NARCCISSUS_VEC3_HPP

#include <array>
#include <cmath>
#include <iostream>

#include "Util.hpp"

template<typename type>
struct Vec3 {

    // VARIABLES
    union {
        struct {
            type x;
            type y;
            type z;
        };
        type v[3];
    };

    // METHODS
    type EL() const {
        return std::asin(z / norm());
    }

    type AZ() const {
        return std::atan2(y, x);
    }

    type norm() const {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    Vec3 unit() const {
        if (norm() == 1) return *this;
        else return {x / norm(), y / norm(), z / norm()};
    }

    // CONSTRUCTORS
    Vec3(const type &x, const type &y, const type &z) : v{x, y, z} {}

    Vec3(const type &el, const type &az) : v{std::cos(el) * std::cos(az), std::cos(el) * std::sin(az), std::sin(el)} {}

    // OVERLOADS
    Vec3 operator+(const Vec3 &v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vec3 operator-(const Vec3 &v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vec3 operator*(const Vec3 &v) const {
        return {x * v.x, y * v.y, z * v.z};
    }

    Vec3 operator/(const Vec3 &v) const {
        return {x / v.x, y / v.y, z / v.z};
    }

    Vec3 operator*(type t) const {
        return {x * t, y * t, z * t};
    }

    Vec3 operator/(type t) const {
        return {x / t, y / t, z / t};
    }
};

// COORDINATE CONVERSIONS
template<typename type>
std::array<type, 2> spherical(const Vec3<type> &v) {
    return {std::asin(v.z / v.norm()), std::atan2(v.y, v.x)};
}

template<typename type>
std::array<type, 3> cartesian(const type &el, const type &az) {
    type x = std::cos(el) * std::cos(az);
    type y = std::cos(el) * std::sin(az);
    type z = std::sin(el);
    return {x, y, z};
}

// VECTOR MATHEMATICS
template<typename type>
type dot(const Vec3<type> &v, const Vec3<type> &w) {
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

template<typename type>
type distance(const Vec3<type> &v, const Vec3<type> &w) {
    type a = v.x - w.x;
    type b = v.y - w.y;
    type c = v.z - w.z;
    return std::sqrt((a * a) + (b * b) + (c * c));
}

template<typename type>
Vec3<type> cross(const Vec3<type> &v, const Vec3<type> &w) {
    type x = v.y * w.z - v.z * w.y;
    type y = v.z * w.x - v.x * w.z;
    type z = v.x * w.y - v.y * w.x;
    return {x, y, z};
}

// OSTREAM OVERLOAD
template<typename type>
std::ostream &operator<<(std::ostream &os, const Vec3<type> &v) {
    os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
    return os;
}

#endif //NARCCISSUS_VEC3_HPP