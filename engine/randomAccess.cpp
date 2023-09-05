#include "randomAccess.hpp"

namespace engine
{
    auto RandomAccess::sol_function(
        const std::vector<std::string> &  /*ans_list*/,
        const std::vector<std::array<uint8_t, word_size>> &  /*ans_info*/,
        std::vector<std::string> * possible_ans) -> std::string 
    {
        std::string guess = possible_ans->at(possible_ans->size() - 1);
        possible_ans->pop_back();
        return guess;
    }
} // namespace engine
