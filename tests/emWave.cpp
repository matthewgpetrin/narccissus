// Copyright(c) 2023, Matthew Petrin, All rights reserved.

// Test designed to view EH field changes with time. Adjusting polar will result in varied waveforms.
// Console output is formatted to be easily pasted into the corresponding MATLAB file.

#include "../include/Vec3.hpp"
#include "../include/Wave.hpp"

int main() {
    using VecC = Vec3<std::complex<double>>;
    using Vec3 = Vec3<double>;
    using Wave = Wave<double>;


    VecC polarization = {{0, 0},
                         {1, 0},
                         {0, 0}};

    Vec3 direction = {1,
                      0,
                      0};

    Wave wave = {{0, 0, 0}, direction, 1, 2.4e9, 0, polarization};

    std::vector<double> distances;

    for (int i = 0; i < 500; i++) {
        distances.push_back(i * 0.001);
    }

    std::cout << "d = [";
    for (const auto &distance: distances) {
        std::cout << distance << ", 0, 0;\n";
    }
    std::cout << "]; \n\n";

    std::cout << "e = [";
    for (const auto &distance: distances) {
        std::cout << real(wave.electricField(direction * distance)) << "\n";
    }
    std::cout << "]; \n\n";

    std::cout << "h = [";
    for (const auto &distance: distances) {
        std::cout << real(wave.magneticField(direction * distance)) << "\n";
    }
    std::cout << "]; \n\n";
}