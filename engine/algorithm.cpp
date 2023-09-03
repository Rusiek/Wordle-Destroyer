#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <set>
#include <string>
#include <thread>
#include <vector>
#include "algorithm.hpp"
#include "indicators.hpp"

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
    using namespace indicators;

    std::ofstream file(output_path, std::ios::out);
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
            ans_info.push_back(validate_ans(guess, possible_ans.at(index)));
            if (guess == possible_ans.at(index)) 
            {
                std::ofstream file(output_path, std::ios::app);
                file << possible_ans.at(index) << "," << guesses_num << std::endl;
                file.close();
                break;
            }
        }
    }

    bar.set_progress(100.0f);
}

void Base::validate_algorithm_multithreaded() 
{
    using namespace indicators;
    std::ofstream file(output_path, std::ios::out);
    file << "word,guesses" << std::endl;
    file.close();
    
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
    auto path_cp = output_path;
    auto func_cp = [this](
        std::vector<std::string> & ans_list,
        std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::vector<std::string> possible_ans) -> std::string
    {
        return sol_function(ans_list, ans_info, possible_ans);
    };

    DynamicProgress<ProgressBar> bars(bar1, bar2, bar3, bar4, bar5, bar6, bar7, bar8);

    std::vector<std::thread> jobs;
    for (uint32_t thread = 0; thread < 8; ++thread)
    {
        auto job = [&bars, &data_cp, thread, &path_cp, &func_cp]()
        {
            const int thread_local_id{thread};
            const uint32_t data_size{data_cp.size()};
            
            auto progress = 0.0f;
            for (uint32_t index = thread; index < data_size; index += 8)
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
                    ans_info.push_back(validate_ans(guess, possible_ans.at(index)));
                    if (guess == possible_ans.at(index)) 
                    {
                        std::ofstream file(path_cp, std::ios::app);
                        file << possible_ans.at(index) << "," << guesses_num << std::endl;
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
