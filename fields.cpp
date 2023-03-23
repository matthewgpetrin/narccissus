
#include "include/Wave.hpp"

Vec3<double> rotate_around_axis(const Vec3<double> &v, const Vec3<double> &axis, double angle) {

    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    double dotp = dot(v, axis);
    Vec3<double> crossp = cross(v, axis);
    Vec3<double> result = {v.x * cos_angle + axis.x * dotp * (1 - cos_angle) +
                           cross(v, axis).x * sin_angle, v.y * cos_angle + axis.y * dotp * (1 - cos_angle) +
                                                         cross(v, axis).y * sin_angle,
                           v.z * cos_angle + axis.z * dotp * (1 - cos_angle) +
                           cross(v, axis).z * sin_angle};
    return result;
}

Vec3<double> rotate_to_axis(const Vec3<double> &v, const Vec3<double> &ref_axis, const Vec3<double> &arb_axis) {
    if (std::abs(dot(v, ref_axis)) == v.norm()) {
        return rotate_around_axis(v, arb_axis, M_PI / 2.0);
    }

    // Compute the projection of the vector v onto the plane perpendicular to the reference axis
    Vec3 v_proj = v - (ref_axis * dot(v, ref_axis));

    // Compute the axis of rotation
    Vec3 k = cross(ref_axis, arb_axis.unit()).unit();

    // Compute the angle of rotation
    double theta = std::acos(dot(v_proj.unit(), arb_axis.unit()));

    // Compute the rotated vector using the Rodrigues' rotation formula
    Vec3 v_rot =
            v_proj * std::cos(theta) + cross(k, v_proj) * std::sin(theta) + k * dot(k, v_proj) * (1 - std::cos(theta));

    return v_rot;
}

std::array<std::array<double, 3>, 3> rotation(const Vec3<double> &v, const Vec3<double> &w) {
    Vec3<double> a = cross(v, w);
    double s = sqrt(dot(a, a));
    double c = dot(v, w);

    double K[3][3] = {{0,    -a.z, a.y},
                      {a.z,  0,    -a.x},
                      {-a.y, a.x,  0}};

    std::array<std::array<double, 3>, 3> rot{};
    for (int n = 0; n < 3; n++) {
        for (int m = 0; m < 3; m++) {
            rot[n][m] = (n == m) ? 1 : 0;
            rot[n][m] = rot[n][m] + K[n][m];
            for (int o = 0; o < 3; o++) rot[n][m] += K[n][o] * K[o][m] * (1 - c) / (s * s);
        }
    }
    return rot;
}

Vec3<double> rotate(const Vec3<double> &v, const Vec3<double> &w) {
    double x = 0;
    double y = 0;
    double z = 0;
    std::array<std::array<double, 3>, 3> rot = rotation(v, w);
    for (int n = 0; n < 3; n++) {
        x += rot[0][n] * v.x;
        y += rot[1][n] * v.y;
        z += rot[2][n] * v.z;
    }
    return {x, y, z};
}

int main() {


    std::complex<double> x(0, 0);
    std::complex<double> y(1, 0);
    std::complex<double> z(1, 0);
    Vec3<std::complex<double>> p = {x, y, z};

    std::complex<double> x2(1, 0);
    std::complex<double> y2(0, 0);
    std::complex<double> z2(0, 0);
    Vec3<std::complex<double>> d = {x2, y2, z2};

    Wave<double> w1 = {{0, 0, 0}, d, 1, 2.4e9, nrcc::pi / 4, p};

    std::cout << "{" << w1.electricField({6.5, 0, 0}).x.real() << ", " << w1.electricField({6.5, 0, 0}).y.real() << ", "
              << w1.electricField({6.5, 0, 0}).z.real() << "} \n ";


    //Vec3<double> a = {0, 0, 1};
    //Vec3<double> b = {1.0, 0, 1};

    //Vec3<double> r = nrcc::rodrigues(a, {1, 0, 0}, b);

    //std::cout << "adWDWD " << r << " adw DAWD ";
    //std::cout << "adWDWD " << r << " adw DAWD ";

    Vec3<double> v = {0, 1, 1}; // Original vector
    Vec3<double> ref_axis = {1, 0, 0}; // Reference axis
    Vec3<double> arb_axis = {1, 1, 1}; // Arbitrary axis
    Vec3<double> v_rot = rotate_to_axis(v, ref_axis, arb_axis); // Rotated vector
    std::cout << "Original vector: (" << v.x << ", " << v.y << ", " << v.z << ")\n";
    std::cout << "Rotated vector: (" << v_rot.x << ", " << v_rot.y << ", " << v_rot.z << ")\n";
    std::cout << "Orthognal???: (" << dot(v_rot, arb_axis) << ")\n";
    std::cout << "Orthognal???: (" << dot(ref_axis, v) << ")\n";

    Vec3<double> v1 = rotate({1, 0, 0}, {1, 0, 1});
    std::cout << "\n ROTATE: " << v1;
}