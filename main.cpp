#include "engine/algorithm.hpp"
#include "engine/randomAccess.hpp"
#include "engine/baseline.hpp"
#include <string>
#include <chrono>
#include <iostream>

template <typename T>
void run_algorithm(T * instance, std::string multithreading);

auto main(int argv, char ** argc) -> int {
    int requests = 0;

    while (requests++ < argv - 1)
    {
        argc = std::next(argc);
        std::string query = *argc;
        if (query == "ra" || query == "ra+")
        {
            engine::RandomAccess ra_instance("validSolutions.csv", "randomAccess");
            run_algorithm(&ra_instance, query);
        }
        else if (query == "bl" || query == "bl+")
        {
            engine::Baseline bl_instance("validSolutions.csv", "baseline");
            run_algorithm(&bl_instance, query);
        }
        else
        {
            std::cout << query << " query is invalid" << std::endl;
        }
    }
    // engine::Baseline bl_instance("validSolutions.csv", "baseline");
    // bl_instance.validate_algorithm();
    // bl_instance.validate_algorithm_multithreaded();

    return 0;
}

template <typename T>
void run_algorithm(T * instance, std::string multithreading)
{
    auto start = std::chrono::high_resolution_clock::now();
    if (multithreading.at(multithreading.size() - 1) == '+')
    {
        instance->validate_algorithm_multithreaded();
    }
    else
    {
        instance->validate_algorithm();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

}