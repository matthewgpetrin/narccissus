#include "include/Vec3.hpp"
#include "include/Face.hpp"
#include "include/Mesh.hpp"
#include "include/Wave.hpp"
#include "include/Path.hpp"
#include "include/Nrcc.hpp"

int main() {
    // TESTING VEC3
    using Vec3 = Vec3<float>;

    std::cout << "\nTESTING VECTOR CONSTRUCTORS\n";

    Vec3 v01 = {1.0, 3.0, 4.0};
    std::cout << "v01: " << v01 << "\n";

    Vec3 v02 = v01;
    std::cout << "v02: " << v02 << "\n";

    Vec3 v03 = {0.8f, 0.8f};
    std::cout << "v01: " << v03 << "\n";

    std::cout << "\nTESTING VECTOR OVERLOADS\n";

    std::cout << "v01 + v03: " << v01 + v03 << "\n";
    std::cout << "v01 - v03: " << v01 - v03 << "\n";
    std::cout << "v01 * v03: " << v01 * v03 << "\n";
    std::cout << "v01 / v03: " << v01 / v03 << "\n";

    std::cout << "v01 * 8: " << v01 * 8 << "\n";
    std::cout << "v03 / 5: " << v03 / 5 << "\n";

    std::cout << "\nTESTING VECTOR METHODS\n";

    std::cout << "v03 spherical: {" << v03.EL() << ", " << v03.AZ() << "}\n";

    std::cout << "v01 norm: " << v01.norm() << "\n";
    std::cout << "v03 unit: " << v03.unit() << "\n";

    std::cout << "\nTESTING COORDINATE FUNCTIONS\n";

    std::cout << "v03 pole: {" << spherical(v03)[0] << ", " << spherical(v03)[1] << "}\n";
    std::cout << "v03 cart: {" << cartesian(0.8, 0.8)[0]
              << ", " << cartesian(0.8, 0.8)[1]
              << ", " << cartesian(0.8, 0.8)[2] << "}\n";

    std::cout << "\nTESTING VECTOR FUNCTIONS\n";

    std::cout << "v01 . v02: " << dot(v01, v02) << "\n";
    std::cout << "v01 2 v02: " << distance(v01, v03) << "\n";
    std::cout << "v01 X v02: " << cross(v01, v02) << "\n";

    // TESTING FACE
    using Face = Face<float>;

    std::cout << "\nTESTING FACE CONSTRUCTORS\n";

    std::array<Vec3, 3> a01 = {{{3, 2, 1}, {4, 2, 1}, {5, 1, 3}}};
    Face f01{a01};
    std::cout << "f01: " << f01 << "\n";

    Face f02 = {{3, 6, 1},
                {3, 1, 7},
                {5, 2, 1}};
    std::cout << "f02: " << f02 << "\n";

    // TESTING MESH
    using Mesh = Mesh<float>;

    std::cout << "\nTESTING FILE READING\n";

    Mesh m01{(std::ifstream) "../magnolia.obj"};

    //for (int i = 0; i < m01.faces.size(); i++) {
    //    std::cout << "tri " << i << ": " << m01.faces[i] << "\n";
    //}

    // TESTING WAVE
    using Wave = Wave<float>;

    std::cout << "\nTESTING RAY CONSTRUCTORS\n";

    Wave w01 = {{1, 0, 1},
                {1, 0, 0}};
    std::cout << "w01: " << w01 << "\n";

    // TESTING PATH
    using Path = Path<float>;

    std::cout << "\nTESTING PATH CONSTRUCTORS\n";

    Path p01 = {w01};
    std::cout << "p01: " << p01;

    // TESTING NRCC
    using Raytracer = Nrcc<float>;

    Raytracer rt01{3};

    std::cout << "\nTESTING RAY FACE METHODS\n";

    Face f03 = {{3, 2,  0},
                {7, 0,  3},
                {5, -2, 0}};
    std::cout << "f03: " << f03 << "\n\n";

    std::cout << "int dist: " << rt01.intersectionDistance(w01, f03) << "\n";
    std::cout << "int vect: " << rt01.intersectionVector(w01, f03) << "\n";
    std::cout << "ref vect: " << rt01.reflectionVector(w01, f03) << "\n";

    std::cout << "\nTESTING RAY SPHERE METHODS\n";

    Vec3 center = {5, 0, 1};
    float radius = 1;

    std::cout << "int dist: " << rt01.intersectionDistance(w01, center, radius) << "\n";
    std::cout << "int vect: " << rt01.intersectionVector(w01, center, radius) << "\n";

    std::cout << "\nTESTING TRACE\n";

    Face f04{{7,   2,    5},
             {0,   0,    5},
             {5.3, -4.7, 4}};

    Mesh m02 = {{f03, f04}};

    Path p02 = rt01.trace(w01, m02);
    std::cout << "p02: " << p02;

    
}