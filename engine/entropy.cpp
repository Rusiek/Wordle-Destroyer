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
        return get_starting_word();
    }

    reduce_answers(ans_list, ans_info, possible_ans);
    std::string top_word = ans_list.at(0);
    double top_word_entropy = std::numeric_limits<double>::max();
    for (const auto & word : **possible_ans)
    {
        std::array<std::vector<std::string>, categories> entropy_info{};
        for (const auto & ans : **possible_ans)
        {
            std::array<uint8_t, word_size> ans_info = validate_ans(ans, word);
            for (uint8_t i = 0; i < word_size; ++i)
            {
                entropy_info.at(ans_info.at(i)).push_back(ans);
            }
        }
        auto total_entropy = utils::find_entropy(entropy_info);
        if (total_entropy < top_word_entropy)
        {
            top_word = word;
            top_word_entropy = total_entropy;
        }
    }

    (*possible_ans)->erase(std::remove((*possible_ans)->begin(), (*possible_ans)->end(), top_word), (*possible_ans)->end());
    return top_word;
}
} // namespace engine
