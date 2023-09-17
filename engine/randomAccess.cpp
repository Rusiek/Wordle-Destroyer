#include "randomAccess.hpp"

namespace engine
{
    auto RandomAccess::sol_function(
        const std::vector<std::string> &   /*ans_list*/,
        const std::vector<std::array<uint8_t, word_size>> &   /*ans_info*/,
        std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string 
    {
        return get_random_word(possible_ans);
    }
} // namespace engine
 