#include "compile_time_by_variant/do_math.hpp"

#include <algorithm>
#include <array>
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

    static constexpr operations_t from_string(std::string_view i_operation_name)
    {
      auto it = std::find_if(
        d_table.begin(), d_table.end(), [i_operation_name](const auto& el) { return el.first == i_operation_name; });
      if (it == d_table.end())
        throw std::invalid_argument(std::format("Unknown operation: {}", i_operation_name));
      else
        return it->second();
    }

  private:
    using make_t = operations_t (*)();

    template<class T>
    static constexpr operations_t make()
    {
      return T{};
    }
    static inline constinit std::array<std::pair<std::string_view, make_t>, sizeof...(Ts)> d_table = {
      { { Ts::operation_name, &make<Ts> }... }
    };
  };

  using variant_factory_t =
    VariantFactory<AdditionOperation, SubtractionOperation, MultiplicationOperation, DivisionOperation>;
}

namespace bench
{
  int do_math_by_variant_self_reg(std::string_view i_operation, int i_x, int i_y)
  {
    auto x = variant_factory_t::from_string(i_operation);
    return std::visit([i_x, i_y](const auto& i_op) { return i_op.do_operation(i_x, i_y); }, x);
  }
}
