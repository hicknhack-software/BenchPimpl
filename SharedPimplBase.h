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
#include <memory>

/*
 * shared pointer based pimpl implementation
 *
 * advantages:
 * * hides implementation from class users
 * * feels like a value object
 * * allows for derived implementations
 *
 * disadvantages:
 * * dynamic allocation is always required
 * * requires protected constructor to pass more spectfic implementations
 */
template <typename Tag>
class SharedPimplBase {
protected:
  struct Implementation {
    virtual ~Implementation() {
    }
  };

protected:
  SharedPimplBase(std::shared_ptr<Implementation> implementation) : m_p(implementation) {
  }

  virtual ~SharedPimplBase() {
  }

  template <typename T>
  T*
  p() {
    return static_cast<T*>(m_p.get());
  }

  template <typename T>
  const T*
  p() const {
    return static_cast<const T*>(m_p.get());
  }

private:
  std::shared_ptr<Implementation> m_p;
};
