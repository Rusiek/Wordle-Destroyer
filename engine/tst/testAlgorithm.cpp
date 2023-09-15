#include <gtest/gtest.h>
#include "../algorithm.hpp"
#include "../baseline.hpp"

class TestAlgorithm : public ::testing::Test
{
public:
    static const engine::Baseline instance;
    static const uint8_t ok = engine::output_status::correct_pos;
    static const uint8_t change = engine::output_status::wrong_pos;
    static const uint8_t wrong = engine::output_status::not_in_word;
};

TEST(TestAlgorithm, TestValidateAns1)
{
    const std::string ans = "abcde";
    const std::string sol = "abcde";
    const std::array<uint8_t, engine::word_size> ans_info = {
        TestAlgorithm::ok,
        TestAlgorithm::ok, 
        TestAlgorithm::ok,
        TestAlgorithm::ok,
        TestAlgorithm::ok};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST(TestAlgorithm, TestValidateAns2)
{
    const std::string ans = "abcde";
    const std::string sol = "abcdz";
    const std::array<uint8_t, engine::word_size> ans_info = {
        TestAlgorithm::ok,
        TestAlgorithm::ok, 
        TestAlgorithm::ok,
        TestAlgorithm::ok,
        TestAlgorithm::wrong};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST(TestAlgorithm, TestValidateAns3)
{
    const std::string ans = "abcde";
    const std::string sol = "abzed";
    const std::array<uint8_t, engine::word_size> ans_info = {
        TestAlgorithm::ok,
        TestAlgorithm::ok, 
        TestAlgorithm::wrong,
        TestAlgorithm::change,
        TestAlgorithm::change};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST(TestAlgorithm, TestValidateAns4)
{
    const std::string ans = "abcde";
    const std::string sol = "xyztq";
    const std::array<uint8_t, engine::word_size> ans_info = {
        TestAlgorithm::wrong,
        TestAlgorithm::wrong, 
        TestAlgorithm::wrong,
        TestAlgorithm::wrong,
        TestAlgorithm::wrong};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST(TestAlgorithm, TestValidateAns5)
{
    const std::string ans = "baaab";
    const std::string sol = "aabaa";
    const std::array<uint8_t, engine::word_size> ans_info = {
        TestAlgorithm::change,
        TestAlgorithm::ok, 
        TestAlgorithm::change,
        TestAlgorithm::ok,
        TestAlgorithm::wrong};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}

TEST (TestAlgorithm, TestValidateAns6)
{
    const std::string ans = "abcde";
    const std::string sol = "bcdea";
    const std::array<uint8_t, engine::word_size> ans_info = {
        TestAlgorithm::change,
        TestAlgorithm::change, 
        TestAlgorithm::change,
        TestAlgorithm::change,
        TestAlgorithm::change};
    EXPECT_EQ(ans_info, TestAlgorithm::instance.validate_ans(ans, sol));
}