#pragma once
#include "algorithm.hpp"

namespace engine
{
class Baseline : public Base
{
public:
    Baseline(std::string input_path, std::string output_path) : Base(input_path, output_path) {}

    virtual std::string sol_function(
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> & possible_ans) override;
};
} // namespace engine