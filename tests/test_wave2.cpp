// Copyright(c) 2023, Matthew Petrin, All rights reserved.

// Test designed to view EH field changes with time. Adjusting polar will result in varied waveforms.
// Output files can be read by matlab functions in /tools/

#include <fstream>
#include "../src/Vec3.hpp"
#include "../src/Wave.hpp"
#include "../src/Nrcc.hpp"

int main() {
    using VecC = Vec3<std::complex<double>>;
    using Vec3 = Vec3<double>;
    using Wave = Wave<double>;


    Wave parent = {{0, 0, 0}, {1, 0, 0}, 5, 2.4e9, 0, nrcc::linear<double>};

    Face<double> face = {{0, -1, 0},
                         {1, -1, 2},
                         {3, 1,  0}};

    Wave child = {{2, 0, 0}, {0, 1, 0}, &parent, &face, nrcc::reflection};

    double r = 100;

    std::cout << "a: " << child.amplitude(r) << "\n";
    std::cout << "t: " << child.phase(r) << "\n";
    std::cout << "p: " << child.polarization(r) << "\n";
    std::cout << dot(child.direct, child.polarization(r).real());

    return 0;
}