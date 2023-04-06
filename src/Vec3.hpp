// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_VEC3_HPP
#define NARCCISSUS_VEC3_HPP

#include <array>
#include <random>
#include <chrono>
#include <complex>
#include <iostream>

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
        return {x / norm(), y / norm(), z / norm()};
    }

    auto real() const {
        using U = typename std::remove_reference<decltype(x)>::type::value_type;
        using V = typename std::remove_reference<decltype(x)>::type;
        return Vec3<typename std::enable_if<std::is_same<V, std::complex<U>>::value, U>::type>
                (static_cast<U>(std::real(x)), static_cast<U>(std::real(y)), static_cast<U>(std::real(z)));
    }

    auto imag() const {
        using U = typename std::remove_reference<decltype(x)>::type::value_type;
        using V = typename std::remove_reference<decltype(x)>::type;
        return Vec3<typename std::enable_if<std::is_same<V, std::complex<U>>::value, U>::type>
                (static_cast<U>(std::imag(x)), static_cast<U>(std::imag(y)), static_cast<U>(std::imag(z)));
    }

    auto cmpx() const {
        using cmpx = std::complex<type>;
        cmpx a = {x, 0};
        cmpx b = {y, 0};
        cmpx c = {z, 0};
        Vec3<cmpx> u = {a, b, c};
        return u;
    }

    // CONSTRUCTORS
    Vec3() : v{-7, -7, -7} {}

    Vec3(const Vec3 &v) : v{v.x, v.y, v.z} {}

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
template<typename T>
std::array<T, 2> spherical(const Vec3<T> &v) {
    return {std::asin(v.z / v.norm()), std::atan2(v.y, v.x)};
}

template<typename T>
std::array<T, 3> cartesian(const T &el, const T &az) {
    T x = std::cos(el) * std::cos(az);
    T y = std::cos(el) * std::sin(az);
    T z = std::sin(el);
    return {x, y, z};
}

// VECTOR MATHEMATICS
template<typename T>
T angle(const Vec3<T> &v, const Vec3<T> &w) {
    return std::acos(dot(v.unit(), w.unit()));
}

template<typename T>
T distance(const Vec3<T> &v, const Vec3<T> &w) {
    T a = v.x - w.x;
    T b = v.y - w.y;
    T c = v.z - w.z;
    return std::sqrt((a * a) + (b * b) + (c * c));
}

// COMPLEX VECTOR MATHEMATICS
template<typename T>
Vec3<T> exp(const Vec3<T> &v) {
    Vec3<T> v2 = v * v;
    Vec3<T> v3 = v * v * v;
    return 1 + v + v2 / 2 + v3 / 6;
}

template<typename T, typename U>
T dot(const Vec3<T> &v, const Vec3<U> &w) {
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

template<typename T, typename U>
Vec3<T> cross(const Vec3<T> &v, const Vec3<U> &w) {
    T x = v.y * w.z - v.z * w.y;
    T y = v.z * w.x - v.x * w.z;
    T z = v.x * w.y - v.y * w.x;
    return {x, y, z};
}

template<typename T, typename U>
Vec3<T> shift(const Vec3<T> &v, const Vec3<U> &w) {
    Vec3<T> x = cross(v, w);
    return cross(x, w) * -1;
}

// OTHER
template<typename T>
Vec3<T> randomVector() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine generator(seed);

    std::uniform_real_distribution<T> distribution(0.0, 1.0);

    T u = distribution(generator);
    T v = distribution(generator);

    T EL = std::acos(1 - 2 * u) - (std::numbers::pi_v<T> / 2);
    T AZ = 2 * std::numbers::pi_v<T> * v;

    return {EL, AZ};
}

// OSTREAM OVERLOAD
template<typename T>
std::ostream &operator<<(std::ostream &os, const Vec3<T> &v) {
    os << v.x << ", " << v.y << ", " << v.z;
    return os;
}

#endif //NARCCISSUS_VEC3_HPP