#include <iostream>
#include "spdlog/spdlog.h"
#include "Eigen/Dense"
#include "medium.h"

int main() {
    spdlog::set_pattern("[%L][%H:%M:%S] %v");
    spdlog::info("spdlog imported successfully!");

    Eigen::Matrix2d test;
    test << 0, 1,
            2, 3;
    std::cout << test << std::endl;

    auto M = Medium(1200);
    M.Layers.emplace_back(200, 10);

    return 0;
}
