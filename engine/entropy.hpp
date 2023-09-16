#pragma once
#include <memory>

#include "ansReduction.hpp"

namespace engine
{
class Entropy : public AnsReduction
{
public:
    Entropy(
        const std::string & input_path,
        const std::string & output_path,
        const std::string & starting_word) : AnsReduction(input_path, output_path, starting_word) {}
    Entropy(const Entropy &) = delete;
    Entropy(Entropy &&) = delete;
    auto operator=(const Entropy &) -> Entropy & = delete;
    auto operator=(Entropy &&) -> Entropy & = delete;

    ~Entropy() override = default;

    auto sol_function(
        const std::vector<std::string> & ans_list,
        const std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string override;
};
} // namespace engine
