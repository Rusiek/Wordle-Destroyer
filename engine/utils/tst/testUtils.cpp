#include <gtest/gtest.h>
#include "../utils.hpp"

class TestUtils : public ::testing::TestWithParam<uint32_t>{};

TEST(TestUtils, TestBuildPathDefault)
{
    const std::string path = "test";
    std::string expected = "data/test/singlethreaded/data.csv";
    std::string actual = engine::utils::build_path(path);
    EXPECT_EQ(expected, actual);
}

TEST_P(TestUtils, TestBuildPathMultithreaded)
{
    const std::string path = "test";
    const uint32_t thread_num = GetParam();
    std::string expected = "data/test/multithreaded/data_" + std::string(2 - std::to_string(thread_num).size(), '0') + std::to_string(thread_num) + ".csv";
    std::string actual = engine::utils::build_path(path, true, thread_num);
    EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(PerThread, TestUtils, ::testing::Range(static_cast<uint32_t>(0), static_cast<uint32_t>(100)));
