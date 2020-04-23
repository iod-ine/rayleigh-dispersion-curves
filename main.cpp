#include <fstream>

#include "spdlog/spdlog.h"

#include "medium.h"
#include "rayleigh.h"

int main() {
    Medium *M = LoadMediumFromFile();

    if (!M) {
        spdlog::error("Unable to load the model. Terminating.");
        return 1;
    }

    // calculate the fundamental mode and 5 higher modes and dump the results
    // to a file.

    auto fundamental = RayleighFundamentalMode(*M);
    auto first = RayleighNextHigherMode(*M, fundamental);
    auto second = RayleighNextHigherMode(*M, first);
    auto third = RayleighNextHigherMode(*M, second);
    auto fourth = RayleighNextHigherMode(*M, third);
    auto fifth = RayleighNextHigherMode(*M, fourth);

    spdlog::info("Writing the curves.csv outputfile...");

    std::ofstream fout;
    fout.open("curves.csv");

    fout << "Fundamental,1st,2nd,3rd,4th,5th" << std::endl;

    for (int i = 0; i < 500; ++i) {
        fout << fundamental[i] << ",";
        fout << first[i] << ",";
        fout << second[i] << ",";
        fout << third[i] << ",";
        fout << fourth[i] << ",";
        fout << fifth[i] << std::endl;
    }

    delete M;
    return 0;
}
