#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <set>
#include <string>
#include <thread>
#include <vector>
#include "../core/algorithm.hpp"
#include "../utils/indicators.hpp"

namespace engine 
{

using namespace indicators;

std::string build_path(std::string path, bool multithreaded = false, uint32_t thread_num = 0)
{
    if (multithreaded)
    {
        return path + "/multithreaded/data_" + std::string(2 - std::to_string(thread_num).size(), '0') + std::to_string(thread_num) + ".csv";
    }
    return path + "/singlethreaded/data.csv";
}

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
    auto progress = 0.0f;

    ProgressBar bar{
        option::BarWidth{50},
        option::Start{" ["},
        option::Fill{"█"},
        option::Lead{"█"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PrefixText{"Solving wordle on main thread"},
        option::ForegroundColor{Color::green},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
    };

    for (int32_t index = 0; index < data.size(); ++index)
    {
        progress = 100.0f * index / data.size();
        bar.set_progress(progress);

        uint32_t guesses_num{0};
        std::vector<std::string> ans_list;
        std::vector<std::array<uint8_t, word_size>> ans_info;
        std::vector<std::string> possible_ans(data);

        while (true) 
        {
            ++guesses_num;
            auto guess = this->sol_function(ans_list, ans_info, possible_ans);
            ans_list.push_back(guess);
            ans_info.push_back(validate_ans(guess, data.at(index)));
            if (guess == data.at(index)) 
            {
                std::ofstream file(path, std::ios::app);
                file << data.at(index) << "," << guesses_num << std::endl;
                file.close();
                break;
            }
        }
    }

    bar.set_progress(100.0f);
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
    
    show_console_cursor(false);
    std::vector<ProgressBar> bars_array;
    ProgressBar bar1{
        option::BarWidth{50},
        option::Start{" ["},
        option::Fill{"█"},
        option::Lead{"█"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PrefixText{"Solving wordle on thread 1/8"},
        option::ForegroundColor{Color::green},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
    };

    ProgressBar bar2{
        option::BarWidth{50},
        option::Start{" ["},
        option::Fill{"█"},
        option::Lead{"█"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PrefixText{"Solving wordle on thread 2/8"},
        option::ForegroundColor{Color::green},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
    };

    ProgressBar bar3{
        option::BarWidth{50},
        option::Start{" ["},
        option::Fill{"█"},
        option::Lead{"█"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PrefixText{"Solving wordle on thread 3/8"},
        option::ForegroundColor{Color::green},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
    };

    ProgressBar bar4{
        option::BarWidth{50},
        option::Start{" ["},
        option::Fill{"█"},
        option::Lead{"█"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PrefixText{"Solving wordle on thread 4/8"},
        option::ForegroundColor{Color::green},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
    };

    ProgressBar bar5{
        option::BarWidth{50},
        option::Start{" ["},
        option::Fill{"█"},
        option::Lead{"█"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PrefixText{"Solving wordle on thread 5/8"},
        option::ForegroundColor{Color::green},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
    };
    
    ProgressBar bar6{
        option::BarWidth{50},
        option::Start{" ["},
        option::Fill{"█"},
        option::Lead{"█"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PrefixText{"Solving wordle on thread 6/8"},
        option::ForegroundColor{Color::green},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
    };

    ProgressBar bar7{
        option::BarWidth{50},
        option::Start{" ["},
        option::Fill{"█"},
        option::Lead{"█"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PrefixText{"Solving wordle on thread 7/8"},
        option::ForegroundColor{Color::green},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
    };

    ProgressBar bar8{
        option::BarWidth{50},
        option::Start{" ["},
        option::Fill{"█"},
        option::Lead{"█"},
        option::Remainder{"-"},
        option::End{"]"},
        option::PrefixText{"Solving wordle on thread 8/8"},
        option::ForegroundColor{Color::green},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
    };

    auto data_cp = data;
    auto thread_num_cp = thread_num;
    auto func_cp = [this](
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> & possible_ans) -> std::string
    {
        return sol_function(ans_list, ans_info, possible_ans);
    };

    DynamicProgress<ProgressBar> bars(bar1, bar2, bar3, bar4, bar5, bar6, bar7, bar8);

    std::vector<std::thread> jobs;
    for (uint32_t thread = 0; thread < thread_num; ++thread)
    {
        auto job = [&bars, data_cp, thread, thread_num_cp, &paths, func_cp]()
        {
            const uint32_t data_size{data_cp.size()};
            const std::string thread_str = std::to_string(thread + 1);
            
            auto progress = 0.0f;
            for (uint32_t index = thread; index < data_size; index += thread_num_cp)
            {
                progress = 100.0f * index / data_size;
                bars[thread].set_progress(progress);

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

            bars[thread].set_progress(100.0f);
        };
        jobs.push_back(std::thread(job));
    }

    for (auto & job : jobs)
    {
        job.join();
    }

    show_console_cursor(true);
}

} // namespace engine
