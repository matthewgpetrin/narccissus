// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_POLE_HPP
#define NARCCISSUS_POLE_HPP

#include "Wave.hpp"

template<typename type>
class Pole {
    using cmpx = std::complex<type>;
    using VecC = Vec3<cmpx>;
    using Vec3 = Vec3<type>;
    using Wave = Wave<type>;

public:
    Vec3 coordinates;
    Vec3 orientation;
    type frequency;
    type length;

    Pole(const Vec3 &c, const Vec3 &o, const type &f, const type &l) :
            coordinates(c), orientation(o), frequency(f), length(l) {}

    std::vector<Wave>
    transmit(const type &power, const type &delay, const type &scaling_factor, const type &accuracy_factor) {
        std::vector<Vec3> wave_directions;
        for (const Vec3 &direction: nrcc::icosphere<type>(accuracy_factor)) {
            wave_directions.emplace_back(direction);
        }

        std::vector<type> wave_scales;
        for (const auto &direction: wave_directions) {
            type s = pow(cross(direction, orientation).norm() / direction.norm() * orientation.norm(), scaling_factor);
            wave_scales.push_back(s);
        }

        type magnitude = 0;
        for (const auto &scale: wave_scales) {
            magnitude += scale;
        }
        for (auto &scale: wave_scales) {
            scale *= power / magnitude;
        }

        std::vector<Wave> waves;
        for (uint64_t i = 0; i < wave_directions.size(); i++) {
            waves.push_back({coordinates, wave_directions[i], wave_scales[i], frequency, delay, orientation.cmpx()});
        }

        return waves;
    }

    type wavelength() {
        return nrcc::lightspeed / frequency;
    }

    Vec3 receive(std::vector<Wave> &waves) {
        std::vector<VecC> e_fields;
        for (auto &wave: waves) {
            type d = nrcc::intersectionDistance(wave.origin, wave.direct, coordinates, length);
            if (d > 0) e_fields.push_back(wave.electricField(length(wave.origin, coordinates)));
        }
        cmpx xx = 0;
        cmpx yx = 0;
        cmpx zx = 0;
        for (auto e_field: e_fields) {
            xx += e_field.x;
            yx += e_field.y;
            zx += e_field.z;
        }
        Vec3 re = {xx.real(), yx.real(), zx.real()};
        return re;
    }
};

#endif //NARCCISSUS_POLE_HPP
