//
// Created by Ivan Dubrovin on 22.04.2020.
//

#ifndef RDCS_RAYLEIGH_H
#define RDCS_RAYLEIGH_H

#include "Eigen/Dense"

#include "layer.h"
#include "medium.h"

using Eigen::Matrix;

Matrix<double, 6, 6> RayleighLayerMatrix(Layer l, double c, double f);

double RayleighDispersionFunction(const Medium &m, double c, double f);

#endif //RDCS_RAYLEIGH_H
