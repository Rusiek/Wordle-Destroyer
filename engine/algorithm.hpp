#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <set>
#include <string>
#include <vector>

namespace engine 
{
constexpr uint8_t word_size{5};
enum output_status { 
    correct_pos = 0, 
    wrong_pos = 1, 
    not_in_word = 2
};

class Algorithm 
{
public:
    Algorithm();
    ~Algorithm();

    static std::array<uint8_t, word_size> Algorithm::validate_ans(std::string ans, std::string sol) {
        std::array<uint8_t, word_size> output{
            output_status::not_in_word,
            output_status::not_in_word,
            output_status::not_in_word,
            output_status::not_in_word,
            output_status::not_in_word
            };
        std::vector<uint8_t> temp_index;
        std::string temp_ans;
        std::string temp_word;

        for (uint8_t i = 0; i < word_size; ++i) {
            if (ans.at(i) == sol.at(i)) {
                output[i] = output_status::correct_pos;
            }
            else {
                temp_ans.push_back(ans.at(i));
                temp_word.push_back(sol.at(i));
                temp_index.push_back(i);
            }
        }

        std::string temp_substring;
        for (uint8_t i = 0; i < temp_ans.size(); ++i) {
            uint8_t substring_occurences = std::count(temp_substring.begin(), temp_substring.end(), temp_ans.at(i));
            uint8_t word_occurences = std::count(temp_word.begin(), temp_word.end(), temp_ans.at(i));
            if (temp_word.find(temp_ans.at(i)) && (substring_occurences < word_occurences)) {
                output[temp_index.at(i)] = output_status::wrong_pos;
                temp_substring.push_back(temp_ans.at(i));
            }
        }
        return output;
    }
    // std::vector<std::pair<std::string, uint8_t>> validate_algorithm();
    // virtual std::pair<std::string, std::map<std::string, uint32_t>> f(std::string, std::string, std::map<std::string, uint32_t>);

private:
    std::set<std::string> data;

};
} // namespace engine

