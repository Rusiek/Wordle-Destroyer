#include "algorithm.hpp"
#include "baseline.hpp"
#include <string>
#include <iostream>

int main() {
    engine::RandomAccess ra_instance("valid_solutions.csv", "random_access.csv");
    ra_instance.validate_algorithm();
    return 0;
}