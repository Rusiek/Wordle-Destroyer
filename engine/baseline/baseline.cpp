#include "baseline.hpp"

namespace engine
{
    std::string Baseline::sol_function(
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> & possible_ans) 
    {
        if (ans_list.size() == 0) 
        {
            std::string guess = possible_ans.at(possible_ans.size() - 1);
            possible_ans.pop_back();
            return guess;
        }
        std::vector<std::string> new_possible_ans;
        for (auto word : possible_ans)
        {
            bool add_word = true;
            for (uint32_t index = 0; index < word_size; ++index)
            {
                if (ans_info.at(ans_info.size() - 1).at(index) == output_status::correct_pos && ans_list.at(ans_list.size() - 1) != word)
                {
                    add_word = false;
                    break;
                }
            }
            if (add_word)
            {
                new_possible_ans.push_back(word);
            }
        }
        possible_ans = new_possible_ans;
        std::string guess = possible_ans.at(possible_ans.size() - 1);
        possible_ans.pop_back();
        return guess;
    }
} // namespace engine