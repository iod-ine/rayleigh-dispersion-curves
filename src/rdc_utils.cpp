//
// Created by Ivan Dubrovin on 22.04.2020.
//

#include "rdc_utils.h"

int Sign(double v) {
    return v < 0 ? -1 : (v > 0 ? 1 : 0);
}