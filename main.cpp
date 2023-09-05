#include "engine/algorithm.hpp"
#include "engine/randomAccess.hpp"
#include "engine/baseline.hpp"
#include <string>
#include <chrono>
#include <iostream>

auto main() -> int {
    engine::RandomAccess ra_instance("validSolutions.csv", "randomAccess");
    auto start = std::chrono::high_resolution_clock::now();
    ra_instance.validate_algorithm();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    ra_instance.validate_algorithm_multithreaded();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    engine::Baseline bl_instance("validSolutions.csv", "baseline");
    // bl_instance.validate_algorithm();
    // bl_instance.validate_algorithm_multithreaded();
    return 0;
}