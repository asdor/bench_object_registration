#pragma once

namespace bench
{
  class AdditionOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;
  };

  class SubtractionOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;
  };

  class MultiplicationOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;
  };

  class DivisionOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;
  };
}
