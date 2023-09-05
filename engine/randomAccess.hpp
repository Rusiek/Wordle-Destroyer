#pragma once
#include <utility>

#include "algorithm.hpp"

namespace engine
{
class RandomAccess : public Base
{
public:
    RandomAccess(const std::string & input_path, const std::string & output_path) : Base(input_path, output_path) {}

    auto sol_function(
        const std::vector<std::string> & ans_list,
        const std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::shared_ptr<std::vector<std::string>> possible_ans) -> std::string override;
};
} // namespace engine
