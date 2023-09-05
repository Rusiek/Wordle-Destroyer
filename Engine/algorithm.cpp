#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <set>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include "algorithm.hpp"

namespace engine 
{

auto build_path(const std::string & path, bool multithreaded = false, uint32_t thread_num = 0) -> std::string
{
    if (multithreaded)
    {
        return "data/" + path + "/multithreaded/data_" + std::string(2 - std::to_string(thread_num).size(), '0') + std::to_string(thread_num) + ".csv";
    }
    return "data/" + path + "/singlethreaded/data.csv";
}

Base::Base(const std::string & input_path, const std::string & output_path) 
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
        this->data.push_back(line);
    }
    file.close();

    this->output_path = output_path;
}

void Base::validate_algorithm() 
{
    std::string path = build_path(output_path);
    std::ofstream file(path, std::ios::out);
    file << "word,guesses" << std::endl;
    file.close();

    for (auto & word : data)
    {
        uint32_t guesses_num{0};
        std::vector<std::string> ans_list{};
        std::vector<std::array<uint8_t, word_size>> ans_info{};
        std::vector<std::string> possible_ans = data;

        while (true) 
        {
            ++guesses_num;
            auto guess = this->sol_function(ans_list, ans_info, &possible_ans);
            ans_list.push_back(guess);
            ans_info.push_back(validate_ans(guess, word));
            if (guess == word) 
            {
                std::ofstream file(path, std::ios::app);
                file << word << "," << guesses_num << std::endl;
                file.close();
                break;
            }
        }
    }
}

void Base::validate_algorithm_multithreaded() 
{
    std::vector<std::string> paths;
    for (uint32_t index = 0; index < thread_num; ++index)
    {
        paths.push_back(build_path(output_path, true, index + 1));
        std::ofstream file(paths.at(index), std::ios::out);
        file << "word,guesses" << std::endl;
        file.close();
    }
    
    auto data_cp = data;
    auto thread_num_cp = thread_num;
    auto func_cp = [this](
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> & possible_ans) -> std::string
    {
        return sol_function(ans_list, ans_info, &possible_ans);
    };

    std::vector<std::thread> jobs;
    for (uint32_t thread = 0; thread < thread_num; ++thread)
    {
        auto job = [&data_cp, thread, &thread_num_cp, &paths, &func_cp]()
        {
            const uint32_t data_size{static_cast<uint32_t>(data_cp.size())};
            const std::string thread_str = std::to_string(thread + 1);
            auto progress = 0.0f;
            for (uint32_t index = thread; index < data_size; index += thread_num_cp)
            {
                progress = 100.0f * index / data_size;
                uint32_t guesses_num{0};
                std::vector<std::string> ans_list;
                std::vector<std::array<uint8_t, word_size>> ans_info;
                std::vector<std::string> possible_ans(data_cp);
                
                while (true) 
                {
                    ++guesses_num;
                    std::string guess = func_cp(ans_list, ans_info, possible_ans);
                    ans_list.push_back(guess);
                    ans_info.push_back(validate_ans(guess, data_cp.at(index)));
                    if (guess == data_cp.at(index)) 
                    {
                        std::ofstream file(paths.at(thread), std::ios::app);
                        file << data_cp.at(index) << "," << guesses_num << std::endl;
                        file.close();
                        break;
                    }
                }
            }
        };
        jobs.emplace_back(job);
    }

    for (auto & job : jobs)
    {
        job.join();
    }
}
} // namespace engine
