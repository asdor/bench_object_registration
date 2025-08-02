#include <compile_time_by_variant/do_math.hpp>
#include <naive_by_condition/do_math.hpp>

#include <functional>

#include <gtest/gtest.h>

namespace
{
  using DoMathSignature = std::function<int(std::string_view, int, int)>;
  class DoMathTest : public testing::TestWithParam<DoMathSignature>
  {
  };
}

TEST_P(DoMathTest, DoAddition)
{
  const auto f = GetParam();
  EXPECT_EQ(f("add", 5, 8), 13);
}

TEST_P(DoMathTest, DoSubtraction)
{
  const auto f = GetParam();
  EXPECT_EQ(f("sub", 10, 2), 8);
}

TEST_P(DoMathTest, DoMultiplication)
{
  const auto f = GetParam();
  EXPECT_EQ(f("mul", 87, 42), 3654);
}

TEST_P(DoMathTest, DoDivision)
{
  const auto f = GetParam();
  EXPECT_EQ(f("div", 1444, 19), 76);
}

INSTANTIATE_TEST_SUITE_P(DoMathTestSuite, DoMathTest, testing::Values(bench::do_math_naive, bench::do_math_by_variant));
