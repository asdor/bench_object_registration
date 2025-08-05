#include <compile_time_by_variant/do_math.hpp>
#include <compile_time_by_variant_self_reg/do_math.hpp>
#include <naive_by_condition/do_math.hpp>
#include <virtual_factory/do_math.hpp>
#include <virtual_factory_self_reg/do_math.hpp>

#include <random>
#include <unordered_map>

#include <benchmark/benchmark.h>

namespace
{
  const std::unordered_map<int, std::string> operations = { { 0, "add" }, { 1, "sub" }, { 2, "mul" }, { 3, "div" } };

  class Randomizer
  {
  public:
    Randomizer() : d_gen(d_rd()), d_int_distrib(1, 100), d_op_distrib(0, 3)
    {
    }

    int random_int()
    {
      return d_int_distrib(d_gen);
    }

    std::string random_op()
    {
      const int index = d_op_distrib(d_gen);
      return operations.at(index);
    }

  private:
    std::random_device d_rd;
    std::mt19937 d_gen;
    std::uniform_int_distribution<int> d_int_distrib;
    std::uniform_int_distribution<int> d_op_distrib;
  };

  template<typename Func>
  void bench_do_math(benchmark::State& state, Func func)
  {
    Randomizer randomizer;
    for (auto _ : state)
    {
      int x = randomizer.random_int();
      int y = randomizer.random_int();
      const auto op = randomizer.random_op();
      benchmark::DoNotOptimize(func(op, x, y));
    }
  }
}

BENCHMARK_CAPTURE(bench_do_math, naive_test, bench::do_math_naive);
BENCHMARK_CAPTURE(bench_do_math, variant_test, bench::do_math_by_variant);
BENCHMARK_CAPTURE(bench_do_math, variant_self_reg_test, bench::do_math_by_variant_self_reg);
BENCHMARK_CAPTURE(bench_do_math, factory_test, bench::do_math_virtual_factory);
BENCHMARK_CAPTURE(bench_do_math, factory_auto_reg_test, bench::do_math_virtual_factory_auto_reg);

BENCHMARK_MAIN();
