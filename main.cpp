#include <iostream>
#include <fstream>

#include "spdlog/spdlog.h"

#include "medium.h"
#include "rayleigh.h"

int main() {
    spdlog::set_pattern("[%L][%H:%M:%S] %v");
    spdlog::set_level(spdlog::level::trace);

    auto M = Medium(1000, 500, 1.9);
    M.Layers.emplace_back(600, 300, 1.9, 10);
    M.Layers.emplace_back(400, 200, 1.9, 10);
    M.Layers.emplace_back(200, 100, 1.9, 10);

    auto res = RayleighFundamentalMode(M);

    std::ofstream fout;
    fout.open("output.csv");
    fout << "Fundamental" << std::endl;
    for (auto val : res) {
        fout << val << std::endl;
    }
    fout.close();

    return 0;
}
