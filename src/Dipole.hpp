// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#ifndef NARCCISSUS_DIPOLE_HPP
#define NARCCISSUS_DIPOLE_HPP

#include <vector>
#include "Nrcc.hpp"
#include "Ray.hpp"

template<typename T>
class Dipole {
    using vect = Vector<T>;
    using Ray = Ray<T>;
private:
    vect center_;
    T radius_;
public:
    explicit Dipole(const vect &center) : center_(center) {}

    std::vector<Ray> transmit(const uint64_t &n) {
        std::vector<Ray> rays;

        for (int idx = 0; idx < n; idx++) {
            T az = std::asin((2.0 * idx - (float) n - 1.0) / (n + 1.0));
            T al = nrcc::golden_angle * idx;
            rays.push_back({center_, az, al});
        }

        return rays;
    }

    const vect &center() const {
        return center_;
    }

    T radius() const {
        return radius_;
    }

};

#endif //NARCCISSUS_DIPOLE_HPP
