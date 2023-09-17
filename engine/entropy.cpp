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
        return get_starting_word(possible_ans);
    }

    reduce_answers(ans_list, ans_info, possible_ans);
    return maximize_entropy(possible_ans);
}
} // namespace engine
