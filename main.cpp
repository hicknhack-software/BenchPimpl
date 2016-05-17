#include "benchmark/benchmark.h"

template <typename T>
void
doNotOptimize(T k) {
#if defined(_MSC_VER) && !defined(__clang__)
  static volatile T m;
  m = k;
//__asm { xor eax, k }
//__asm { nop }; (void)k;
#else
  benchmark::DoNotOptimize(k);
#endif
}

/////////////////////////////////////////////////////
#include "PlainRect.h"

void
Plain(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto rect = new PlainRect(1, 2, 3, 4);
    auto sum = rect->sum();
    benchmark::DoNotOptimize(sum);
    delete rect;
  }
}
BENCHMARK(Plain);

#include <memory>

void
SharedPlain(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto rect = std::make_shared<PlainRect>(1, 2, 3, 4);
    auto sum = rect->sum();
    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(SharedPlain);

/////////////////////////////////////////////////////
#include "UniquePimplRect.h"

void
UniquePimpl(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto rect = new UniquePimplRect(1, 2, 3, 4);
    auto sum = rect->sum();
    doNotOptimize(sum);
    delete rect;
  }
}
BENCHMARK(UniquePimpl);

/////////////////////////////////////////////////////
#include "SharedPimplRect.h"

void
SharedPimpl(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto rect = new SharedPimplRect(1, 2, 3, 4);
    auto sum = rect->sum();
    doNotOptimize(sum);
    delete rect;
  }
}
BENCHMARK(SharedPimpl);

/////////////////////////////////////////////////////
#include "ChainedPimplRect.h"

void
BenchChainedPimpl(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto rect = ChainedPimplRect::create(1, 2, 3, 4);
    auto sum = rect->sum();
    doNotOptimize(sum);
    delete rect;
  }
}
BENCHMARK(BenchChainedPimpl);

void
SharedChainedPimpl(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto rect = ChainedPimplRect::make_shared(1, 2, 3, 4);
    auto sum = rect->sum();
    doNotOptimize(sum);
  }
}
BENCHMARK(SharedChainedPimpl);

/////////////////////////////////////////////////////
#include "ChainedDeleterPimplRect.h"

void
ChainedDeleterPimpl(benchmark::State& state) {
  while (state.KeepRunning()) {
    auto rect = ChainedDeleterPimplRect::create(1, 2, 3, 4);
    auto sum = rect->sum();
    doNotOptimize(sum);
    delete rect;
  }
}
BENCHMARK(ChainedDeleterPimpl);

BENCHMARK_MAIN()
