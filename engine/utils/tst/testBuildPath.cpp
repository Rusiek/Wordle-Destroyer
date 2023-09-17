#include <gtest/gtest.h>
#include "../utils.hpp"

class TestBuildPath : public ::testing::Test{};

TEST_F(TestBuildPath, TestBuildPathDefault)
{
    const std::string path = "test";
    std::string expected = "data/test/singlethreaded/data.csv";
    std::string actual = engine::utils::build_path(path);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestBuildPath, TestBuildPathMultithreaded)
{
    const std::string path = "test";
    for (uint8_t thread_num = 0; thread_num < 100; ++thread_num)
    {
        std::string expected = "data/test/multithreaded/data_" + std::string(2 - std::to_string(thread_num).size(), '0') + std::to_string(thread_num) + ".csv";
        std::string actual = engine::utils::build_path(path, true, thread_num);
        EXPECT_EQ(expected, actual);
    }
}