// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_WAVE_HPP
#define NARCCISSUS_WAVE_HPP

#include "Vec3.hpp"
#include "Util.hpp"

template<typename type>
class Wave {
    using cmpx = std::complex<type>;
    using VecC = Vec3<cmpx>;
    using Vec3 = Vec3<type>;

public:
    // VARIABLES
    const Vec3 origin;
    const Vec3 direct;

    //const type EL;
    //const type AZ;

    const type power;
    const type delay;
    const VecC polar;

    const type frequency;

    // CONSTRUCTORS
    Wave(const Vec3 &o, const Vec3 &d, const type &P, const type &f, const type &t, const VecC &p)
            : origin(o), direct(d), power(P), delay(t), frequency(f), polar{shift(p, d).unit()} {}

    Wave(const Vec3 &o, const Vec3 &d)
            : origin(o), direct(d), power(1), delay(), frequency(1e9), polar{shift(nrcc::linear<type>, d).unit()} {}

    type wavenumber() const {
        return 2 * nrcc::pi / wavelength();
    }

    type wavelength() const {
        return nrcc::lightspeed / frequency;
    }

    Vec3 wavevector() const {
        return direct * wavenumber();
    }

    type amplitude(const Vec3 &r) const {
        return power;
    }

    cmpx phase(const Vec3 &r) const {
        return std::exp<type>(nrcc::j * dot(wavevector(), r) + nrcc::j * delay);
    }

    // TODO: CHECK IF THIS SHOULD BE NEGATIVE OR NOT
    VecC electricField(const Vec3 &r) const {
        return polar * amplitude(r) * phase(r) * -1;
    }

    VecC magneticField(const Vec3 &r) const {
        //return cross(electricField(r), direct) / (377);
        return cross(electricField(r), direct) * -1;
    }

    // Polarization is represented as vector of complex numbers. The real and imaginary components represent
    // a linear combination of two vectors that are orthogonal to each other. This, when included in the
    // calculation for the E and H fields allows for the phase to react to non linear polarizations that rotate with phase
    //
    // Examples:
    // {0, 1, 0} j{0, 0, 0} Linearly polarized horizontally
    // {0, 0, 1} j{0, 0, 0} Linearly polarized vertically
    // {0, 0, 1} j{0, 1, 0} Circular polarized clockwise
    // {0, 0, 2} j{0, 1, 0} Elliptically polarized clockwise
    //
    // Note that the input parameters assume a ray with direction {1, 0, 0}. This is for ease of use, the actual
    // vectors of the polar are computed in the initializer list using shifted().
};

// OSTREAM
template<typename T>
std::ostream &operator<<(std::ostream &os, const Wave<T> &wave) {
    os << "[" << wave.origin << ", " << wave.direct << "]";
    return os;
}

#endif //NARCCISSUS_WAVE_HPP