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
#include "ChainedDeleterPimplPoint.h"

class ChainedDeleterPimplRect : public ChainedDeleterPimplPoint {
  typedef ChainedDeleterPimplRect Interface;
  friend class chained;

public:
  static ChainedDeleterPimplRect* create(double x, double y, double w, double h);
  static std::shared_ptr<ChainedDeleterPimplRect> make_shared(double x, double y, double w,
                                                              double h);

protected:
  class Implementation;
  ChainedDeleterPimplRect();

private:
  ChainedDeleterPimplRect(double x, double y, double w, double h);

public:
  double width() const;
  double height() const;
  double sum() const;

protected:
  static size_t implementation_size();
  void destruct_implementation();
};
