#include <gtest/gtest.h>
#include "../algorithm.hpp"
#include "../baseline.hpp"

class TestAlgorithm : public ::testing::Test
{
public:
    static const engine::Baseline instance;
};

TEST_F(TestAlgorithm, TestValidateAns1)
{
    const std::string ans = "abcde";
    const std::string sol = "abcde";
    const std::array<uint8_t, engine::word_size> ans_info = {
        engine::output_status::correct_pos,
        engine::output_status::correct_pos, 
        engine::output_status::correct_pos,
        engine::output_status::correct_pos,
        engine::output_status::correct_pos};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST_F(TestAlgorithm, TestValidateAns2)
{
    const std::string ans = "abcde";
    const std::string sol = "abcdz";
    const std::array<uint8_t, engine::word_size> ans_info = {
        engine::output_status::correct_pos,
        engine::output_status::correct_pos, 
        engine::output_status::correct_pos,
        engine::output_status::correct_pos,
        engine::output_status::not_in_word};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST_F(TestAlgorithm, TestValidateAns3)
{
    const std::string ans = "abcde";
    const std::string sol = "abzed";
    const std::array<uint8_t, engine::word_size> ans_info = {
        engine::output_status::correct_pos,
        engine::output_status::correct_pos, 
        engine::output_status::not_in_word,
        engine::output_status::wrong_pos,
        engine::output_status::wrong_pos};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST_F(TestAlgorithm, TestValidateAns4)
{
    const std::string ans = "abcde";
    const std::string sol = "xyztq";
    const std::array<uint8_t, engine::word_size> ans_info = {
        engine::output_status::not_in_word,
        engine::output_status::not_in_word, 
        engine::output_status::not_in_word,
        engine::output_status::not_in_word,
        engine::output_status::not_in_word};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST_F(TestAlgorithm, TestValidateAns5)
{
    const std::string ans = "baaab";
    const std::string sol = "aabaa";
    const std::array<uint8_t, engine::word_size> ans_info = {
        engine::output_status::wrong_pos,
        engine::output_status::correct_pos, 
        engine::output_status::wrong_pos,
        engine::output_status::correct_pos,
        engine::output_status::not_in_word};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST_F(TestAlgorithm, TestValidateAns6)
{
    const std::string ans = "abcde";
    const std::string sol = "bcdea";
    const std::array<uint8_t, engine::word_size> ans_info = {
        engine::output_status::wrong_pos,
        engine::output_status::wrong_pos, 
        engine::output_status::wrong_pos,
        engine::output_status::wrong_pos,
        engine::output_status::wrong_pos};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}