// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_NRCC_HPP
#define NARCCISSUS_NRCC_HPP

#include "Face.hpp"
#include "Wave.hpp"

template<typename type>
class Nrcc {
    using cmpx = std::complex<type>;
    using VecC = Vec3<cmpx>;
    using Vec3 = Vec3<type>;
    using Face = Face<type>;
    using Wave = Wave<type>;

public:

// VECTOR - FACE METHODS*/

    type intersectionDistance(const Wave &wave, const Face &face) {
        Vec3 p_vec = cross(wave.direct, face.bounds[1]);

        type det = dot(face.bounds[0], p_vec);

        if (std::fabs(det) < nrcc::epsilon) return -1.0;

        Vec3 t_vec = wave.origin - face.points[0];

        type u = dot(t_vec, p_vec) * (1 / det);

        if (u < 0 || u > 1) return -1.0;

        Vec3 q_vec = cross(t_vec, face.bounds[0]);

        type v = dot(wave.direct, q_vec) * (1 / det);

        if (v < 0 || u + v > 1) return -1.0;

        return dot(face.bounds[1], q_vec) * (1 / det);
    }

    Vec3 intersectionVector(const Wave &wave, const Face &face) {
        return wave.direct * intersectionDistance(wave, face) + wave.origin;
    }

    Vec3 reflectionVector(const Wave &wave, const Face &face) {
        return wave.direct - face.normal() * dot(face.normal(), wave.direct) * 2;
    }

    Vec3 refractionVector(const Wave &wave, const Face &face) {
        cmpx nint = cmpx(1, 0) / face.refractiveIndex(wave.initial.frequency);
        type cos_i = dot(face.normal(), wave.direct * -1.0);

        cmpx sin_t = nint * std::sqrt(1 - cos_i * cos_i);
        cmpx cos_t = std::sqrt(cmpx(1) - sin_t * sin_t);

        VecC refc = wave.direct.cmpx() * nint + face.normal().cmpx() * (nint * cos_i - cos_t);
        return refc.real().unit();
    }

    Wave reflectedWave(Wave &wave, Face &face) {
        return {intersectionVector(wave, face), reflectionVector(wave, face), &wave, &face, nrcc::reflection};
    }

    Wave refractedWave(Wave &wave, Face &face) {
        return {intersectionVector(wave, face), refractionVector(wave, face), &wave, &face, nrcc::refraction};
    }

    // RECURSIVE TRACE METHOD
    std::vector<Wave> trace(Wave &wave, std::vector<Face> &faces, const uint8_t &rs) {
        std::vector<Wave> waves{wave};

        bool intersected = false;
        Face intersecting_face = faces.back();

        type min_distance = nrcc::infinity;
        for (const auto &face: faces) {
            type new_distance = intersectionDistance(wave, face);

            if (new_distance > nrcc::epsilon && new_distance < min_distance) {
                intersected = true;
                intersecting_face = face;
                min_distance = new_distance;
            }
        }
        // TODO: The below should be rewritten to allow for const declarations in wave and face
        if (intersected) {
            if (rs > 1) {
                Wave reflect_wave = reflectedWave(wave, intersecting_face);
                Wave refract_wave = refractedWave(wave, intersecting_face);

                std::vector<Wave> reflection_traced = trace(reflect_wave, faces, rs - 1);
                std::vector<Wave> refraction_traced = trace(refract_wave, faces, rs - 1);

                waves.insert(waves.end(), reflection_traced.begin(), reflection_traced.end());
                waves.insert(waves.end(), refraction_traced.begin(), refraction_traced.end());
            }
            else {
                waves.push_back(reflectedWave(wave, intersecting_face));
                waves.push_back(refractedWave(wave, intersecting_face));
            }
        }
        return waves;
    }
};

#endif //NARCCISSUS_NRCC_HPP