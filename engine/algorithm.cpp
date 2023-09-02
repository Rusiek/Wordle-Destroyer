#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "algorithm.hpp"

namespace engine 
{

Algorithm::Algorithm() {
    std::ifstream file("valid_solutions.csv");
    std::string line;
    while (std::getline(file, line)) { data.insert(line); }

    file.close();
}

Algorithm::~Algorithm() {}

} // namespace engine
