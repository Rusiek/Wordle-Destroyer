#include "algorithm.hpp"
#include <string>
#include <iostream>

int main() {
    engine::Algorithm a;
    for (auto x : engine::Algorithm::validate_ans("aabaa", "ababa")) {
        std::cout << static_cast<int>(x);
    }
    std::cout << std::endl;
    for (auto x : engine::Algorithm::validate_ans("aabad", "ababa")) {
        std::cout << static_cast<int>(x);
    }
    return 0;
}