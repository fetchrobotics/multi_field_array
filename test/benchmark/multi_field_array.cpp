/**
 * @copyright 2021 MF
 * @author Brian Cairl
 */

// C++ Standard Library
#include <numeric>
#include <string>
#include <vector>

// GBenchmark
#include <benchmark/benchmark.h>

// MF
#include <mf/multi_field_array.hpp>


struct Two_Fields
{
  float a;
  std::string b;
};

struct Many_Fields
{
  float a;
  std::string b;
  int c, d, e, f;
};


//
// ITERATION BENCHMARKING
//

static void Iteration_One_Of_Two_Fields_MFA(benchmark::State& state)
{
  mf::multi_field_array<float, std::string> multi_field_array;
  multi_field_array.resize(1000000);

  for (auto _ : state)
  {
    auto view = multi_field_array.view<float, std::string>();

    const float sum = std::accumulate(
      view.begin(), view.end(), 0.f, [](float prev, const auto& tuple) { return prev + std::get<0>(tuple); });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_One_Of_Two_Fields_MFA);


static void Iteration_One_Of_Two_Fields_Vec(benchmark::State& state)
{
  std::vector<Two_Fields> vector_analogue;
  vector_analogue.resize(1000000);

  for (auto _ : state)
  {
    const float sum =
      std::accumulate(vector_analogue.begin(), vector_analogue.end(), 0.f, [](float prev, const auto& element) {
        return prev + element.a;
      });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_One_Of_Two_Fields_Vec);


static void Iteration_Two_Of_Two_Fields_MFA(benchmark::State& state)
{
  mf::multi_field_array<float, std::string> multi_field_array;
  multi_field_array.resize(1000000);

  for (auto _ : state)
  {
    auto view = multi_field_array.view<float, std::string>();

    const float sum = std::accumulate(view.begin(), view.end(), 0.f, [](float prev, const auto& tuple) {
      return prev + std::get<0>(tuple) + std::get<1>(tuple).size();
    });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_Two_Of_Two_Fields_MFA);


static void Iteration_Two_Of_Two_Fields_Vec(benchmark::State& state)
{
  std::vector<Two_Fields> vector_analogue;
  vector_analogue.resize(1000000);

  for (auto _ : state)
  {
    const float sum =
      std::accumulate(vector_analogue.begin(), vector_analogue.end(), 0.f, [](float prev, const auto& element) {
        return prev + element.a + element.b.size();
      });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_Two_Of_Two_Fields_Vec);


static void Iteration_Two_Of_Many_Fields_MFA_View(benchmark::State& state)
{
  mf::multi_field_array<float, std::string, int, int, int, int> multi_field_array;
  multi_field_array.resize(1000000);

  for (auto _ : state)
  {
    auto view = multi_field_array.view<float, std::string>();

    const float sum = std::accumulate(view.begin(), view.end(), 0.f, [](float prev, const auto& tuple) {
      return prev + std::get<0>(tuple) + std::get<1>(tuple).size();
    });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_Two_Of_Many_Fields_MFA_View);


static void Iteration_Two_Of_Many_Fields_MFA_All_Fields(benchmark::State& state)
{
  mf::multi_field_array<float, std::string, int, int, int, int> multi_field_array;
  multi_field_array.resize(1000000);

  for (auto _ : state)
  {
    auto view = multi_field_array.view();

    const float sum = std::accumulate(view.begin(), view.end(), 0.f, [](float prev, const auto& tuple) {
      return prev + std::get<0>(tuple) + std::get<1>(tuple).size();
    });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_Two_Of_Many_Fields_MFA_All_Fields);


static void Iteration_Two_Of_Many_Fields_Vec(benchmark::State& state)
{
  std::vector<Many_Fields> vector_analogue;
  vector_analogue.resize(1000000);

  for (auto _ : state)
  {
    const float sum =
      std::accumulate(vector_analogue.begin(), vector_analogue.end(), 0.f, [](float prev, const auto& element) {
        return prev + element.a + element.b.size();
      });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_Two_Of_Many_Fields_Vec);


static void Iteration_One_Of_Many_Fields_MFA_View(benchmark::State& state)
{
  mf::multi_field_array<float, std::string, int, int, int, int> multi_field_array;
  multi_field_array.resize(1000000);

  for (auto _ : state)
  {
    auto view = multi_field_array.view<float, std::string>();

    const float sum = std::accumulate(
      view.begin(), view.end(), 0.f, [](float prev, const auto& tuple) { return prev + std::get<0>(tuple); });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_One_Of_Many_Fields_MFA_View);


static void Iteration_One_Of_Many_Fields_MFA_All_Fields(benchmark::State& state)
{
  mf::multi_field_array<float, std::string, int, int, int, int> multi_field_array;
  multi_field_array.resize(1000000);

  for (auto _ : state)
  {
    auto view = multi_field_array.view();

    const float sum = std::accumulate(
      view.begin(), view.end(), 0.f, [](float prev, const auto& tuple) { return prev + std::get<0>(tuple); });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_One_Of_Many_Fields_MFA_All_Fields);


static void Iteration_One_Of_Many_Fields_Vec(benchmark::State& state)
{
  std::vector<Many_Fields> vector_analogue;
  vector_analogue.resize(1000000);

  for (auto _ : state)
  {
    const float sum =
      std::accumulate(vector_analogue.begin(), vector_analogue.end(), 0.f, [](float prev, const auto& element) {
        return prev + element.a;
      });

    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(Iteration_One_Of_Many_Fields_Vec);

//
// ALLOCATION BENCHMARKING
//


static void Allocation_Two_Fields_MFA(benchmark::State& state)
{
  for (auto _ : state)
  {
    mf::multi_field_array<float, std::string> multi_field_array;
    multi_field_array.resize(10000);
    benchmark::DoNotOptimize(multi_field_array);
  }
}
BENCHMARK(Allocation_Two_Fields_MFA);


static void Allocation_Two_Fields_Vec(benchmark::State& state)
{
  for (auto _ : state)
  {
    std::vector<Two_Fields> vector_analogue;
    vector_analogue.resize(10000);
    benchmark::DoNotOptimize(vector_analogue);
  }
}
BENCHMARK(Allocation_Two_Fields_Vec);


static void Allocation_Many_Fields_MFA(benchmark::State& state)
{
  for (auto _ : state)
  {
    mf::multi_field_array<float, std::string, int, int, int, int> multi_field_array;
    multi_field_array.resize(10000);
    benchmark::DoNotOptimize(multi_field_array);
  }
}
BENCHMARK(Allocation_Many_Fields_MFA);


static void Allocation_Many_Fields_Vec(benchmark::State& state)
{
  for (auto _ : state)
  {
    std::vector<Many_Fields> vector_analogue;
    vector_analogue.resize(10000);
    benchmark::DoNotOptimize(vector_analogue);
  }
}
BENCHMARK(Allocation_Many_Fields_Vec);


BENCHMARK_MAIN();
