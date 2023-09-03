#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include "algorithm.hpp"

namespace engine 
{

Base::Base(std::string input_path, std::string output_path) 
{
    try 
    {
        std::ifstream file(input_path);
        if (!file.is_open()) 
        {
            throw std::runtime_error("Input file not found");
        }
        file.close();
    }
    catch (const std::exception & e) 
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::ifstream file(input_path);
    std::string line;
    while (std::getline(file, line)) 
    {
        line.pop_back();
        this->data.push_back(line);
    }
    file.close();

    this->output_path = output_path;
}

void Base::validate_algorithm() 
{
    std::ofstream file(output_path, std::ios::out);
    file << "word,guesses" << std::endl;
    file.close();

    auto start = std::chrono::high_resolution_clock::now();
    auto timestamp = std::chrono::high_resolution_clock::now();

    for (int32_t i = 0; i < data.size(); ++i)
    {
        timer(start, timestamp, i, data.size());

        uint32_t guesses_num{0};
        std::vector<std::string> ans_list;
        std::vector<std::array<uint8_t, word_size>> ans_info;
        std::vector<std::string> possible_ans(data);

        while (possible_ans.size() > 1) 
        {
            ++guesses_num;
            auto guess = this->func(ans_list, ans_info, possible_ans);
            ans_list.push_back(guess);
            ans_info.push_back(validate_ans(guess, possible_ans.at(i)));
            if (guess == possible_ans.at(i)) 
            {
                std::ofstream file(output_path, std::ios::app);
                file << possible_ans.at(i) << "," << guesses_num << std::endl;
                file.close();
                break;
            }
        }
    }
}

} // namespace engine
