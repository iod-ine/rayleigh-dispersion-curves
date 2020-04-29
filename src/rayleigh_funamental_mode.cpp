//
// Created by Ivan Dubrovin on 22.04.2020.
//

#include "rayleigh.h"

array<double, 1500> RayleighFundamentalMode(const Medium &m) {
    array<double, 1500> out = {0};

    spdlog::info("Calculating the fundamental mode...");

    double min_vs = m.Vs;
    for (auto layer : m.Layers) {
        min_vs = min_vs > layer.Vs ? layer.Vs : min_vs;
    }

    double f, guess;
    int sign0, sign1;

    for (int i = 0; i < 1500; ++i) {
        f = 0.1 * (i + 1);
        guess = min_vs / 2;

        sign0 = Sign(RayleighDispersionFunction(m, guess, f));

        guess += 0.5;
        while (guess < m.Vs) {
            sign1 = Sign(RayleighDispersionFunction(m, guess, f));
            if (sign1 != sign0) {
                out[i] = guess - 0.25;
                break;
            }
            guess += 0.5;
        }

    }

    return out;
}
