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
#include "UniquePimplRect.h"
#include "UniquePimplRect_p.h"

UniquePimplRect::Implementation::Implementation(double x, double y, double w, double h)
    : UniquePimplPoint::Implementation(x, y), w(w), h(h) {
}

double
UniquePimplRect::Implementation::sum() const {
  return x + y + w + h;
}

UniquePimplRect::UniquePimplRect(double x, double y, double w, double h)
    : UniquePimplPoint(new Implementation(x, y, w, h)) {
}

double
UniquePimplRect::width() const {
  return p<Implementation>()->w;
}

double
UniquePimplRect::height() const {
  return p<Implementation>()->h;
}

double
UniquePimplRect::sum() const {
  return p<Implementation>()->sum();
}

UniquePimplRect::UniquePimplRect(UniquePimplRect::Implementation* implementation)
    : UniquePimplPoint(implementation) {
}
