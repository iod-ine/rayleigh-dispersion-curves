//
// Created by Ivan Dubrovin on 22.04.2020.
//

#include <cmath>
#include "medium.h"

using std::sqrt; using std::pow;

Medium::Medium(double vs) {
    Vp = vs * sqrt(3);          // calculate Vp from Vs assuming λ = μ
    Vs = vs;
    Rho = 0.31 * pow(Vp, 0.25);  // calculate Rho from Gardner's relation

    spdlog::info("Created a Medium: α≈{:.1f} β={} ρ≈{:.3f}", Vp, Vs, Rho);
}

Medium::Medium(double vp, double vs, double rho) {
    Vp = vp;
    Vs = vs;
    Rho = rho;

    spdlog::info("Created a Medium: α={} β={} ρ={}", Vp, Vs, Rho);
}
