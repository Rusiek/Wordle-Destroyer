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
constexpr uint8_t word_size{5};
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

    static void timer(
        const std::chrono::high_resolution_clock::time_point & start, 
        std::chrono::high_resolution_clock::time_point & timestamp,
        uint32_t current_index, 
        uint32_t data_size)
    {
        auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() > 100)
        {
            timestamp = now;
            std::stringstream progress;
            progress << std::fixed << std::setprecision(2) << 100 * (static_cast<float>(current_index) / data_size);
            std::string progress_str = " [" + std::string(6 - progress.str().size(), ' ') + progress.str() + "%] ";
            auto eta = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() * (data_size - current_index) / current_index;
            auto time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(eta)).count();
            std::cout << progress_str << "[ETA: " << time << "s]\n\x1b[A";
        }
    }

    virtual void validate_algorithm();
    virtual std::string func(
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> possible_ans) = 0;

protected:
    std::vector<std::string> data;
    uint32_t thread_num{std::thread::hardware_concurrency() - 1};

private:
    std::string output_path{};

};
} // namespace engine

