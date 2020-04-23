#include <iostream>
#include <fstream>

#include "spdlog/spdlog.h"

#include "medium.h"
#include "rayleigh.h"

int main() {
    spdlog::set_pattern("[%L][%H:%M:%S] %v");

    auto M = Medium(1000, 500, 1.9);
    M.Layers.emplace_back(600, 300, 1.9, 10);
    M.Layers.emplace_back(400, 200, 1.9, 10);
    M.Layers.emplace_back(200, 100, 1.9, 10);

    auto fund = RayleighFundamentalMode(M);
    auto first = RayleighNextHigherMode(M, fund);
    auto second = RayleighNextHigherMode(M, first);
    auto third = RayleighNextHigherMode(M, second);
    auto fourth = RayleighNextHigherMode(M, third);
    auto fifth = RayleighNextHigherMode(M, fourth);
    auto sixths = RayleighNextHigherMode(M, fifth);
    auto seventh = RayleighNextHigherMode(M, sixths);
    auto eights = RayleighNextHigherMode(M, seventh);
    auto nineth = RayleighNextHigherMode(M, eights);
    auto tenth = RayleighNextHigherMode(M, nineth);
    auto eleventh = RayleighNextHigherMode(M, tenth);

    std::ofstream fout;
    fout.open("output.csv");
    fout << "Fundamental,1st,2nd,3rd,4th,5th,6th,7th,8th,9th,10th,11th" << std::endl;
    for (int i = 0; i < 500; ++i) {
        fout << fund[i] << ",";
        fout << first[i] << ",";
        fout << second[i] << ",";
        fout << third[i] << ",";
        fout << fourth[i] << ",";
        fout << fifth[i] << ",";
        fout << sixths[i] << ",";
        fout << seventh[i] << ",";
        fout << eights[i] << ",";
        fout << nineth[i] << ",";
        fout << tenth[i] << ",";
        fout << eleventh[i] << std::endl;
    }
    fout.close();

    return 0;
}
