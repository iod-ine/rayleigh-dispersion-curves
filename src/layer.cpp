//
// Created by Ivan Dubrovin on 22.04.2020.
//

#include <cmath>
#include "layer.h"

using std::sqrt; using std::pow;

Layer::Layer(double vs, double h) {
    Vp = vs * sqrt(3);          // calculate Vp from Vs assuming λ = μ
    Vs = vs;
    Rho = 0.31 * pow(Vp, 0.25);  // calculate Rho from Gardner's relation
    H = h;

    spdlog::info("Created a Layer: α≈{:.1f} β={} ρ≈{:.3f} h={}", Vp, Vs, Rho, H);
}

Layer::Layer(double vp, double vs, double rho, double h) {
    Vp = vp;
    Vs = vs;
    Rho = rho;
    H = h;

    spdlog::info("Created a Layer: α={:.1f} β={} ρ={:.1f} h={}", Vp, Vs, Rho, H);
}
