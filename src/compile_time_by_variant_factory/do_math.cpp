#include "compile_time_by_variant_factory/do_math.hpp"

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

    static constexpr std::string_view operation_name = "add";
  };

  class SubtractionOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;

    static constexpr std::string_view operation_name = "sub";
  };

  class MultiplicationOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;

    static constexpr std::string_view operation_name = "mul";
  };

  class DivisionOperation
  {
  public:
    int do_operation(int i_x, int i_y) const;

    static constexpr std::string_view operation_name = "div";
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

  template<class... Ts>
  class VariantFactory
  {
  public:
    using operations_t = std::variant<Ts...>;

    static constexpr bool from_string(std::string_view i_operation_name, operations_t& i_operation)
    {
      return (try_find<Ts>(i_operation_name, i_operation) || ...);
    }

  private:
    template<class T>
    static constexpr bool try_find(std::string_view i_operation_name, operations_t& i_operation)
    {
      if (i_operation_name == T::operation_name)
      {
        i_operation.template emplace<T>();
        return true;
      }

      return false;
    }
  };

  using variant_factory_t =
    VariantFactory<AdditionOperation, SubtractionOperation, MultiplicationOperation, DivisionOperation>;
}

namespace bench
{
  int do_math_by_variant_factory(std::string_view i_operation_name, int i_x, int i_y)
  {
    variant_factory_t::operations_t operation;
    const bool is_found = variant_factory_t::from_string(i_operation_name, operation);
    if (!is_found)
      throw std::invalid_argument(std::format("Unknown operation: {}", i_operation_name));
    return std::visit([i_x, i_y](const auto& i_op) { return i_op.do_operation(i_x, i_y); }, operation);
  }
}
