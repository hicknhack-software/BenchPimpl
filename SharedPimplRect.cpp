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
#include "SharedPimplRect.h"
#include "SharedPimplRect_p.h"

SharedPimplRect::Implementation::Implementation(double x, double y, double w, double h)
    : SharedPimplPoint::Implementation(x, y), w(w), h(h) {
}

double
SharedPimplRect::Implementation::sum() const {
  return x + y + w + h;
}

SharedPimplRect::SharedPimplRect(double x, double y, double w, double h)
    : SharedPimplPoint(std::make_shared<Implementation>(x, y, w, h)) {
}

double
SharedPimplRect::width() const {
  return p<Implementation>()->w;
}

double
SharedPimplRect::height() const {
  return p<Implementation>()->h;
}

double
SharedPimplRect::sum() const {
  return p<Implementation>()->sum();
}

SharedPimplRect::SharedPimplRect(std::shared_ptr<SharedPimplRect::Implementation> implementation)
    : SharedPimplPoint(implementation) {
}
