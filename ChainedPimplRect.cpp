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
#include "ChainedPimplRect.h"

class ChainedPimplRect::Implementation : protected chained::Implementation<ChainedPimplRect> {
public:
  Implementation(double w, double h) : w(w), h(h) {
  }

  double
  sum() const {
    return w + h + i()->x() + i()->y();
  }

  double w, h;
};

ChainedPimplRect::ChainedPimplRect(double x, double y, double w, double h)
    : ChainedPimplPoint(x, y) {
  new (p(this)) Implementation(w, h);
}

ChainedPimplRect::~ChainedPimplRect() {
  p(this)->~Implementation();
}

ChainedPimplRect*
ChainedPimplRect::create(double x, double y, double w, double h) {
  return chained::create<Interface>(x, y, w, h);
}

std::shared_ptr<ChainedPimplRect>
ChainedPimplRect::make_shared(double x, double y, double w, double h) {
  return chained::make_shared<Interface>(x, y, w, h);
}

double
ChainedPimplRect::width() const {
  return p(this)->w;
}

double
ChainedPimplRect::height() const {
  return p(this)->h;
}

double
ChainedPimplRect::sum() const {
  return p(this)->sum();
}

size_t
ChainedPimplRect::implementation_size() {
  return chained::implementation_size<Interface>() + ChainedPimplPoint::implementation_size();
}
