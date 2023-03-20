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

    const type power;
    const type phase;
    const type frequency;

    const Vec3 E_polarization = {0, 0, 1};
    const Vec3 H_polarization = {1, 0, 0};

    // CONSTRUCTORS
    Wave(const Vec3 &o, const Vec3 &d, const type &pow, const type &fre, const type &del)
            : origin(o), direct(d), power(pow), phase(del), frequency(fre), EL(d.EL()), AZ(d.AZ()) {}

    Wave(const Vec3 &o, const Vec3 &el, const Vec3 &az) : origin(o), direct({el, az}), EL(el), AZ(az) {}

    type wavenumber() const {
        return 2 * nrcc::pi / wavelength();
    }

    type wavelength() const {
        return nrcc::lightspeed / frequency;
    }

    std::complex<type> shift(const type &distance) {
        return std::exp(-nrcc::j * wavenumber() * distance + phase);
    }

    type eAmplitude(const type distance) {
        return std::sqrt(30 * power / (distance * wavelength() * 4 * nrcc::pi));
    }

    type mAmplitude(const type distance) {
        return std::sqrt(120 * power / (distance * wavelength() * 4 * nrcc::pi));
    }

    std::array<std::complex<type>, 3> eField(const type &distance) {
        std::complex<type> x = eAmplitude(distance) * E_polarization.x * shift(distance);
        std::complex<type> y = eAmplitude(distance) * E_polarization.y * shift(distance);
        std::complex<type> z = eAmplitude(distance) * E_polarization.z * shift(distance);
        return {x, y, z};
    }

    std::array<std::complex<type>, 3> mField(const type &distance) {
        std::complex<type> x = eAmplitude(distance) * H_polarization.x * shift(distance) * (1 / nrcc::permeability);
        std::complex<type> y = eAmplitude(distance) * H_polarization.y * shift(distance) * (1 / nrcc::permeability);
        std::complex<type> z = eAmplitude(distance) * H_polarization.z * shift(distance) * (1 / nrcc::permeability);
        return {x, y, z};
    }
};

// OSTREAM
template<typename T>
std::ostream &operator<<(std::ostream &os, const Wave<T> &wave) {
    os << "[" << wave.origin << ", " << wave.direct << "]";
    return os;
}

#endif //NARCCISSUS_WAVE_HPP