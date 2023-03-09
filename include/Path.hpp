// Copyright(c) 2023, Matthew, All rights reserved.

#ifndef NARCCISSUS_PATH_HPP
#define NARCCISSUS_PATH_HPP

#include <vector>
#include <optional>
#include "Ray.hpp"

template<typename type>
class Path {
    using vect = Vector<type>;
    using Face = Face<type>;
    using Ray = Ray<type>;
public:
    std::vector<Ray> rays;
    std::vector<Face> faces;

    int max_reflections;

    void pop() {
        rays.pop_back();
        faces.pop_back();
    }

    void push(const Ray &r, const Face &f) {
        rays.push_back({r});
        faces.push_back(f);
    }

    void trace(const std::vector<Face> &fs) {
        Ray ray = rays.back();
        int tested_reflections = 0;
        type curr_dist = nrcc::infinity;

        // Loop through all surfaces sent to function
        for (const auto &face: fs) {

            // Calculates the distance from the current leading ray to current face
            type test_dist = ray.intersectionDistance(face);

            // If distance is positive and less than last intersect distance, reflect the ray
            if (test_dist < curr_dist && test_dist > 1e-9) {
                Ray resultant{ray.intersectionVector(face), ray.reflectionVector(face)};

                // If further surface has already been intersected, delete data before adding updated intersection
                if (tested_reflections > 0) pop();

                push(resultant, face);

                tested_reflections++;
                curr_dist = test_dist;
            }
        }

        // Recursive call if reflection occurs, and max reflections have not occurred
        if (tested_reflections > 0 && rays.size() <= max_reflections) trace(fs);
    }

    type length(const int &r, const vect &v) {
        type d = 0;

        for (int idx = 0; idx < r; idx++) d += distance((rays[idx + 1]).origin, (rays[idx]).origin);

        return d + distance((rays[r]).origin, v);
    }

    type loss(const int &r, const vect &v) {
        return pow(4 * nrcc::pi * length(r, v) * 1e9 / nrcc::lightspeed, -2);
    }

    type power(const int &r, const vect &v) {}

    Path(const Ray &r) : rays{r}, faces(), max_reflections(2) {}

    Path(const Ray &r, const int &rs) : rays{r}, faces(), max_reflections(rs) {}
};

template<class type>
std::ostream &operator<<(std::ostream &os, Path<type> &p) {
    for (int idx = 0; idx < p.rays.size(); idx++) {
        os << idx << ": " << p.rays[idx] << "\n";
    }
    return os;
}

#endif //NARCCISSUS_PATH_HPP