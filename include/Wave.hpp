// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_WAVE_HPP
#define NARCCISSUS_WAVE_HPP

#include "Vec3.hpp"

template<typename type>
class Wave {
    using Vec3 = Vec3<type>;
    
public:
    // VARIABLES
    const Vec3 origin;
    const Vec3 direct;

    const type EL;
    const type AZ;

    // CONSTRUCTORS
    Wave(const Vec3 &o, const Vec3 &d) : origin(o), direct(d), EL(d.EL()), AZ(d.AZ()) {}

    Wave(const Vec3 &o, const Vec3 &el, const Vec3 &az) : origin(o), direct({el, az}), EL(el), AZ(az) {}
};

// OSTREAM
template<typename T>
std::ostream &operator<<(std::ostream &os, const Wave<T> &wave) {
    os << "[" << wave.origin << ", " << wave.direct << "]";
    return os;
}

#endif //NARCCISSUS_WAVE_HPP