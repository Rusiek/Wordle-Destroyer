#include "core/algorithm.hpp"
#include "randomAccess/randomAccess.hpp"
#include <string>
#include <iostream>

int main() {
    engine::RandomAccess ra_instance("valid_solutions.csv", "randomAccess/randomAccess.csv");
    ra_instance.validate_algorithm();
    ra_instance.validate_algorithm_multithreaded();
    return 0;
}