#include <compile_time_by_variant/arithmetic_operations.hpp>

#include <iostream>

int main()
{
  const int x = 42;
  const int y = 51;
  const bench::AdditionOperation op;
  const int z = op.do_operation(x, y);
  std::cout << x << " + " << y << " = " << z << '\n';

  return 0;
}
