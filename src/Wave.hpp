// Copyright(c) 2023, Matthew Petrin, All rights reserved.

// Wave class with ray representation. Geometry (origin, direction) is computed on creation. Electromagnetic properties
// are only initialized in origin or parent waves. Waves resulting from optical interaction exist with -7 initialized
// variables until explicitly requested to save on computation. Upon request, wave will compute and save its EM
// characteristics based on the "genesis" struct, which contains its parent wave, parent face, origin type, and distance
// from its parent wave's origin. Requests for EM characteristics call on parent waves recursively.
//
// Waves may either be constructed as parent waves, in which case the genesis variables are null, or as child waves, in
// which case the initial variables are initialized as impossible values.

#ifndef NARCCISSUS_WAVE_HPP
#define NARCCISSUS_WAVE_HPP

#include "Face.hpp"

template<typename type>
class Wave {
    using cmpx = std::complex<type>;
    using VecC = Vec3<cmpx>;
    using Vec3 = Vec3<type>;
    using Face = Face<type>;

public:
    // VARIABLES
    const Vec3 origin;
    const Vec3 direct;

    struct {
        type frequency;
        type amplitude;
        type phase;
        VecC polarization;
    } initial;

    struct {
        Wave *wave;
        Face *face;
        const type distance;
        const nrcc::Interaction interaction;
    } genesis;

public:
    // ELECTROMAGNETIC PROPERTIES
    // Note that in this implementation, only phase is actually distance dependent. Frequency shift based on interacting
    // surface should be added eventually. Additionally, amplitude and polarization have the potential to change in
    // more complex mediums than air.
    //
    // These functions first check if the "initial" values have been initialized. If not, they call the initializeEm()
    // function, which will compute and store the "initial" values for future use.

    type frequency(const type &r) {
        if (initial.frequency == -7.0) initializeEm();

        return initial.frequency;
    }

    type amplitude(const type &r) {
        if (initial.amplitude == -7.0) initializeEm();

        type a = 0;
        return initial.amplitude * std::exp(-a * r);
    }

    cmpx phase(const type &r) {
        if (initial.amplitude == -7.0) initializeEm();

        return std::exp(initial.phase + nrcc::j * wavenumber(r) * r);
    }

    VecC polarization(const type &r) {
        if (initial.amplitude == -7.0) initializeEm();

        return initial.polarization;
    }

    // Polarization is represented as vector of complex numbers. The real and imaginary components represent
    // a linear combination of two vectors that are orthogonal to each other. This, when included in the
    // calculation for the E and H fields allows for the phase to react to non linear polarizations that rotate with phase
    //
    // Examples:
    // {0, 1, 0} j{0, 0, 0} Linearly polarized horizontally
    // {0, 0, 1} j{0, 0, 0} Linearly polarized vertically
    // {0, 0, 1} j{0, 1, 0} Circular polarized clockwise
    // {0, 0, 2} j{0, 1, 0} Elliptically polarized clockwise
    //
    // Note that the input parameters assume a ray with direction {1, 0, 0}. This is for ease of use, the actual
    // vectors of the polar are computed in the initializer list using shifted().

    // FREQUENCY DEPENDENT PROPERTIES
    type wavelength(const type &r) {
        if (initial.frequency == -7) initializeEm();

        return nrcc::lightspeed / frequency(r);
    }

    type wavenumber(const type &r) {
        return 2 * nrcc::pi / wavelength(r);
    }

    Vec3 wavevector(const type &r) {
        return direct * wavenumber();
    }

    // FIELD VECTOR METHODS
    VecC electricField(const type &r) {
        return polarization(r) * phase(r) * amplitude(r);
    }                                                                             // TODO: CHECK IF THIS SHOULD BE NEGATIVE OR NOT

    VecC magneticField(const type &r) {
        //return cross(electricField(r), wavevector(r)) / 377;
        return cross(electricField(r), direct); // Inaccurate used for visualization
    }

    // EM PROPERTY INITIALIZER
    void initializeEm() {
        // INITIALIZE FREQUENCY
        initial.frequency = genesis.wave->frequency(genesis.distance);

        // CALCULATE EH FIELD (FRESNEL EQUATIONS)
        Vec3 n = genesis.face->normal();
        Vec3 t = genesis.face->bounds[0];
        VecC nc = {{n.x, 0},
                   {n.y, 0},
                   {n.z, 0}};

        VecC Ei = genesis.wave->electricField(genesis.distance);

        cmpx ni = {1, 0};
        cmpx nt = {genesis.face->refractiveIndex(initial.frequency).real(), 0};

        cmpx cos_i = dot(Ei, n);
        cmpx sin_i = std::sqrt(cmpx(1.0) - cos_i * cos_i);

        cmpx sin_t = ni / nt * sin_i;
        cmpx cos_t = std::sqrt(cmpx(1.0) - sin_t * sin_t);

        cmpx Rp = std::pow((ni * cos_i - nt * cos_t) / (ni * cos_i + nt * cos_t), 2);
        cmpx Rs = std::pow((nt * cos_i - ni * cos_t) / (nt * cos_i + ni * cos_t), 2);

        VecC Es = cross(Ei, t);
        VecC Ep = Ei - Es * nc;

        VecC Er = Es * Rs + Ep * Rp;

        // INITIALIZE INITIAL VARIABLES
        initial.amplitude = Er.real().norm();

        initial.phase = std::atan2(dot(Er.imag(), Er.real()), Er.real().norm());

        initial.polarization = shift(Er.unit(), direct);
    }

    // PARENT WAVE CONSTRUCTOR
    Wave(const Vec3 &o,
         const Vec3 &d,
         const type &A,
         const type &f,
         const type &t,
         const VecC &p) :
            origin(o),
            direct(d),
            initial{f, A, t, shift(p, d)},
            genesis{nullptr, nullptr, 0, nrcc::emission} {}

    // CHILD WAVE CONSTRUCTOR
    Wave(const Vec3 &o,
         const Vec3 &d,
         Wave *w,
         Face *f,
         const nrcc::Interaction i) :
            origin(o),
            direct(d),
            genesis{w, f, distance(w->origin, o), i},
            initial{-7.0, -7.0, -7.0} {}
};

// OSTREAM
template<typename T>
std::ostream &operator<<(std::ostream &os, const Wave<T> &wave) {
    os << "[" << wave.origin << ", " << wave.direct << "]";
    return os;
}

#endif //NARCCISSUS_WAVE_HPP