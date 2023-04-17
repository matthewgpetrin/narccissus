// Copyright(c) 2023, Matthew Petrin, All rights reserved.

#include <fstream>
#include <chrono>
#include "../src/Vec3.hpp"
#include "../src/Wave.hpp"
#include "../src/Nrcc.hpp"
#include "../src/Pole.hpp"
#include "../src/Face.hpp"


int main() {

    auto start = std::chrono::high_resolution_clock::now();

    Pole<double> pole = {{10, 30, 30}, {0, 0, 1}, 2.4e9, 1};
    std::vector<Wave<double>> waves = pole.transmit(1, 0, 2, 4);

    //std::vector<Face<double>> mesh = {{{-2, -2, -2}, {2,  -2, -2}, {0,  2, -2}},
    //                                  {{4,  -1, -1}, {4,  -1, 2},  {4,  1, -1}},
    //                                  {{-7, -1, -1}, {-8, -1, 2},  {-9, 1, -1}},
    //                                  {{7,  -1, -1}, {8,  -1, 2},  {9,  1, -1}}};
    std::vector<Face<double>> mesh{read<double>((std::ifstream) "../data/stevens.obj")};


    Nrcc<double> tracer;
    std::vector<Wave<double>> blah;
    for (Wave<double> &wave: waves) {
        std::vector<Wave<double>> temp = tracer.trace(wave, mesh, 2);
        blah.insert(blah.end(), temp.begin(), temp.end());
    }

    std::cout << mesh[0];

//    std::ofstream txverts("../data/txverts.txt", std::ofstream::out);
//    for (const auto &wave: blah) {
//        txverts << wave.origin << "\n";
//    }
//    txverts.close();

//    std::ofstream txdirs("../data/txdirs.txt", std::ofstream::out);
//    for (const auto &wave: blah) {
//        txdirs << wave.direct << "\n";
//    }
//    txdirs.close();

//    std::ofstream txtype("../data/txtype.txt", std::ofstream::out);
//    for (const auto &wave: blah) {
//        if (wave.genesis.interaction == nrcc::emission) txtype << "r" << "\n";
//        if (wave.genesis.interaction == nrcc::refraction) txtype << "g" << "\n";
//        if (wave.genesis.interaction == nrcc::reflection) txtype << "b" << "\n";
//    }
//    txtype.close();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << mesh.size() << "\n";
    std::cout << waves.size() << "\n";
    std::cout << "double time" << duration.count() << "\n\n";

}