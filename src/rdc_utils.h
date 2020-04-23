//
// Created by Ivan Dubrovin on 22.04.2020.
//

#ifndef RDCS_RDC_UTILS_H
#define RDCS_RDC_UTILS_H

#include <string>
#include <regex>
#include <fstream>

#include "spdlog/spdlog.h"

#include "medium.h"

using std::string;
using std::ifstream; using std::ofstream;
using std::regex; using std::regex_search;

int Sign(double v);

Medium *LoadMediumFromFile();

#endif //RDCS_RDC_UTILS_H
