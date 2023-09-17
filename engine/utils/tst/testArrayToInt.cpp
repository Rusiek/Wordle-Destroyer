#include <gtest/gtest.h>
#include "../utils.hpp"

class TestArrayToInt : public ::testing::TestWithParam<uint32_t>
{
public:
    void reset_input(std::array<uint8_t, 5> & input)
    {
        for (auto & x : input)
        {
            x = 0;
        }
    }

    void add_one_to_input(std::array<uint8_t, 5> & input)
    {
        uint8_t index = 0;
        do
        {
            ++input.at(index);
            if (input.at(index) == 3)
            {
                input.at(index) = 0;
                ++index;
            }
            else
            {
                break;
            }
        } while (index < input.size());
    }
};

TEST_F(TestArrayToInt, TestArrayToInt)
{
    std::array<uint8_t, 5> input;
    reset_input(input);
    for (uint8_t value = 0; value < 243; ++value)
    {
        EXPECT_EQ(engine::utils::array_to_uint8_t(input), value);
        add_one_to_input(input);
    }
}
