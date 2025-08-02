#include <naive_by_condition/do_math.hpp>

#include <gtest/gtest.h>

TEST(A, B)
{
  EXPECT_EQ(bench::do_math_naive("add", 5, 8), 13);
  EXPECT_EQ(bench::do_math_naive("sub", 10, 2), 8);
  EXPECT_EQ(bench::do_math_naive("mul", 87, 42), 3654);
  EXPECT_EQ(bench::do_math_naive("div", 1444, 19), 76);
}
