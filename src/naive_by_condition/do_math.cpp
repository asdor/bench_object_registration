#include "naive_by_condition/do_math.hpp"

#include <format>
#include <stdexcept>

namespace bench
{
  int do_math_naive(std::string_view i_operation, int i_x, int i_y)
  {
    if (i_operation == "add")
      return i_x + i_y;
    else if (i_operation == "sub")
      return i_x - i_y;
    else if (i_operation == "mul")
      return i_x * i_y;
    else if (i_operation == "div")
      return i_x / i_y;
    else
      throw std::invalid_argument(std::format("Unknown operation: {}", i_operation));
  }
}
