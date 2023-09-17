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

    static double find_entropy(
        const std::array<std::vector<std::string>, engine::categories> & entropy_info,
        std::unique_ptr<std::vector<std::string>> * possible_ans)
    {
        double entropy = 0;
        for (const auto & category : entropy_info)
        {
            if (category.empty())
            {
                continue;
            }
            double probability = static_cast<double>(category.size()) / static_cast<double>((*possible_ans)->size());
            entropy += probability * std::log2(probability);
        }
        return -entropy;
    }
    
    static std::string maximize_entropy(std::unique_ptr<std::vector<std::string>> * possible_ans)
    {
        std::string top_word{};
        double top_word_entropy = 0.0F;
        if ((*possible_ans)->size() == 1)
        {
            return (*possible_ans)->at(0);
        }
        for (const auto & ans : **possible_ans)
        {
            std::array<std::vector<std::string>, categories> entropy_info{};
            for (const auto & sol : **possible_ans)
            {
                std::array<uint8_t, word_size> ans_info_entropy = validate_ans(ans, sol);
                entropy_info.at(utils::array_to_uint8_t(ans_info_entropy)).push_back(sol);
            }
            auto total_entropy = find_entropy(entropy_info, possible_ans);
            if (total_entropy > top_word_entropy)
            {
                top_word = ans;
                top_word_entropy = total_entropy;
            }
        }

        (*possible_ans)->erase(std::remove((*possible_ans)->begin(), (*possible_ans)->end(), top_word), (*possible_ans)->end());
     
        return top_word;
    }
};
} // namespace engine
