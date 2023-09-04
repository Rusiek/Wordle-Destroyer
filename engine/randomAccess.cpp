#include "randomAccess.hpp"

namespace engine
{
    std::string RandomAccess::sol_function(
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> & possible_ans) 
    {
        std::string guess = possible_ans.at(possible_ans.size() - 1);
        possible_ans.pop_back();
        return guess;
    }
} // namespace engine
