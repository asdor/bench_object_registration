#include "virtual_factory_self_reg/do_math.hpp"

#include <format>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

namespace
{
  class OperationInterface
  {
  public:
    virtual ~OperationInterface() = default;
    virtual int do_operation(int i_x, int i_y) const = 0;
  };

  class Registry
  {
  public:
    static Registry& instance()
    {
      static Registry registry;
      return registry;
    }

    bool registrate(std::string_view i_operation_name, std::unique_ptr<OperationInterface> i_op)
    {
      d_operations[i_operation_name] = std::move(i_op);
      return true;
    }

    OperationInterface& get(std::string_view i_operation)
    {
      if (auto it = d_operations.find(i_operation); it != d_operations.end())
        return *it->second;
      else
        throw std::invalid_argument(std::format("Unknown operation: {}", i_operation));
    }

  private:
    std::unordered_map<std::string_view, std::unique_ptr<OperationInterface>> d_operations;
  };

  class AdditionOperation final : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override
    {
      return i_x + i_y;
    }

    static inline bool is_registered_in_factory =
      Registry::instance().registrate("add", std::make_unique<AdditionOperation>());
  };

  class SubtractionOperation final : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override
    {
      return i_x - i_y;
    }

    static inline bool is_registered_in_factory =
      Registry::instance().registrate("sub", std::make_unique<SubtractionOperation>());
  };

  class MultiplicationOperation final : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override
    {
      return i_x * i_y;
    }

    static inline bool is_registered_in_factory =
      Registry::instance().registrate("mul", std::make_unique<MultiplicationOperation>());
  };

  class DivisionOperation final : public OperationInterface
  {
  public:
    int do_operation(int i_x, int i_y) const override
    {
      return i_x / i_y;
    }

    static inline bool is_registered_in_factory =
      Registry::instance().registrate("div", std::make_unique<DivisionOperation>());
  };

  class Factory
  {
  public:
    OperationInterface& create(std::string_view i_operation)
    {
      return Registry::instance().get(i_operation);
    }
  };
}

namespace bench
{
  int do_math_virtual_factory_auto_reg(std::string_view i_operation, int i_x, int i_y)
  {
    Factory factory;
    const auto& operation = factory.create(i_operation);
    return operation.do_operation(i_x, i_y);
  }
}
