//
// Created by Ivan Dubrovin on 22.04.2020.
//

#ifndef RDCS_MEDIUM_H
#define RDCS_MEDIUM_H

#include <vector>

#include "spdlog/spdlog.h"

#include "layer.h"

using std::vector;

class Medium {
public:
    double Vp, Vs, Rho;
    vector<Layer> Layers;

    explicit Medium(double vs);

    Medium(double vp, double vs, double rho);
};


#endif //RDCS_MEDIUM_H
