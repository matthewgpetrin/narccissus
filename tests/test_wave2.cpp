// Copyright(c) 2023, Matthew Petrin, All rights reserved.

// Test designed to view EH field changes with time. Adjusting polar will result in varied waveforms.
// Output files can be read by matlab functions in /tools/

#include <fstream>
#include "../src/Vec3.hpp"
#include "../src/Wave.hpp"
#include "../src/Nrcc.hpp"

int main() {
    using Vec3 = Vec3<double>;
    using Wave = Wave<double>;

    Wave parent = {{0, 0, 0}, {1, -.10, .2}, 1e9, 1, 0, nrcc::polarization::linear};

    Nrcc<double> rt = {};

    Face<double> face = {{5, -1, -1},
                         {6, -1, 2},
                         {7, 1,  -1}};

    Wave reflection = {rt.intersectionVector(parent, face), rt.reflectionVector(parent, face), &parent, &face,
                       nrcc::reflection};

    Wave refraction = {rt.intersectionVector(parent, face), rt.refractionVector(parent, face), &parent, &face,
                       nrcc::refraction};

    double r = rt.intersectionDistance(parent, face);

    std::cout << "a reflect: " << reflection.amplitude(r) << "\n";
    std::cout << "t reflect: " << reflection.phase(r) << "\n";
    std::cout << "p reflect: " << reflection.polar(r) << "\n";

    std::cout << "a refract: " << refraction.amplitude(r) << "\n";
    std::cout << "t refract: " << refraction.phase(r) << "\n";
    std::cout << "p refract: " << refraction.polar(r) << "\n";

    // make list of distances
    std::vector<double> distances;
    for (int i = 0; i < rt.intersectionVector(parent, face).norm() / .001; i++) {
        distances.push_back(i * 0.001);
    }

    std::ofstream wave_0_e_o("../data/wave_0_e_o.txt", std::ofstream::out);
    std::ofstream wave_0_e_d("../data/wave_0_e_d.txt", std::ofstream::out);
    for (const auto &distance: distances) {
        Vec3 point_i = parent.direct.unit() * distance + parent.origin;
        Vec3 field_i = parent.electricField(distance).real() * 0.1;
        wave_0_e_o << point_i << "\n";
        wave_0_e_d << field_i << "\n";
    }
    wave_0_e_o.close();
    wave_0_e_d.close();

    std::ofstream wave_0_m_o("../data/wave_0_m_o.txt", std::ofstream::out);
    std::ofstream wave_0_m_d("../data/wave_0_m_d.txt", std::ofstream::out);
    for (const auto &distance: distances) {
        Vec3 point_i = parent.direct.unit() * distance + parent.origin;
        Vec3 field_i = parent.magneticField(distance).real() * 0.1;
        wave_0_m_o << point_i << "\n";
        wave_0_m_d << field_i << "\n";
    }
    wave_0_m_o.close();
    wave_0_m_d.close();

    std::ofstream wave_1_e_o("../data/wave_1_e_o.txt", std::ofstream::out);
    std::ofstream wave_1_e_d("../data/wave_1_e_d.txt", std::ofstream::out);
    for (const auto &distance: distances) {
        Vec3 point_i = reflection.direct.unit() * distance + reflection.origin;
        Vec3 field_i = reflection.electricField(distance).real() * 0.1;
        wave_1_e_o << point_i << "\n";
        wave_1_e_d << field_i << "\n";
    }
    wave_1_e_o.close();
    wave_1_e_d.close();

    std::ofstream wave_1_m_o("../data/wave_1_m_o.txt", std::ofstream::out);
    std::ofstream wave_1_m_d("../data/wave_1_m_d.txt", std::ofstream::out);
    for (const auto &distance: distances) {
        Vec3 point_i = reflection.direct.unit() * distance + reflection.origin;
        Vec3 field_i = reflection.magneticField(distance).real() * 0.1;
        wave_1_m_o << point_i << "\n";
        wave_1_m_d << field_i << "\n";
    }
    wave_1_m_o.close();
    wave_1_m_d.close();

    std::ofstream wave_2_e_o("../data/wave_2_e_o.txt", std::ofstream::out);
    std::ofstream wave_2_e_d("../data/wave_2_e_d.txt", std::ofstream::out);
    for (const auto &distance: distances) {
        Vec3 point_i = refraction.direct.unit() * distance + refraction.origin;
        Vec3 field_i = refraction.electricField(distance).real() * 0.1;
        wave_2_e_o << point_i << "\n";
        wave_2_e_d << field_i << "\n";
    }
    wave_2_e_o.close();
    wave_2_e_d.close();

    std::ofstream wave_2_m_o("../data/wave_2_m_o.txt", std::ofstream::out);
    std::ofstream wave_2_m_d("../data/wave_2_m_d.txt", std::ofstream::out);
    for (const auto &distance: distances) {
        Vec3 point_i = refraction.direct.unit() * distance + refraction.origin;
        Vec3 field_i = refraction.magneticField(distance).real() * 0.1;
        wave_2_m_o << point_i << "\n";
        wave_2_m_d << field_i << "\n";
    }
    wave_2_m_o.close();
    wave_2_m_d.close();

    return 0;
}