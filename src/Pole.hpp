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

    Pole(const Vec3 &c, const Vec3 &o, const type &f) : coordinates(c), orientation(o), frequency(f) {}

//    std::vector<Vec3> transmit(const type &power, const type &scaling_factor, const type &accuracy_factor) {
//        auto lambda = [this](const Vec3 &v) -> type {
//            return pow(cross(v, orientation).norm() / v.norm() * orientation.norm(), 2);
//        };
//
//        std::vector<Vec3> vecs;
//        for (const Vec3 &vec: nrcc::icosphere(accuracy_factor)) {
//            type A = pow(cross(vec, orientation).norm() / vec.norm() * orientation.norm(), scaling_factor);
//            vecs.emplace_back(vec * A);
//        }
//
//        type magnitudes = 0;
//        for (const auto &vec: vecs) {
//            magnitudes += vec.norm();
//        }
//
//        std::vector<Vec3> wecs;
//        for (const auto &vec: vecs) {
//            wecs.push_back(vec * power / magnitudes);
//        }
//
//        return wecs;
//    }

    std::vector<Wave> transmit(const type &power, const type &scaling_factor, const type &accuracy_factor) {
        //type lambda = [this, &scaling_factor](const Vec3 &v) -> type {
        //    return pow(cross(v, orientation).norm() / v.norm() * orientation.norm(), scaling_factor);
        //};

        std::vector<Vec3> wave_directions;
        for (const Vec3 &direction: nrcc::icosphere(accuracy_factor)) {
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
            waves.push_back({coordinates, wave_directions[i], wave_scales[i], frequency, 0, orientation.cmpx()});
        }

        return waves;
    }
};

#endif //NARCCISSUS_POLE_HPP
