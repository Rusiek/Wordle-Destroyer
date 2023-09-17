#include <chrono>
#include <gtest/gtest.h>
#include "../baseline.hpp"

class TestGetRandomWord : public ::testing::TestWithParam<std::vector<std::string>>
{
public:
    static const engine::Baseline instance_s;
};

TEST_P(TestGetRandomWord, TestCorrectness)
{
    std::unique_ptr<std::vector<std::string>> possible_ans = std::make_unique<std::vector<std::string>>(GetParam());
    std::string expected = possible_ans->at(possible_ans->size() - 1);
    std::string actual = instance_s.get_random_word(&possible_ans);
    EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    PerVector, 
    TestGetRandomWord, 
    ::testing::Values(
        std::vector<std::string>{"oneWord"},
        std::vector<std::string>{"wordOne", "wordTwo"},
        std::vector<std::string>{"aback", "abase", "abate", "abbey", "abbot", "abhor", "abide", "abled"}
    ));

TEST_F(TestGetRandomWord, TestPerformance)
{
    constexpr int num_words = 1'000'000;
    constexpr int max_time_ms = 150;

    std::unique_ptr<std::vector<std::string>> possible_ans = std::make_unique<std::vector<std::string>>(std::vector<std::string>{});
    for (int word_num = 0; word_num < num_words; ++word_num)
    {
        possible_ans->push_back("test" + std::string(7 - std::to_string(word_num).size(), '0') + std::to_string(word_num));
    }

    auto timer_start = std::chrono::high_resolution_clock::now();
    for (int word_num = 0; word_num < num_words; ++word_num)
    {
        instance_s.get_random_word(&possible_ans);
    }
    auto timer_end = std::chrono::high_resolution_clock::now();
    auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(timer_end - timer_start).count();
    
    EXPECT_LT(total_time, max_time_ms);
}