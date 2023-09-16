#include "ansReduction.hpp"
#include "utils/utils.hpp"

namespace engine
{
auto AnsReduction::sol_function(
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
    return utils::get_random_word(possible_ans);
}
} // namespace engine
