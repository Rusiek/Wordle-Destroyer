#include "engine/ansReduction.hpp"
#include "engine/algorithm.hpp"
#include "engine/entropy.hpp"
#include "engine/randomAccess.hpp"
#include "engine/baseline.hpp"
#include <string>
#include <chrono>
#include <iostream>

void run_algorithm(engine::Base * instance, std::string multithreading);

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
        else if (query == "red" || query == "red+")
        {
            engine::AnsReduction red_instance("validSolutions.csv", "ansReduction");
            run_algorithm(&red_instance, query);
        }
        else if (query == "en" || query == "en+")
        {
            engine::Entropy en_instance("validSolutions.csv", "entropy");
            run_algorithm(&en_instance, query);
        }
        else
        {
            std::cout << query << " query is invalid" << std::endl;
        }
    }

    return 0;
}

void run_algorithm(engine::Base * instance, std::string multithreading)
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