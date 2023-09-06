#include "utils.hpp"

namespace engine
{
namespace utils
{
auto build_path(const std::string & path, bool multithreaded, uint32_t thread_num) -> std::string
{
    if (multithreaded)
    {
        return "data/" + path + "/multithreaded/data_" + std::string(2 - std::to_string(thread_num).size(), '0') + std::to_string(thread_num) + ".csv";
    }
    return "data/" + path + "/singlethreaded/data.csv";
}

auto get_random_word(std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string
{
    std::string guess = (*possible_ans)->at((*possible_ans)->size() - 1);
    (*possible_ans)->pop_back();
    return guess;
}
}  // namespace utils
}  // namespace engine
