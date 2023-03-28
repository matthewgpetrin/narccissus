// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_PATH_HPP
#define NARCCISSUS_PATH_HPP

#include <vector>

#include "Wave.hpp"
#include "Face.hpp"

template<typename type>
class Path {
    using Wave = Wave<type>;
    using Face = Face<type>;

public:
    // VARIABLES
    std::vector<Wave> waves;
    std::vector<Face> faces;

    // CONSTRUCTORS
    Path(const Wave &wave) : waves{wave} {}

    Path(const std::vector<Wave> &waves, const std::vector<Face> &faces) : waves(waves), faces(faces) {}

    const std::vector<Wave> &getWaves() const {
        return waves;
    }

    const std::vector<Face> &getFaces() const {
        return faces;
    }

private:
    // METHODS
    void pop() {
        waves.pop_back();
        faces.pop_back();
    }

    void push(const Wave &wave, const Face &face) {
        waves.push_back(wave);
        faces.push_back(face);
    }
};

// OSTREAM
template<class T>
std::ostream &operator<<(std::ostream &os, Path<T> &path) {
    for (int idx = 0; idx < path.waves.size(); idx++) os << idx << ": " << path.waves[idx] << "\n";
    return os;
}

#endif //NARCCISSUS_PATH_HPP