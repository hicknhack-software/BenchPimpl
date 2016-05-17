#pragma once
#include "ChainedPimplBase.h"

class ChainedPimplPoint : protected ChainedPimpl::Base<ChainedPimplPoint> {
  typedef ChainedPimplPoint Interface;
  friend class chained;
  class Implementation;

protected:
  ChainedPimplPoint(double x, double y);

public:
  ~ChainedPimplPoint();

public:
  static ChainedPimplPoint* create(double x, double y);
  static std::shared_ptr<ChainedPimplPoint> make_shared(double x, double y);

  double x() const;
  double y() const;

protected:
  static size_t implementation_size();
};
