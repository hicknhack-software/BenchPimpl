/* BenchPimpl
 * Copyright 2016 HicknHack Software GmbH
 *
 * The original code can be found at:
 *    https://github.com/hicknhack-software/BenchPimpl
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
