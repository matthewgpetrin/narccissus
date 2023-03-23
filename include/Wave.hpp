// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_WAVE_HPP
#define NARCCISSUS_WAVE_HPP

#include "Vec3.hpp"

template<typename type>
class Wave {
    using cmpx = std::complex<type>;
    using VecC = Vec3<cmpx>;
    using Vec3 = Vec3<type>;

public:
    // VARIABLES
    const Vec3 origin;
    const VecC direct;

    //const type EL;
    //const type AZ;

    const type power;
    const type delay;
    const type frequency;
    const VecC polarization;

    // CONSTRUCTORS
    Wave(const Vec3 &o, const VecC &d, const type &P, const type &f, const type &t, const VecC &p)
            : origin(o), direct(d), power(P), delay(t), frequency(f), polarization(shifted(p, {1, 0, 0}, d)) {}

    //Wave(const Vec3 &o, const Vec3 &el, const Vec3 &az) : origin(o), direct({el, az}) {}

    type wavenumber() const {
        return 2 * nrcc::pi / wavelength();
    }

    type wavelength() const {
        return nrcc::lightspeed / frequency;
    }

    VecC wavevector() const {
        return direct * wavenumber();
    }

    type amplitude(const Vec3 &r) const {
        return 3;
    }

    cmpx phase(const Vec3 &r) const {
        cmpx x(r.x, 0);
        cmpx y(r.y, 0);
        cmpx z(r.z, 0);
        return std::exp(nrcc::j * dot(wavevector(), {x, y, z}) + nrcc::j * delay);
    }

    VecC electricField(const Vec3 &r) const {
        cmpx x = amplitude(r) * phase(r) * polarization.x;
        cmpx y = amplitude(r) * phase(r) * polarization.y;
        cmpx z = amplitude(r) * phase(r) * polarization.z;

        return {x, y, z};
    }

    VecC magneticField(const Vec3 &r) const {
        return cross(electricField(r), direct) / (nrcc::lightspeed * nrcc::lightspeed);
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
    // vectors of the polarization are computed in the initializer list using shifted().
};

// OSTREAM
template<typename T>
std::ostream &operator<<(std::ostream &os, const Wave<T> &wave) {
    os << "[" << wave.origin << ", " << wave.direct << "]";
    return os;
}

#endif //NARCCISSUS_WAVE_HPP