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
#include "ChainedDeleterPimplPoint.h"
#include "ChainedDeleterPimplPoint_p.h"

ChainedDeleterPimplPoint::Implementation::Implementation(double x, double y) : x(x), y(y) {
}

ChainedDeleterPimplPoint*
ChainedDeleterPimplPoint::create(double x, double y) {
  return chained::create<Interface>(x, y);
}

std::shared_ptr<ChainedDeleterPimplPoint>
ChainedDeleterPimplPoint::make_shared(double x, double y) {
  return chained::make_shared<Interface>(x, y);
}

double
ChainedDeleterPimplPoint::x() const {
  return p(this)->x;
}

double
ChainedDeleterPimplPoint::y() const {
  return p(this)->y;
}

ChainedDeleterPimplPoint::ChainedDeleterPimplPoint() {
}

ChainedDeleterPimplPoint::ChainedDeleterPimplPoint(double x, double y) {
  new (p(this)) Implementation(x, y);
}

size_t
ChainedDeleterPimplPoint::implementation_size() {
  return chained::implementation_size<Interface>();
}

void
ChainedDeleterPimplPoint::destruct_implementation() {
  chained::destruct_implementation(this);
}
