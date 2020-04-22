//
// Created by Ivan Dubrovin on 22.04.2020.
//

#include "rayleigh.h"

Matrix<double, 6, 6> RayleighLayerMatrix(Layer l, double c, double f) {
    Matrix<double, 6, 6> out;

    const double w = 2 * M_PI * f;
    const double k = w / c;
    const double g = 2 * l.Vs * l.Vs / c / c;
    const double d = g - 1;

    double r, s, P, Q;
    double p1, p2, p3;
    double q1, q2, q3;
    double w1, w2, w3;

    if (c < l.Vs) {
        // when c < Vs, both r and s are imaginary,
        // which means P and Q are also imaginary.
        // however, cos(P) and cos(Q) will be real,
        // whereas sin(P) and sin(Q) are always paired with r and s.
        // where they are divided, j is cancelled, and
        // where they are multiplied, we need to flip the sign

        // in this branch formulas from Novotny are modified to avoid dealing with complex numbers.
        // actual formulas are in the last branch of this if statement.

        r = sqrt(1 - c * c / l.Vp / l.Vp);  // sqrt(x-1) = jsqrt(1-x), so this is purely imaginary
        s = sqrt(1 - c * c / l.Vs / l.Vs);  // so is this

        P = k * r * l.H;  // as a consequence, so is this
        Q = k * s * l.H;  // and this

        p1 = cosh(P);       // cos(jx) = cosh(x)
        p2 = -r * sinh(P);  // ja * sin(jb) = ja * jsinh(b) = - asinh(b)
        p3 = sinh(P) / r;   // sin(jb) / ja = jsinh(b) / ja = sinh(b) / a

        q1 = cosh(Q);       // same here
        q2 = -s * sinh(Q);
        q3 = sinh(Q) / s;

    } else if (c < l.Vp) {
        // when Vs <= c < Vp, r is imaginary, but s is real.
        // here we repeat the substitutions from the last branch, but only for r.

        // also, a special case is c == Vs, because s becomes 0 and values
        // where it is in the denominator need to be manually set to 0

        // in this branch formulas from Novotny are modified to avoid dealing with complex numbers.
        // actual formulas are in the last branch of this if statement.

        r = sqrt(1 - c * c / l.Vp / l.Vp);  // sqrt(x-1) = jsqrt(1-x), so this is again purely imaginary
        s = sqrt(c * c / l.Vs / l.Vs - 1);  // this, however, is now real

        P = k * r * l.H;  // still imaginary
        Q = k * s * l.H;  // real

        p1 = cosh(P);       // cos(jx) = cosh(x)
        p2 = -r * sinh(P);  // ja * sin(jb) = ja * jsinh(b) = - asinh(b)
        p3 = sinh(P) / r;   // sin(jb) / ja = jsinh(b) / ja = sinh(b) / a

        q1 = cos(Q);  // since Q is real, these are what they should be
        q2 = s * sin(Q);
        q3 = c == l.Vs ? 0 : sin(Q) / s;  // here we must check for c == Vs to avoid division by 0

    } else {
        // when Vp <= c, everything is finally real.
        // however, still need to check for c == Vp to avoid division by zero (now with r)

        r = sqrt(c * c / l.Vp / l.Vp - 1);
        s = sqrt(c * c / l.Vs / l.Vs - 1);

        P = k * r * l.H;
        Q = k * s * l.H;

        p1 = cos(P);
        p2 = r * sin(P);
        p3 = c == l.Vp ? 0 : sin(P) / r;

        q1 = cos(Q);
        q2 = s * sin(Q);
        q3 = sin(Q) / s;
    }

    w1 = 1 - p1 * q1;
    w2 = p2 * q2;
    w3 = p3 * q3;

    double a11, a12, a13, a15, a16, a21, a22, a23, a25, a31, a32, a33, a34, a51, a52, a61;

    a11 = -2 * g * d + (2 * g * g - 2 * g + 1) * p1 * q1 - g * g * w2 - d * d * w3;
    a12 = -(p1 * q3 + q1 * p2) / l.Rho;
    a13 = -((g + d) * w1 + g * w2 + d * w3) / l.Rho;
    a15 = -(p1 * q2 + q1 * p3) / l.Rho;
    a16 = (2 * w1 + w2 + w3) / l.Rho / l.Rho;
    a21 = l.Rho * (g * g * p1 * q2 + d * d * q1 * p3);
    a22 = p1 * q1;
    a23 = g * p1 * q2 + d * q1 * p3;
    a25 = -p3 * q2;
    a31 = l.Rho * (g * d * (g + d) * w1 + g * g * g * w2 + d * d * d * w3);
    a32 = d * p1 * q3 + g * q1 * p2;
    a33 = 1 + 2 * g * d * w1 + g * g * w2 + d * d * w3;
    a34 = a33 - 1;
    a51 = l.Rho * (d * d * p1 * q3 + g * g * q1 * p2);
    a52 = -p2 * q3;
    a61 = l.Rho * l.Rho * (2 * g * g * d * d * w1 + g * g * g * g * w2 + d * d * d * d * w3);

    out << a11, a12, a13, a13, a15, a16,
            a21, a22, a23, a23, a25, a15,
            a31, a32, a33, a34, a23, a13,
            a31, a32, a34, a33, a23, a13,
            a51, a52, a32, a32, a22, a12,
            a61, a51, a31, a31, a21, a11;

    return out;
}
