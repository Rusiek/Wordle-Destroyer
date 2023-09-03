#include "randomAccess.hpp"

namespace engine
{
    std::string RandomAccess::sol_function(
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> possible_ans) 
    {
        std::string guess = possible_ans.at(rand() % possible_ans.size());
        possible_ans.erase(std::remove(possible_ans.begin(), possible_ans.end(), guess), possible_ans.end());
        return guess;
    }
} // namespace engine