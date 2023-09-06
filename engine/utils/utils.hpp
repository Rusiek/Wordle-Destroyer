#pragma once
#include <memory>
#include <string>
#include <vector>

namespace engine
{
namespace utils
{
auto build_path(const std::string & path, bool multithreaded = false, uint32_t thread_num = 0) -> std::string;
auto get_random_word(std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string;
} // namespace utils
} // namespace engine
