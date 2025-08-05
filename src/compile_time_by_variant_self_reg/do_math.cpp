#include "compile_time_by_variant/do_math.hpp"

#include <format>
#include <functional>
#include <stdexcept>
#include <string_view>
#include <unordered_set>
#include <variant>

namespace
{
  class AdditionOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;

    static bool is_registered_in_factory;
  };

  class SubtractionOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;

    static bool is_registered_in_factory;
  };

  class MultiplicationOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;

    static bool is_registered_in_factory;
  };

  class DivisionOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;

    static bool is_registered_in_factory;
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

  using operations_t =
    std::variant<AdditionOperation, SubtractionOperation, MultiplicationOperation, DivisionOperation>;

  class Registry
  {
  public:
    static Registry& instance()
    {
      static Registry registry;
      return registry;
    }

    void set_operation(std::string_view i_operation_name, operations_t& i_operation) const
    {
      if (auto it = d_map.find(i_operation_name); it != d_map.end())
      {
        auto f = it->second;
        f(i_operation);
      }
      else
        throw std::invalid_argument(std::format("Unknown operation: {}", i_operation_name));
    }

    template<class T>
    bool registrate(std::string_view i_operation_name)
    {
      d_map[i_operation_name] = [](operations_t& i_operation) { i_operation.emplace<T>(); };
      return true;
    }

  private:
    std::unordered_map<std::string_view, std::function<void(operations_t&)>> d_map;
  };

  class OperationManager
  {
  private:
    operations_t d_operation;

  public:
    void set_operation(std::string_view i_operation)
    {
      Registry::instance().set_operation(i_operation, d_operation);
    }

    int do_operation(int i_x, int i_y) const
    {
      return std::visit([i_x, i_y](const auto& i_op) { return i_op.do_operation(i_x, i_y); }, d_operation);
    }
  };

  bool AdditionOperation::is_registered_in_factory = Registry::instance().registrate<AdditionOperation>("add");
  bool SubtractionOperation::is_registered_in_factory = Registry::instance().registrate<SubtractionOperation>("sub");
  bool MultiplicationOperation::is_registered_in_factory =
    Registry::instance().registrate<MultiplicationOperation>("mul");
  bool DivisionOperation::is_registered_in_factory = Registry::instance().registrate<DivisionOperation>("div");
}

namespace bench
{

  int do_math_by_variant_try(std::string_view i_operation, int i_x, int i_y)
  {
    OperationManager manager;
    manager.set_operation(i_operation);

    return manager.do_operation(i_x, i_y);
  }
}
