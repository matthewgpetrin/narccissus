// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_FACE_HPP
#define NARCCISSUS_FACE_HPP

#include <unordered_set>
#include "Vec3.hpp"
#include "Util.hpp"

template<typename type>
struct Face {
    using Vec3 = Vec3<type>;

    // VARIABLES
    std::array<Vec3, 3> points;
    std::array<Vec3, 2> bounds;

    nrcc::Materials material;

    // METHODS
    Vec3 normal() const {
        return cross(bounds[0], bounds[1]).unit();
    }

    // CONSTRUCTORS
    Face(const std::array<Vec3, 3> &ps) :
            points(ps),
            bounds{ps[2] - ps[0], ps[2] - ps[1]},
            material(nrcc::concrete) {}

    Face(const Vec3 &p, const Vec3 &q, const Vec3 &r) :
            points{p, q, r},
            bounds{q - p, r - p},
            material(nrcc::concrete) {}

    Face(const std::array<Vec3, 3> &ps, const nrcc::Materials &material) :
            points(ps),
            bounds{ps[2] - ps[0], ps[2] - ps[1]},
            material(material) {}

    Face(const Vec3 &p, const Vec3 &q, const Vec3 &r, const nrcc::Materials material) :
            points{p, q, r},
            bounds{q - p, r - p},
            material(material) {}

    std::complex<type> refractiveIndex(const type &frequency) const {
        type n = nrcc::permittivity[material][0] * std::pow(frequency, nrcc::permittivity[material][1]);

        type c = nrcc::conductivity[material][0] * std::pow(frequency, nrcc::conductivity[material][1]);

        type k = 17.98 * c / frequency;

        return {n, k};
    }
    // https://www.itu.int/dms_pubrec/itu-r/rec/p/R-REC-P.2040-1-201507-S!!PDF-E.pdf
};

struct hash {
    std::size_t operator()(const std::array<uint64_t, 4> &face) const {
        std::size_t h = std::hash<uint64_t>{}(face[0]);
        std::size_t i = std::hash<uint64_t>{}(face[1]);
        std::size_t j = std::hash<uint64_t>{}(face[2]);
        h ^= (i << 1);
        h ^= (j << 2);
        return h * 31;
    }
};

template<typename type>
std::vector<Face<type>> read(std::ifstream mesh) {
    if (!mesh) {

        std::cerr << "Error: Could not open file\n";
    }

    std::vector<Vec3<type>> vertices;
    std::vector<std::string> materials;
    std::vector<std::array<uint64_t, 4>> indices;

    int normals = -1;
    char slash = '/';
    std::string garbage;

    std::string line;
    while (std::getline(mesh, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream ss_vertex(line.substr(2));
            type x, y, z;
            ss_vertex >> x >> y >> z;
            vertices.push_back({x, y, z});
        } else if (line.substr(0, 7) == "usemtl ") {
            std::istringstream ss_material(line.substr(7));
            std::string material;
            ss_material >> material;
            materials.push_back(material);
        } else if (line.substr(0, 2) == "f ") {
            std::istringstream ss_indices(line.substr(2));
            uint64_t i, j, k;
            ss_indices >> i;
            switch (normals) {
                case 0:
                    ss_indices >> j >> k;
                    break;
                case 1:
                    ss_indices >> slash >> garbage >> j >> slash >> garbage >> k;
                    break;
                case 2:
                    ss_indices >> slash >> slash >> garbage >> j >> slash >> slash >> garbage >> k;
                    break;
                default:
                    if (ss_indices.peek() != slash) {
                        ss_indices >> j >> k;
                        normals = 0;
                    } else {
                        ss_indices >> slash;
                        if (ss_indices.peek() != slash) {
                            ss_indices >> garbage >> j >> slash >> garbage >> k;
                            normals = 1;
                        } else {
                            ss_indices >> slash >> garbage >> j >> slash >> slash >> garbage >> k;
                            normals = 2;
                        }
                    }
            }
            indices.push_back({i - 1, j - 1, k - 1, static_cast<uint64_t>(materials.size() - 1)});
        }
    }

    std::unordered_set<std::array<uint64_t, 4>, hash> set(indices.begin(), indices.end());

    indices.assign(set.begin(), set.end());

    std::vector<Face<type>> fs;
    for (const auto &idx: indices) {
        uint64_t a = idx[0];
        uint64_t b = idx[1];
        uint64_t c = idx[2];
        Face f = {vertices[a], vertices[b], vertices[c]};
        fs.push_back({vertices[a], vertices[b], vertices[c]});
    }

    return fs;
}

// OSTREAM OVERRIDE
template<typename type>
std::ostream &operator<<(std::ostream &os, const Face<type> &face) {
    os << "[" << face.points[0] << "; " << face.points[1] << "; " << face.points[2] << "];";
    return os;
}

#endif //NARCCISSUS_FACE_HPP