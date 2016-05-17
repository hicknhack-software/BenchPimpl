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
 * plain unique pointer based pimpl implementation
 *
 * advantages:
 * * hides implementation from class users
 * * allows for derived implementations
 *
 * disadvantages:
 * * dynamic allocation is always required
 * * you need to implement copy semantics (clone the implementation)
 * * requires protected constructor to pass more spectfic implementations
 */
template <typename Tag>
class UniquePimplBase {
protected:
  struct Implementation {
    virtual ~Implementation() {
    }
  };

protected:
  UniquePimplBase(Implementation* implementation) : m_p(implementation) {
  }

  virtual ~UniquePimplBase() {
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
  struct PrivateDeleter {
    void
    operator()(Implementation* p) const {
      delete p;
    }
  };
  const std::unique_ptr<Implementation, PrivateDeleter> m_p;
};
