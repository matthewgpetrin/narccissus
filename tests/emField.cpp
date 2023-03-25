// Copyright(c) 2023, Matthew Petrin, All rights reserved.

// Test designed to visualize dipole far fields calculated by electricField and magneticField.
// Console output is formatted to be easily pasted into the corresponding MATLAB file.

#include "../include/Wave.hpp"
#include "../include/Util.hpp"

int main() {
    using VecC = Vec3<std::complex<double>>;
    using Vec3 = Vec3<double>;
    using Wave = Wave<double>;

    VecC polarization = {{1,   0},
                         {0.0, .99},
                         {0,   0}};

    std::vector<Vec3> directs;

    for (int i = 0; i < 500; i++) {
        directs.push_back(randomVector<double>().unit() * 3);
    }

    std::vector<Wave> waves;

    for (int i = 0; i < 500; i++) {
        waves.push_back({{0, 0, 0}, directs[i], 1, 2.4e9, 0, polarization});
    }

    std::cout << "a = [";
    for (int i = 0; i < 500; i++) {
        std::cout << directs[i] << "\n" << directs[i] << "\n";
    }
    std::cout << "]; \n\n";

    std::cout << "b = [";
    for (int i = 0; i < 500; i++) {
        std::cout << real(waves[i].electricField(directs[i])).unit() << "\n";
        std::cout << real(waves[i].magneticField(directs[i])).unit() << "\n";
    }
    std::cout << "]; \n\n";

    return 0;
}