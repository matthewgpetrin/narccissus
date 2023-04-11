// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#include <fstream>
#include "../src/Wave.hpp"
#include "../src/Pole.hpp"

int main() {
    using Pole = Pole<double>;
    using Wave = Wave<double>;
    using Vec3 = Vec3<double>;

    int tx_waves = 6;
    int tx_count = 8;
    double tx_power = 100000;
    double tx_frequency = 2.4e9;
    double tx_wavelength = nrcc::lightspeed / tx_frequency;

    double rx_size = 0.01;

    std::vector<Vec3> ico = nrcc::icosphere(5);

    std::vector<double> phases = {1.2022, 2.9025, 2.9025, 1.2022, -1.2022, -2.9025, -2.9025, -1.2022};

    std::vector<Pole> poles;
    for (int i = 0; i < tx_count; i++) {
        Vec3 ang = {0, nrcc::pi / 4 * i + 0.3926991};
        std::cout << ang * tx_wavelength / 2 << "\n";
        poles.push_back({ang * tx_wavelength, {0, 0, 1}, 2.4e9, 1});
    }

    std::vector<Wave> waves;
    for (int i = 0; i < poles.size(); i++) {
        double phase = phases[i];
        std::vector<Wave> tx = poles[i].transmit(tx_power, phase, 2, tx_waves);
        for (auto &wave: tx) waves.push_back(wave);
    }

    std::vector<Pole> rxs;
    for (const auto &rx: ico) {
        rxs.push_back({rx, {0, 0, 1}, tx_frequency, rx_size});
    }

    std::vector<Vec3> efs;
    for (auto &rx: rxs) {
        efs.push_back(rx.receive(waves));
    }

    std::ofstream polesc("../data/polesc.txt", std::ofstream::out);
    for (auto &pole: poles) {
        polesc << pole.coordinates << "\n";
    }
    polesc.close();


    std::ofstream points("../data/points.txt", std::ofstream::out);
    for (auto &rx: rxs) {
        points << rx.coordinates << "\n";
    }
    points.close();
    std::cout << waves.size();

    std::ofstream fields("../data/fields.txt", std::ofstream::out);
    for (const auto &ef: efs) {
        fields << ef << "\n";
    }
    fields.close();

    std::ofstream powers("../data/powers.txt", std::ofstream::out);
    for (const auto &ef: efs) {
        powers << ef.norm() << "\n";
    }
    powers.close();

    return 0;
}