// Copyright(c) 2023, Matthew Petrin, All rights reserved.
/*
#ifndef NARCCISSUS_NRCC_HPP
#define NARCCISSUS_NRCC_HPP

#include "Mesh.hpp"
#include "Wave.hpp"

template<typename type>
class Nrcc {
    using Vec3 = Vec3<type>;
    using Face = Face<type>;
    using Wave = Wave<type>;
    //using Path = Path<type>;
    using Mesh = Mesh<type>;

private:
    // VARIABLES
    const uint8_t reflections;

public:
    // METHODS
    Path trace(const Wave &wave, const Mesh &mesh) {
        std::vector<Wave> waves{wave};
        std::vector<Face> faces;

        bool reflected = false;

        type min_distance = nrcc::infinity;
        for (const auto &face: mesh.faces) {
            type new_distance = intersectionDistance(wave, face);

            if (new_distance > nrcc::epsilon && new_distance < min_distance) {
                if (reflected) {
                    waves.pop_back();
                    faces.pop_back();
                }

                waves.push_back({intersectionVector(wave, face), reflectionVector(wave, face)});
                faces.push_back(face);

                min_distance = new_distance;
                reflected = true;
            }
        }

        if (reflected == 1 && reflections > 1) return trace(waves, faces, mesh, reflections - 1);

        else return {waves, faces};
    }
/*
    // CONSTRUCTOR
    Nrcc() : reflections(2) {}

    explicit Nrcc(const uint8_t &rs) : reflections(rs) {}

// VECTOR - FACE METHODS
    template<typename type>
    type intersectionDistance(const Wave<type> &wave, const Face<type> &face) {
        Vec3 p_vec = cross(wave.direct, face.bounds[1]);

        type det = dot(face.bounds[0], p_vec);

        if (det < nrcc::epsilon) return -1;

        Vec3 t_vec = wave.origin - face.points[0];

        type u = dot(t_vec, p_vec) * (1 / det);

        if (u < 0 || u > 1) return -1.0;

        Vec3 q_vec = cross(t_vec, face.bounds[0]);

        type v = dot(wave.direct, q_vec) * (1 / det);

        if (v < 0 || u + v > 1) return -1.0;

        return dot(face.bounds[1], q_vec) * (1 / det);
    }

    template<typename type>
    Vec3<type> intersectionVector(const Wave<type> &wave, const Face<type> &face) {
        return wave.direct * intersectionDistance(wave, face) + wave.origin;
    }

    template<typename type>
    Vec3<type> reflectionVector(const Wave<type> &wave, const Face<type> &face) {
        return wave.direct - face.normal() * dot(wave.direct, face.normal()) * 2;
    }

    // VECTOR - SPHERE METHODS


    // RECURSIVE TRACE METHOD
    Path trace(std::vector<Wave> &waves, std::vector<Face> &faces, const Mesh &mesh, const uint8_t &rs) {
        Wave wave = waves.back();
        bool reflected = false;

        type min_distance = nrcc::infinity;
        for (const auto &face: mesh.faces) {
            type new_distance = intersectionDistance(wave, face);

            if (new_distance > nrcc::epsilon && new_distance < min_distance) {
                if (reflected) {
                    waves.pop_back();
                    faces.pop_back();
                }

                waves.push_back({intersectionVector(wave, face), reflectionVector(wave, face)});
                faces.push_back(face);

                min_distance = new_distance;
                reflected = true;
            }
        }

        if (reflected && rs > 1) return trace(waves, faces, mesh, rs - 1);

        else return {waves, faces};
    }
};*/

#endif //NARCCISSUS_NRCC_HPP