#include "../src/Nrcc.hpp"
#include "../src/Vec3.hpp"

int main() {
    using Vec3 = Vec3<float>;
    using Face = Face<float>;
    using Wave = Wave<float>;
    using Path = Path<float>;
    using Mesh = Mesh<float>;

    Nrcc<float> tracer(2);

    std::vector<Wave> waves;
    std::vector<Path> paths;
    std::vector<Face> faces;

    // DEFINE FACE
    Face t0 = {{-2, 0, 0},
               {-2, 2, 0},
               {-2, 0, 2}};
    Face t1 = {{2, 0,  1},
               {1, -1, 2},
               {1, 1,  2}};
    Face t2 = {{0,  3,  -2},
               {-2, -2, -2},
               {2,  -2, -2}};
    Face t3 = {{2, 0, 0},
               {2, 0, 2},
               {2, 2, 0}};

    // ADD TO FACE VECTOR
    faces.push_back(t0);
    faces.push_back(t1);
    faces.push_back(t2);
    faces.push_back(t3);

    // DEFINE ACCURACY
    uint32_t n_waves = 10000;

    // CREATE MESH FROM FACES
    Mesh mesh{faces};

    for (int i = 0; i < n_waves; i++) {
        waves.push_back({{.5, .5, .5}, randomVector<float>()});
    }

    for (int i = 0; i < n_waves; i++) {
        paths.push_back(tracer.trace(waves[i], mesh));
    }

    std::ofstream origins0("../data/reflects_o0.txt", std::ofstream::out);
    std::ofstream directs0("../data/reflects_d0.txt", std::ofstream::out);
    std::ofstream origins1("../data/reflects_o1.txt", std::ofstream::out);
    std::ofstream directs1("../data/reflects_d1.txt", std::ofstream::out);
    std::ofstream origins2("../data/reflects_o2.txt", std::ofstream::out);
    std::ofstream directs2("../data/reflects_d2.txt", std::ofstream::out);

    for (const auto &path: paths) {
        if (path.waves.size() > 2) {
            origins2 << path.waves[2].origin << "\n";
            directs2 << path.waves[2].direct << "\n";
        }

        if (path.waves.size() > 1) {
            origins1 << path.waves[1].origin << "\n";
            directs1 << path.waves[1].direct << "\n";
        }

        origins0 << path.waves[0].origin << "\n";
        directs0 << path.waves[0].direct << "\n";
    }
    origins0.close();
    directs0.close();
    origins1.close();
    directs1.close();
    origins2.close();
    directs2.close();

    return 0;
}