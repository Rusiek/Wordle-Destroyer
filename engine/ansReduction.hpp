#pragma once
#include <memory>

#include "algorithm.hpp"

namespace engine
{
class AnsReduction : public Base
{
public:
    AnsReduction(const std::string & input_path, const std::string & output_path) : Base(input_path, output_path) {}
    AnsReduction(const AnsReduction &) = delete;
    AnsReduction(AnsReduction &&) = delete;
    auto operator=(const AnsReduction &) -> AnsReduction & = delete;
    auto operator=(AnsReduction &&) -> AnsReduction & = delete;

    ~AnsReduction() override = default;

    auto sol_function(
        const std::vector<std::string> & ans_list,
        const std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string override;

    static void reduce_answers(
        const std::vector<std::string> & ans_list,
        const std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::unique_ptr<std::vector<std::string>> * possible_ans)
    {
        if (ans_list.empty())
        {
            return;
        }
        
        std::vector<std::string> new_possible_ans;

        for (const auto & word : **possible_ans)
        {
            bool add_word = true;
            auto validation = Base::validate_ans(ans_list.at(ans_list.size() - 1), word);
            for (uint32_t index = 0; index < word_size; ++index)
            {
                if (validation.at(index) != ans_info.at(ans_info.size() - 1).at(index))
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
    }
};
} // namespace engine
