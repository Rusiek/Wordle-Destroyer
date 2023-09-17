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
} // namespace utils
} // namespace engine
