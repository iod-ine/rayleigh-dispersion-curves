//
// Created by Ivan Dubrovin on 22.04.2020.
//

#include "rayleigh.h"

double RayleighDispersionFunction(const Medium &m, double c, double f) {
    Matrix<double, 6, 6> A;

    A = Matrix<double, 6, 6>::Identity();
    for (auto Layer : m.Layers) {
        A = A * RayleighLayerMatrix(Layer, c, f);
    }

    double L1, L2, L3, L4, L5, L6;
    double H1, H2, H3, H4, H5, H6;

    L1 = A(0, 0);
    L2 = A(1, 0);
    L3 = A(2, 0);
    L4 = A(3, 0);
    L5 = A(4, 0);
    L6 = A(5, 0);

    // these are the expressions for the halfspace.
    // no need to deal with the imaginary values: we assume that
    // phase velocity is always less than the velocity in the halfspace,
    // since otherwise the boundary condition at infinite depth is broken.
    // values of phase velocity greater will yield complex dispersion function values.

    const double r = sqrt(1 - c * c / m.Vp / m.Vp);
    const double s = sqrt(1 - c * c / m.Vs / m.Vs);
    const double g = 2 * m.Vs * m.Vs / c / c;
    const double d = g - 1;

    H1 = m.Rho * (g * g * r * s - d * d);
    H2 = -m.Rho * r;
    H3 = H4 = m.Rho * (g * r * s - d);
    H5 = -m.Rho * s;
    H6 = 1 - r * s;

    return L1 * H1 + L2 * H2 + L3 * H3 + L4 * H4 + L5 * H5 + L6 * H6;
}
