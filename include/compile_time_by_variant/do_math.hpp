#pragma once

#include <string_view>

namespace bench
{
  int do_math_by_variant(std::string_view i_operation, int i_x, int i_y);
}
