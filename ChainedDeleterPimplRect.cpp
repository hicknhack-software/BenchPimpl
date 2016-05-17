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
#include "ChainedDeleterPimplRect.h"
#include "ChainedDeleterPimplRect_p.h"

ChainedDeleterPimplRect::Implementation::Implementation(double x, double y, double w, double h)
    : ChainedDeleterPimplPoint::Implementation(x, y), w(w), h(h) {
}

double
ChainedDeleterPimplRect::Implementation::sum() const {
  return w + h + x + y;
}

ChainedDeleterPimplRect*
ChainedDeleterPimplRect::create(double x, double y, double w, double h) {
  return chained::create<Interface>(x, y, w, h);
}

std::shared_ptr<ChainedDeleterPimplRect>
ChainedDeleterPimplRect::make_shared(double x, double y, double w, double h) {
  return chained::make_shared<Interface>(x, y, w, h);
}

double
ChainedDeleterPimplRect::width() const {
  return p(this)->w;
}

double
ChainedDeleterPimplRect::height() const {
  return p(this)->h;
}

double
ChainedDeleterPimplRect::sum() const {
  return p(this)->sum();
}

ChainedDeleterPimplRect::ChainedDeleterPimplRect() {
}

ChainedDeleterPimplRect::ChainedDeleterPimplRect(double x, double y, double w, double h) {
  new (p(this)) Implementation(x, y, w, h);
}

size_t
ChainedDeleterPimplRect::implementation_size() {
  return chained::implementation_size<Interface>();
}

void
ChainedDeleterPimplRect::destruct_implementation() {
  chained::destruct_implementation(this);
}
