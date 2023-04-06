// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#include <fstream>
#include "../src/Wave.hpp"
#include "../src/Pole.hpp"

int main() {
    using Pole = Pole<double>;
    using Wave = Wave<double>;

    Pole pole = {{0, 0, 0}, {0, 0, 1}, 2.4e9};
    std::vector<Wave> waves = pole.transmit(10000, 4, 5);

    std::ofstream donut_points("../data/donut_points.txt", std::ofstream::out);
    for (const auto &wave: waves) {
        donut_points << wave.direct * wave.initial.amplitude << "\n";
    }
    donut_points.close();

    std::ofstream donut_powers("../data/donut_powers.txt", std::ofstream::out);
    for (const auto &wave: waves) {
        donut_powers << wave.initial.amplitude << "\n";
    }
    donut_powers.close();

    double power_check = 0;
    for (const auto &wave: waves) {
        power_check += wave.initial.amplitude;
    }
    std::cout << "power: " << power_check;

    return 0;
}