#include "baseline.hpp"
#include "utils/utils.hpp"
#include <iostream>

namespace engine
{
auto Baseline::sol_function(
    const std::vector<std::string> & ans_list,
    const std::vector<std::array<uint8_t, word_size>> & ans_info,
    std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string
{
    if (ans_list.empty())
    {
        return utils::get_random_word(possible_ans);
    }

    std::vector<std::string> new_possible_ans = get_all_ok_words(ans_list, ans_info, possible_ans);

    *possible_ans = std::make_unique<std::vector<std::string>>(new_possible_ans);
    return utils::get_random_word(possible_ans);
}
} // namespace engine
