//
// Created by Ivan Dubrovin on 23.04.2020.
//

#include "rdc_utils.h"

Medium *LoadMediumFromFile() {

    ifstream inputf;
    inputf.open("model.in");

    auto out = new Medium;

    if (inputf.is_open()) {
        spdlog::info("Parsing the input file...");

        string line;

        // regular expressions to create layers and the medium
        regex layer_re_1(R"(Layer:\s(\d+\.?\d*)\s(\d+\.?\d*)\s*$)");                           // -> vs, h
        regex layer_re_2(R"(Layer:\s(\d+\.?\d*)\s(\d+\.?\d*)\s(\d+\.?\d*)\s(\d+\.?\d*)\s*$)"); // -> vp, vs, rho, h
        regex halfspace_re_1(R"(Half\-?space:\s(\d+\.?\d*)\s*$)");                             // -> vs
        regex halfspace_re_2(R"(Half\-?space:\s(\d+\.?\d*)\s(\d+\.?\d*)\s(\d+\.?\d*)\s*$)");   // -> vp, vs, rho
        std::smatch matches;

        double vp, vs, rho, h;

        // parse the first line - halfspace

        std::getline(inputf, line);

        if (regex_search(line, matches, halfspace_re_1)) {
            vs = std::stod(matches.str(1));
            *out = Medium(vs);
        } else if (regex_search(line, matches, halfspace_re_2)) {
            vp = std::stod(matches.str(1));
            vs = std::stod(matches.str(2));
            rho = std::stod(matches.str(3));
            *out = Medium(vp, vs, rho);
        } else {
            spdlog::error("Seems that the input file format is wrong.");
            return nullptr;
        }

        // iterate over the rest of the lines, creating layers

        while (inputf) {
            std::getline(inputf, line);

            if (std::regex_search(line, matches, layer_re_1)) {
                vs = std::stod(matches.str(1));
                h = std::stod(matches.str(2));
                out->Layers.emplace_back(vs, h);
            } else if (std::regex_search(line, matches, layer_re_2)) {
                vp = std::stod(matches.str(1));
                vs = std::stod(matches.str(2));
                rho = std::stod(matches.str(3));
                h = std::stod(matches.str(4));
                out->Layers.emplace_back(vp, vs, rho, h);
            } else if (line.empty()) {
                spdlog::info("Done parsing the input file!");
                break;
            } else {
                spdlog::error("Seems that the input file format is wrong.");
                return nullptr;
            }
        }
    } else {
        spdlog::error("No input file found! Creating a template one.");

        ofstream fout;
        fout.open("model.in");

        fout << "Halfspace: vp vs rho OR vs" << std::endl;
        fout << "Layer: vp vs rho h OR vs h" << std::endl;
        fout << "Layer: vp vs rho h OR vs h" << std::endl;

        fout.close();

        return nullptr;
    }

    return out;
}
