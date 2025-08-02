#include "compile_time_by_variant/do_math.hpp"

#include <format>
#include <stdexcept>
#include <string_view>
#include <variant>

namespace
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

  int AdditionOperation::do_operation(int i_x, int i_y) const
  {
    return i_x + i_y;
  }

  int SubtractionOperation::do_operation(int i_x, int i_y) const
  {
    return i_x - i_y;
  }

  int MultiplicationOperation::do_operation(int i_x, int i_y) const
  {
    return i_x * i_y;
  }

  int DivisionOperation::do_operation(int i_x, int i_y) const
  {
    return i_x / i_y;
  }

  class OperationManager
  {
  private:
    std::variant<AdditionOperation, SubtractionOperation, MultiplicationOperation, DivisionOperation> d_operation;

  public:
    void set_operation(std::string_view i_operation)
    {
      if (i_operation == "add")
        d_operation.emplace<AdditionOperation>();
      else if (i_operation == "sub")
        d_operation.emplace<SubtractionOperation>();
      else if (i_operation == "mul")
        d_operation.emplace<MultiplicationOperation>();
      else if (i_operation == "div")
        d_operation.emplace<DivisionOperation>();
      else
        throw std::invalid_argument(std::format("Unknown operation: {}", i_operation));
    }

    int do_operation(int i_x, int i_y) const
    {
      return std::visit([i_x, i_y](const auto& i_op) { return i_op.do_operation(i_x, i_y); }, d_operation);
    }
  };
}

namespace bench
{

  int do_math_by_variant(std::string_view i_operation, int i_x, int i_y)
  {
    OperationManager manager;
    manager.set_operation(i_operation);

    return manager.do_operation(i_x, i_y);
  }
}
