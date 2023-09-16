#pragma once
#include <cmath>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace engine
{
static constexpr uint8_t word_size{5};
static constexpr uint8_t categories{243};
static const uint32_t thread_num{std::thread::hardware_concurrency() - 1};
namespace utils
{
inline std::string build_path(const std::string & path, bool multithreaded = false, uint32_t thread_num = 0)
{
    if (multithreaded)
    {
        return "data/" + path + "/multithreaded/data_" + std::string(2 - std::to_string(thread_num).size(), '0') + std::to_string(thread_num) + ".csv";
    }
    return "data/" + path + "/singlethreaded/data.csv";
}

inline std::string get_random_word(std::unique_ptr<std::vector<std::string>> * possible_ans)
{
    std::string guess = (*possible_ans)->at((*possible_ans)->size() - 1);
    (*possible_ans)->pop_back();
    return guess;
}

constexpr std::array<uint8_t, engine::word_size> three_pow{1, 3, 9, 27, 81};
inline uint8_t array_to_uint8_t(const std::array<uint8_t, engine::word_size> & arr)
{
    uint8_t output = 0;
    for (uint8_t i = 0; i < engine::word_size; ++i)
    {
        output += arr.at(i) * three_pow.at(i);
    }
    return output;
}

inline double find_entropy(const std::array<std::vector<std::string>, engine::categories> & entropy_info)
{
    double entropy = 0;
    for (const auto & category : entropy_info)
    {
        if (category.empty())
        {
            continue;
        }
        double probability = static_cast<double>(category.size()) / static_cast<double>(engine::categories);
        entropy += probability * std::log2(probability);
    }
    return -entropy;
}
} // namespace utils
} // namespace engine
