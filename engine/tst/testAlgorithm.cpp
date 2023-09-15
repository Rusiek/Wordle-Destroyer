#include <gtest/gtest.h>
#include "../algorithm.hpp"
#include "../baseline.hpp"

class TestBaseline : public ::testing::Test
{
public:
    const engine::Baseline instance{"test", "test"};
    const std::string test_path = "test";
    static const uint8_t ok = engine::output_status::correct_pos;
    static const uint8_t change = engine::output_status::wrong_pos;
    static const uint8_t wrong = engine::output_status::not_in_word;
};

TEST(TestBaseline, TestValidateAns)
{
    engine::Baseline instance("test", "test");

    const std::array<uint8_t, engine::word_size> ans_info_1 = {
        TestBaseline::ok,
        TestBaseline::ok, 
        TestBaseline::ok,
        TestBaseline::ok,
        TestBaseline::ok};
    EXPECT_EQ(ans_info_1, instance.validate_ans("abcde", "abcde"));
}
