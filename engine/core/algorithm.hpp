#pragma once
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace engine 
{
static constexpr uint8_t word_size{5};
static const uint32_t thread_num{std::thread::hardware_concurrency()};
enum output_status 
{ 
    correct_pos = 0, 
    wrong_pos = 1, 
    not_in_word = 2
};

class Base 
{
public:
    Base(std::string input_path, std::string output_path);
    virtual ~Base() = default;

    static std::array<uint8_t, word_size> validate_ans(const std::string ans, const std::string sol) {
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

        for (uint8_t i = 0; i < word_size; ++i)
        {
            if (ans.at(i) == sol.at(i)) 
            {
                output[i] = output_status::correct_pos;
            }
            else 
            {
                temp_ans.push_back(ans.at(i));
                temp_word.push_back(sol.at(i));
                temp_index.push_back(i);
            }
        }

        std::string temp_substring{};
        for (uint8_t i = 0; i < temp_ans.size(); ++i)
        {
            uint8_t substring_occurences = std::count(temp_substring.begin(), temp_substring.end(), temp_ans.at(i));
            uint8_t word_occurences = std::count(temp_word.begin(), temp_word.end(), temp_ans.at(i));
               
            if ((temp_word.find(temp_ans.at(i)) != std::string::npos) && (substring_occurences < word_occurences))
            {
                output.at(temp_index.at(i)) = output_status::wrong_pos;
            }
            temp_substring.push_back(temp_ans.at(i));
        }
        return output;
    }

    virtual void validate_algorithm();
    virtual void validate_algorithm_multithreaded();
    virtual std::string sol_function(
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> & possible_ans) = 0;

private:
    std::string output_path{};
    std::vector<std::string> data;
};
} // namespace engine

