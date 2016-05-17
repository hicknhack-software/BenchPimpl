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
#pragma once
#include "ChainedPimplBase.h"

class ChainedDeleterPimplPoint : protected ChainedPimpl::Base<ChainedDeleterPimplPoint> {
  typedef ChainedDeleterPimplPoint Interface;
  friend class chained;

public:
  static ChainedDeleterPimplPoint* create(double x, double y);
  static std::shared_ptr<ChainedDeleterPimplPoint> make_shared(double x, double y);

protected:
  class Implementation;
  ChainedDeleterPimplPoint();

private:
  ChainedDeleterPimplPoint(double x, double y);

public:
  double x() const;
  double y() const;

protected:
  static size_t implementation_size();
  void destruct_implementation();
};
