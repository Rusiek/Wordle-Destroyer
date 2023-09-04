#include "baseline.hpp"

namespace engine
{
    std::string Baseline::sol_function(
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> & possible_ans) 
    {
        if (ans_list.size() == 0 || possible_ans.size() == 0)
        {
            std::string guess = possible_ans.at(possible_ans.size() - 1);
            possible_ans.pop_back();
            return guess;
        }

        std::vector<std::string> new_possible_ans;
        for (auto word : possible_ans)
        {
            bool add_word = true;
            std::cout << "word: " << word << std::endl;
            std::cout << "ans_list.at(ans_list.size() - 1): " << ans_list.at(ans_list.size() - 1) << std::endl;
            std::cout << "ans_info.at(ans_info.size() - 1): ";
            for (uint32_t index = 0; index < word_size; ++index)
            {
                std::cout << ans_info.at(ans_info.size() - 1).at(index);
            }
            std::cout << std::endl;
            for (uint32_t index = 0; index < word_size; ++index)
            {
                if ((ans_info.at(ans_info.size() - 1).at(index) == output_status::correct_pos) && (ans_list.at(ans_list.size() - 1) != word))
                {
                    add_word = false;
                    break;
                }
            }
            std::cout << add_word << std::endl;
            std::cout << std::endl;
            if (add_word)
            {
                new_possible_ans.push_back(word);
            }
        }

        std::cout << "new_possible_ans.size(): " << new_possible_ans.size() << std::endl;
        std::string guess = new_possible_ans.at(new_possible_ans.size() - 1);
        new_possible_ans.pop_back();
        possible_ans = new_possible_ans;
        return guess;
    }
} // namespace engine
