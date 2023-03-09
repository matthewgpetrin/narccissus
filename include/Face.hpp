#ifndef NARCCISSUS_FACE_HPP
#define NARCCISSUS_FACE_HPP

#include <array>
#include <fstream>
#include <unordered_set>

#include "Vector.hpp"

template<typename type>
class Face {
    using vect = Vector<type>;
public:
    const std::array<vect, 3> points;
    const std::array<vect, 2> edges;

    vect normal() const {
        return cross(edges[0], edges[1]).unit();
    }

    Face(const std::array<vect, 3> &v) : points{v}, edges{v[2] - v[0], v[2] - v[1]} {}

    Face(const vect &p, const vect &q, const vect &r) : points{{p, q, r}}, edges{r - p, q - p} {}
};

template<typename type>
std::ostream &operator<<(std::ostream &os, const Face<type> &f) {
    os << "[" << f.points[0] << ", " << f.points[1] << ", " << f.points[2] << "];   " << f.normal();
    return os;
}

struct hash {
    std::size_t operator()(const std::array<uint64_t, 4> &face) const {
        std::size_t h0 = std::hash<uint64_t>{}(face[0]);
        std::size_t h1 = std::hash<uint64_t>{}(face[1]);
        std::size_t h2 = std::hash<uint64_t>{}(face[2]);
        h0 ^= (h1 << 1);
        h0 ^= (h2 << 2);
        return h0 * 31;
    }
};

template<typename type>
std::vector<Face<type>> read(std::ifstream obj) {
    using Face = Face<type>;
    if (!obj) {
        std::cerr << "Error: Could not open file\n";
        //return 1;
    }

    std::vector<std::string> materials;
    std::vector<Vector<type>> vertices;
    std::vector<std::array<uint64_t, 4>> indices;

    int normals = 0;
    std::string line;
    while (std::getline(obj, line)) {
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
            switch (normals) {
                case 1:
                    ss_indices >> i >> j >> k;
                    indices.push_back({i - 1, j - 1, k - 1, static_cast<uint64_t>(materials.size() - 1)});
                    break;
                case 2:
                    char x;
                    ss_indices >> i >> x >> x >> x >> j >> x >> x >> x >> k;
                    indices.push_back({i - 1, j - 1, k - 1, static_cast<uint64_t>(materials.size() - 1)});
                    break;
                default:
                    ss_indices >> i;
                    if (ss_indices.peek() != '/') {
                        ss_indices >> j >> k;
                        normals = 1;
                    } else {
                        ss_indices >> x >> x >> x >> j >> x >> x >> x >> k;
                        normals = 2;
                    }
                    break;
            }
            indices.push_back({i - 1, j - 1, k - 1, static_cast<uint64_t>(materials.size() - 1)});
        }
    }

    std::unordered_set<std::array<uint64_t, 4>, hash> set(indices.begin(), indices.end());
    indices.assign(set.begin(), set.end());

    std::vector<Face> faces;
    for (const auto &idx: indices) {
        uint64_t a{idx[0]};
        uint64_t b{idx[1]};
        uint64_t c{idx[2]};
        Face f{vertices[a], vertices[b], vertices[c]};
        faces.push_back(f);
    }

    return faces;
}

#endif //NARCCISSUS_FACE_HPP