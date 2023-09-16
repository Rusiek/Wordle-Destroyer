#pragma once
#include <memory>

#include "algorithm.hpp"

namespace engine
{
class Baseline : public Base
{
public:
    Baseline(const std::string & input_path, const std::string & output_path) : Base(input_path, output_path) {}
    Baseline(const Baseline &) = delete;
    Baseline(Baseline &&) = delete;
    auto operator=(const Baseline &) -> Baseline & = delete;
    auto operator=(Baseline &&) -> Baseline & = delete;

    virtual ~Baseline() = default;

    auto sol_function(
        const std::vector<std::string> & ans_list,
        const std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string override;

    static std::vector<std::string> get_all_ok_words(
        const std::vector<std::string> & ans_list,
        const std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::unique_ptr<std::vector<std::string>> * possible_ans)
    {
        std::vector<std::string> new_possible_ans;

        for (const auto & word : **possible_ans)
        {
            bool add_word = true;
            for (uint32_t index = 0; index < word_size; ++index)
            {
                if ((ans_info.at(ans_info.size() - 1).at(index) == output_status::correct_pos) && word.at(index) != ans_list.at(ans_list.size() - 1).at(index))
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

        return new_possible_ans;
    }
};
} // namespace engine
