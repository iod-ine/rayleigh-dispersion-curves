//
// Created by Ivan Dubrovin on 22.04.2020.
//

#ifndef RDCS_RAYLEIGH_H
#define RDCS_RAYLEIGH_H

#include <array>

#include "Eigen/Dense"

#include "layer.h"
#include "medium.h"
#include "rdc_utils.h"

using Eigen::Matrix;
using std::array;

Matrix<double, 6, 6> RayleighLayerMatrix(Layer l, double c, double f);

double RayleighDispersionFunction(const Medium &m, double c, double f);

array<double, 500> RayleighFundamentalMode(const Medium &m);

#endif //RDCS_RAYLEIGH_H
