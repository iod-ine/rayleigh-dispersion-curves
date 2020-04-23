//
// Created by Ivan Dubrovin on 22.04.2020.
//

#include "rayleigh.h"

array<double, 500> RayleighNextHigherMode(const Medium &m, const array<double, 500> &prev) {
    array<double, 500> out;

    spdlog::info("Calculating next higher mode...");

    double f, guess;
    int sign0, sign1;

    for (int i = 0; i < 500; ++i) {

        if (isnan(prev[i]) || prev[i] + 2 >= m.Vs) {
            out[i] = NAN;
            continue;
        }

        f = 0.1 * (i + 1);
        guess = prev[i] + 1;

        sign0 = Sign(RayleighDispersionFunction(m, guess, f));

        ++guess;
        while (guess < m.Vs) {
            sign1 = Sign(RayleighDispersionFunction(m, guess, f));
            if (sign1 != sign0) {
                out[i] = guess - 0.5;
                break;
            }

            out[i] = NAN;
            ++guess;
        }
    }

    return out;
}
