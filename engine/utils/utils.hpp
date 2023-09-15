#pragma once
#include <memory>
#include <string>
#include <vector>

namespace engine
{
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
} // namespace utils
} // namespace engine
