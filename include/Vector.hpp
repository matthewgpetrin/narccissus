// Copyright(c) 2023, Matthew, All rights reserved.

#ifndef NARCCISSUS_VECTOR_HPP
#define NARCCISSUS_VECTOR_HPP

#include <cmath>
#include <iostream>
#include <iomanip>

template<typename T>
struct Vector {
    const T x, y, z;

    T magnitude() const {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    Vector<T> unit() const {
        if (magnitude() == 1) return *this;
        else return {x / magnitude(), y / magnitude(), z / magnitude()};
    }

    //Vector(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {}

    Vector<T> operator+(const Vector<T> &v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vector<T> operator-(const Vector<T> &v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vector<T> operator*(const Vector<T> &v) const {
        return {x * v.x, y * v.y, z * v.z};
    }

    Vector<T> operator/(const Vector<T> &v) const {
        return {x / v.x, y / v.y, z / v.z};
    }

    Vector<T> operator*(T t) const {
        return {x * t, y * t, z * t};
    }

    Vector<T> operator/(T t) const {
        return {x / t, y / t, z / t};
    }
};

template<typename T>
T dot(const Vector<T> &v, const Vector<T> &w) {
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

template<typename T>
T distance(const Vector<T> &v, const Vector<T> &w) {
    T a = v.x - w.x;
    T b = v.y - w.y;
    T c = v.z - w.z;
    return sqrt((a * a) + (b * b) + (c * c));
}

template<typename T>
Vector<T> cross(const Vector<T> &v, const Vector<T> &w) {
    T x = v.y * w.z - v.z * w.y;
    T y = v.z * w.x - v.x * w.z;
    T z = v.x * w.y - v.y * w.x;
    return {x, y, z};
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &v) {
    os << std::setprecision(2) << "{" << v.x << ", " << v.y << ", " << v.z << "}";
    return os;
}

#endif //NARCCISSUS_VECTOR_HPP