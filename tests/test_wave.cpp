// Copyright(c) 2023, Matthew Petrin, All rights reserved.

// Test designed to view EH field changes with time. Adjusting polar will result in varied waveforms.
// Output files can be read by matlab functions in /tools/

#include <fstream>
#include "../src/Vec3.hpp"
#include "../src/Wave.hpp"

int main() {
    using VecC = Vec3<std::complex<double>>;
    using Vec3 = Vec3<double>;
    using Wave = Wave<double>;


    VecC polarization = {{0,  0},
                         {0,  1},
                         {.9, 0}};

    Vec3 direction = {1,
                      0,
                      0};

    Wave wave = {{0, 0, 0}, direction, 1, 2.4e9, 0, polarization};

    std::vector<double> distances;
    for (int i = 0; i < 500; i++) {
        distances.push_back(i * 0.001);
    }

    std::ofstream dists("../data/waves_d.txt", std::ofstream::out);
    if (!dists.is_open()) {
        std::cerr << "Could not open waves_d.txt" << "\n";
        return 1;
    }
    for (const auto &distance: distances) {
        dists << direction * distance << "\n";
    }
    dists.close();

    std::ofstream eles("../data/waves_e.txt", std::ofstream::out);
    if (!eles.is_open()) {
        std::cerr << "Could not open waves_e.txt" << "\n";
        return 2;
    }
    for (const auto &distance: distances) {
        eles << wave.electricField(direction * distance).real() << "\n";
    }
    eles.close();

    std::ofstream mags("../data/waves_m.txt", std::ofstream::out);
    if (!mags.is_open()) {
        std::cerr << "Could not open waves_m.txt" << "\n";
        return 3;
    }
    for (const auto &distance: distances) {
        mags << wave.magneticField(direction * distance).real() << "\n";
    }
    mags.close();

    return 0;
}