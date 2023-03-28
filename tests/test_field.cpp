// Copyright(c) 2023, Matthew Petrin, All rights reserved.

// Test designed to visualize dipole far fields calculated by electricField and magneticField.
// Output files can be read by matlab functions in /tools/

#include <fstream>
#include "../src/Wave.hpp"

int main() {
    using VecC = Vec3<std::complex<double>>;
    using Vec3 = Vec3<double>;
    using Wave = Wave<double>;

    uint64_t nWaves = 500;

    VecC polarization = {{0,  0},
                         {0,  0},
                         {-1, 0}};

    std::vector<Vec3> directs;
    for (int i = 0; i < nWaves; i++) {
        directs.push_back(randomVector<double>().unit());
    }

    std::vector<Wave> waves;
    for (int i = 0; i < nWaves; i++) {
        waves.push_back({{0, 0, 0}, directs[i], 1, 2.4e9, 0, polarization});
    }

    std::ofstream origins("../data/fields_o.txt", std::ofstream::out);
    if (!origins.is_open()) {
        std::cerr << "Could not open fields_o.txt" << "\n";
        return 1;
    }
    for (int i = 0; i < nWaves; i++) {
        origins << directs[i].unit() << "\n";
    }
    origins.close();

    std::ofstream electrics("../data/fields_e.txt", std::ofstream::out);
    if (!electrics.is_open()) {
        std::cerr << "Could not open fields_e.txt" << "\n";
        return 2;
    }
    for (int i = 0; i < nWaves; i++) {
        electrics << waves[i].electricField(directs[i]).real().unit() / 2 << "\n";
    }
    electrics.close();

    std::ofstream magnets("../data/fields_m.txt", std::ofstream::out);
    if (!magnets.is_open()) {
        std::cerr << "Could not open fields_m.txt" << "\n";
        return 3;
    }
    for (int i = 0; i < nWaves; i++) {
        magnets << waves[i].magneticField(directs[i]).real().unit() / 2 << "\n";
    }
    magnets.close();

    return 0;
}