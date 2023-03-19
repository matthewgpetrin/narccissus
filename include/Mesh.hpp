// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_MESH_HPP
#define NARCCISSUS_MESH_HPP

#include <vector>
#include <fstream>
#include <unordered_set>

#include "Face.hpp"

template<typename type>
class Mesh {
    using Vec3 = Vec3<type>;
    using Face = Face<type>;
public:
    // VARIABLES
    const std::vector<Face> faces;

    // CONSTRUCTORS
    Mesh(std::ifstream mesh) : faces(read(mesh)) {}

    Mesh(std::vector<Face> faces) : faces(faces) {}

private:
    // METHODS
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

    std::vector<Face> read(std::ifstream &mesh) {
        if (!mesh) {
            std::cerr << "Error: Could not open file\n";
        }

        std::vector<Face> faces;
        std::vector<Vec3> vertices;
        std::vector<std::string> materials;
        std::vector<std::array<uint64_t, 4>> indices;

        int normals = 0;
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
                }
                indices.push_back({i - 1, j - 1, k - 1, static_cast<uint64_t>(materials.size() - 1)});
            }
        }

        std::unordered_set<std::array<uint64_t, 4>, hash> set(indices.begin(), indices.end());

        indices.assign(set.begin(), set.end());

        for (const auto &idx: indices) {
            uint64_t a = idx[0];
            uint64_t b = idx[1];
            uint64_t c = idx[2];
            faces.push_back({vertices[a], vertices[b], vertices[c]});
        }

        return faces;
    }
};

#endif //NARCCISSUS_MESH_HPP