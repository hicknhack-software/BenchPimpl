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
