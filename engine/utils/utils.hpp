#pragma once
#include <string>

namespace engine
{
namespace utils
{
auto build_path(const std::string & path, bool multithreaded = false, uint32_t thread_num = 0) -> std::string;
} // namespace utils
} // namespace engine
