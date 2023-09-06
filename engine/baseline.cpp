#include "baseline.hpp"
#include <iostream>

namespace engine
{
    auto Baseline::sol_function(
        const std::vector<std::string> & ans_list,
        const std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string
    {
        std::cout << (*possible_ans)->size() << std::endl;
        if (ans_list.empty())
        {
            std::string guess = (*possible_ans)->at((*possible_ans)->size() - 1);
            (*possible_ans)->pop_back();
            return guess;
        }

        std::vector<std::string> new_possible_ans;

        for (const auto & word : **possible_ans)
        {
            bool add_word = true;
            for (uint32_t index = 0; index < word_size; ++index)
            {
                if ((ans_info.at(ans_info.size() - 1).at(index) == output_status::correct_pos) && (ans_list.at(ans_list.size() - 1) != word))
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

        *possible_ans = std::make_unique<std::vector<std::string>>(new_possible_ans);
        std::string guess = (*possible_ans)->at((*possible_ans)->size() - 1);
        (*possible_ans)->pop_back();
        return guess;
    }
} // namespace engine
