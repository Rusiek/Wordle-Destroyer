#include "core/algorithm.hpp"
#include "randomAccess/randomAccess.hpp"
#include "baseline/baseline.hpp"
#include <string>
#include <iostream>

using namespace engine;

int main() {
    RandomAccess ra_instance("validSolutions.csv", "randomAccess");
    ra_instance.validate_algorithm();
    ra_instance.validate_algorithm_multithreaded();

    // Baseline bl_instance("validSolutions.csv", "baseline");
    // bl_instance.validate_algorithm();
    // bl_instance.validate_algorithm_multithreaded();
    return 0;
}