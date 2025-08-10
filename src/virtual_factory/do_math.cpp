#include "virtual_factory/do_math.hpp"

#include <format>
#include <memory>
#include <stdexcept>

namespace
{
  class OperationInterface
  {
  public:
    virtual ~OperationInterface() = default;
    virtual int do_operation(int i_x, int i_y) const = 0;
  };

  class AdditionOperation final : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override
    {
      return i_x + i_y;
    }
  };

  class SubtractionOperation final : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override
    {
      return i_x - i_y;
    }
  };

  class MultiplicationOperation final : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override
    {
      return i_x * i_y;
    }
  };

  class DivisionOperation final : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override
    {
      return i_x / i_y;
    }
  };

  class OperationFactory
  {
  public:
    std::unique_ptr<OperationInterface> create(std::string_view i_operation)
    {
      if (i_operation == "add")
        return std::make_unique<AdditionOperation>();
      else if (i_operation == "sub")
        return std::make_unique<SubtractionOperation>();
      else if (i_operation == "mul")
        return std::make_unique<MultiplicationOperation>();
      else if (i_operation == "div")
        return std::make_unique<DivisionOperation>();
      else
        throw std::invalid_argument(std::format("Unknown operation: {}", i_operation));
    }
  };
}

namespace bench
{
  int do_math_virtual_factory(std::string_view i_operation, int i_x, int i_y)
  {
    OperationFactory factory;
    const auto operation = factory.create(i_operation);
    return operation->do_operation(i_x, i_y);
  }
}
