#include "virtual_factory/do_math.hpp"

#include <memory>

namespace
{
  class OperationInterface
  {
  public:
    virtual ~OperationInterface() = default;
    virtual int do_operation(int i_x, int i_y) const = 0;
  };

  class AdditionOperation : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override;
  };

  class SubtractionOperation : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override;
  };

  class MultiplicationOperation : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override;
  };

  class DivisionOperation : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override;
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
        return nullptr;
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
