#include "entropy.hpp"
#include "utils/utils.hpp"

#include <iostream>

namespace engine
{
auto Entropy::sol_function(
    const std::vector<std::string> & ans_list,
    const std::vector<std::array<uint8_t, word_size>> & ans_info,
    std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string
{
    if (ans_list.empty())
    {
        (*possible_ans)->erase(std::remove((*possible_ans)->begin(), (*possible_ans)->end(), get_starting_word()), (*possible_ans)->end());
        return get_starting_word();
    }

    reduce_answers(ans_list, ans_info, possible_ans);
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
        auto total_entropy = utils::find_entropy(entropy_info, possible_ans);
        if (total_entropy > top_word_entropy)
        {
            top_word = ans;
            top_word_entropy = total_entropy;
        }
    }

    (*possible_ans)->erase(std::remove((*possible_ans)->begin(), (*possible_ans)->end(), top_word), (*possible_ans)->end());
    return top_word;
}
} // namespace engine
