#include <compile_time_by_variant/do_math.hpp>
#include <naive_by_condition/do_math.hpp>

#include <gtest/gtest.h>

TEST(A, B)
{
  EXPECT_EQ(bench::do_math_naive("add", 5, 8), 13);
  EXPECT_EQ(bench::do_math_naive("sub", 10, 2), 8);
  EXPECT_EQ(bench::do_math_naive("mul", 87, 42), 3654);
  EXPECT_EQ(bench::do_math_naive("div", 1444, 19), 76);
}

TEST(A, C)
{
  EXPECT_EQ(bench::do_math_by_variant("add", 5, 8), 13);
  EXPECT_EQ(bench::do_math_by_variant("sub", 10, 2), 8);
  EXPECT_EQ(bench::do_math_by_variant("mul", 87, 42), 3654);
  EXPECT_EQ(bench::do_math_by_variant("div", 1444, 19), 76);
}
