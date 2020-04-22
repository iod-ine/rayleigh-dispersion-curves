#include <iostream>
#include "spdlog/spdlog.h"
#include "Eigen/Dense"
#include "medium.h"

int main() {

    auto M = Medium(1200);
    M.Layers.emplace_back(200, 10);

    return 0;
}
