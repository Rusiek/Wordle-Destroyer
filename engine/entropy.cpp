#include "entropy.hpp"
#include "utils/utils.hpp"

#include <limits>

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
    // double top_word_entropy = std::numeric_limits<double>::max();
    // for (const auto & ans : **possible_ans)
    // {
    //     std::array<std::vector<std::string>, categories> entropy_info{};
    //     for (const auto & sol : **possible_ans)
    //     {
    //         std::array<uint8_t, word_size> ans_info = validate_ans(ans, sol);
    //         for (uint8_t i = 0; i < word_size; ++i)
    //         {
    //             entropy_info.at(ans_info.at(i)).push_back(sol);
    //         }
    //     }
    //     auto total_entropy = utils::find_entropy(entropy_info);
    //     if (total_entropy < top_word_entropy)
    //     {
    //         top_word = ans;
    //         top_word_entropy = total_entropy;
    //     }
    // }
    return utils::get_random_word(possible_ans);
}
} // namespace engine
