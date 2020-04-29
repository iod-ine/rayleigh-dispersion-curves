//
// Created by Ivan Dubrovin on 22.04.2020.
//

#ifndef RDCS_RAYLEIGH_H
#define RDCS_RAYLEIGH_H

#include <array>
#include <cmath>

#include "Eigen/Dense"

#include "layer.h"
#include "medium.h"
#include "rdc_utils.h"

using Eigen::Matrix;
using std::array;
using std::isnan;

Matrix<double, 6, 6> RayleighLayerMatrix(Layer l, double c, double f);

double RayleighDispersionFunction(const Medium &m, double c, double f);

array<double, 1500> RayleighFundamentalMode(const Medium &m);

array<double, 1500> RayleighNextHigherMode(const Medium &m, const array<double, 1500> &prev);

#endif //RDCS_RAYLEIGH_H
