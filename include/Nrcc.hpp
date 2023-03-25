// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_NRCC_HPP
#define NARCCISSUS_NRCC_HPP

#include "Path.hpp"
#include "Mesh.hpp"

template<typename type>
class Nrcc {
    using Vec3 = Vec3<type>;
    using Face = Face<type>;
    using Wave = Wave<type>;
    using Path = Path<type>;
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

        if (reflected && reflections > 1) return trace(waves, faces, mesh, reflections - 1);
        else return {waves, faces};
    }

    // CONSTRUCTOR
    explicit Nrcc(const uint8_t &rs) : reflections(rs) {}

    Nrcc() : reflections(2) {}

//private:
    // VECTOR - FACE METHODS
    type intersectionDistance(const Wave &wave, const Face &face) const {
        Vec3 p_vec = cross(wave.direct, face.bounds[1]);

        type det = dot(face.bounds[0], p_vec);

        if (fabs(det) < nrcc::epsilon) return -1;

        Vec3 t_vec = wave.origin - face.points[0];

        type u = dot(t_vec, p_vec) * (1 / det);

        if (u < 0 || u > 1) return -1.0;

        Vec3 q_vec = cross(t_vec, face.bounds[0]);

        type v = dot(wave.direct, q_vec) * (1 / det);

        if (v < 0 || u + v > 1) return -1.0;

        return dot(face.bounds[1], q_vec) * (1 / det);
    }

    Vec3 intersectionVector(const Wave &wave, const Face &face) const {
        return wave.direct * intersectionDistance(wave, face) + wave.origin;
    }

    Vec3 reflectionVector(const Wave &wave, const Face &face) const {
        return wave.direct - face.normal() * 2 * dot(wave.direct, face.normal());
    }

    // VECTOR - SPHERE METHODS
    type intersectionDistance(const Wave &wave, const Vec3 &center, const type &radius) const {
        Vec3 l = wave.origin - center;

        type a = dot(wave.direct, wave.direct);
        type b = 2 * dot(wave.direct, l);
        type c = dot(l, l) - radius * radius;

        type d = b * b - 4 * a * c;

        type t, u;

        if (d < 0) return -1;
        else if (d == 0) return -0.5 * b / a;
        else {
            type q = (b > 0) ? -0.5 * (b + std::sqrt(d)) : -0.5 * (b - std::sqrt(d));

            t = q / a;
            u = c / q;

            if (t < u && t > 0) return t;
            else if (u > 0) return u;
            else return -1;
        }
    }

    Vec3 intersectionVector(const Wave &wave, const Vec3 &center, const type &radius) const {
        return wave.direct * intersectionDistance(wave, center, radius) + wave.origin;
    }

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
};

#endif //NARCCISSUS_NRCC_HPP