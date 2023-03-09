#include "include/Path.hpp"

int main() {
    // TESTING VECTOR
    using vect = Vector<float>;

    std::cout << "\nTESTING VECTOR CONSTRUCTORS\n";

    vect v01{1, 3, 4};
    std::cout << "v01: " << v01 << "\n";

    vect v02 = v01;
    std::cout << "v02: " << v02 << "\n";

    std::cout << "\nTESTING VECTOR OVERLOADS\n";

    std::cout << "v01 + v02: " << v01 + v02 << "\n";
    std::cout << "v01 - v02: " << v01 - v02 << "\n";
    std::cout << "v01 * v02: " << v01 * v02 << "\n";
    std::cout << "v01 / v02: " << v01 / v02 << "\n";

    std::cout << "v01 * 8: " << v01 * 8 << "\n";
    std::cout << "v02 / 5: " << v02 / 5 << "\n";

    std::cout << "\nTESTING VECTOR METHODS\n";

    std::cout << "v01 magnitude: " << v01.magnitude() << "\n";
    std::cout << "v02 normalized: " << v01.unit() << "\n";

    std::cout << "\nTESTING VECTOR FUNCTIONS\n";

    std::cout << "v01 . v02: " << dot(v01, v02) << "\n";
    std::cout << "v01 2 v02: " << distance(v01, v02) << "\n";
    std::cout << "v01 X v02: " << cross(v01, v02) << "\n";

    // TESTING FACE
    using Face = Face<float>;

    std::cout << "\nTESTING FACE CONSTRUCTORS\n";

    std::array<vect, 3> a01 = {{{3, 2, 1}, {4, 2, 1}, {5, 1, 3}}};
    Face f01{a01};
    std::cout << "f01: " << f01 << "\n";

    Face f02{{3, 6, 1},
             {3, 1, 7},
             {5, 2, 1}};
    std::cout << "f02: " << f02 << "\n";

    // TESTING RAY
    using Ray = Ray<float>;

    std::cout << "\nTESTING RAY CONSTRUCTORS\n";

    Ray r01{{1, 0, 1},
            {1, 0, 0}};
    std::cout << "r01: " << r01 << "\n";

    std::cout << "\nTESTING RAY METHODS\n";

    Face f03{{3, 2,  0},
             {7, 0,  3},
             {5, -2, 0}};
    std::cout << "f03: " << f03 << "\n\n";

    std::cout << "int dist: " << r01.intersectionDistance(f03) << "\n";
    std::cout << "int vect: " << r01.intersectionVector(f03) << "\n";
    std::cout << "ref vect: " << r01.reflectionVector(f03) << "\n";

    //TESTING PATH
    using Path = Path<float>;

    std::cout << "\nTESTING PATH CONSTRUCTORS\n";

    Path p02{r01};
    std::cout << "p01: \n" << p02 << "\n";

    std::cout << "\nTESTING PATH TRACING\n";

    Face f04{{7,   2,    5},
             {0,   0,    5},
             {5.3, -4.7, 4}};

    std::vector<Face> fs01;
    fs01.push_back(f04);
    fs01.push_back(f03);

    p02.trace(fs01);
    std::cout << "p01: \n" << p02 << "\n";

    std::cout << "path loss at 2: " << p02.loss(0, {100, 0, 1});

    // TESTING OBJ READING
    std::cout << "\nTESTING FILE READING\n";

    std::vector<Face> scene{read<float>(std::ifstream("../diamond.obj"))};

    for (int i = 0; i < scene.size(); i++) {
        std::cout << "tri " << i << ": " << scene[i] << "\n";
    }

    return 0;
}