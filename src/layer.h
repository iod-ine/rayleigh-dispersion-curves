//
// Created by Ivan Dubrovin on 22.04.2020.
//

#ifndef RDCS_LAYER_H
#define RDCS_LAYER_H


class Layer {
public:
    double Vp, Vs, Rho, H;

    Layer(double vs, double h);

    Layer(double vp, double vs, double rho, double h);
};


#endif //RDCS_LAYER_H
