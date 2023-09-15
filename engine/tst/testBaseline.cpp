#include <gtest/gtest.h>
#include <vector>
#include "../algorithm.hpp"
#include "../baseline.hpp"

class TestBaseline;

TEST(TestBaseline, TestGetAllOkWords_Empty)
{
    const std::string test_path = "test";
    engine::Baseline instance(test_path, test_path);

    const std::vector<std::string> ans_list{};
    const std::vector<std::array<uint8_t, engine::word_size>> ans_info{};
    const std::vector<std::string> dataset{"abcde", "xyztq", "makao"};
    std::unique_ptr<std::vector<std::string>> possible_ans{std::make_unique<std::vector<std::string>>(dataset)};

    const auto result = instance.sol_function(ans_list, ans_info, &possible_ans);
    EXPECT_EQ(result, "makao");
    EXPECT_EQ(possible_ans->size(), dataset.size() - 1);
}
