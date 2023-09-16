#pragma once

#include "algorithm.hpp"
#include "utils/utils.hpp"

namespace engine
{
class RandomAccess : public Base
{
public:
    RandomAccess(
        const std::string & input_path,
        const std::string & output_path,
        const std::string & starting_word) : Base(input_path, output_path, starting_word) {}
    RandomAccess(const RandomAccess &) = delete;
    RandomAccess(RandomAccess &&) = delete;
    auto operator=(const RandomAccess &) -> RandomAccess & = delete;
    auto operator=(RandomAccess &&) -> RandomAccess & = delete;

    ~RandomAccess() override = default;

    auto sol_function(
        const std::vector<std::string> & ans_list,
        const std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string override;
};
} // namespace engine
