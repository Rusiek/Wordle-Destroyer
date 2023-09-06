#include "utils.hpp"

namespace engine::utils
{
auto build_path(const std::string & path, bool multithreaded, uint32_t thread_num) -> std::string
{
    if (multithreaded)
    {
        return "data/" + path + "/multithreaded/data_" + std::string(2 - std::to_string(thread_num).size(), '0') + std::to_string(thread_num) + ".csv";
    }
    return "data/" + path + "/singlethreaded/data.csv";
}
} // namespace engine::utils
