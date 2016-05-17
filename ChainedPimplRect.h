#pragma once
#include "ChainedPimplPoint.h"

class ChainedPimplRect : public ChainedPimplPoint {
  typedef ChainedPimplRect Interface;
  friend class chained;
  class Implementation;

protected:
  ChainedPimplRect(double x, double y, double w, double h);

public:
  ~ChainedPimplRect();

public:
  static ChainedPimplRect* create(double x, double y, double w, double h);
  static std::shared_ptr<ChainedPimplRect> make_shared(double x, double y, double w, double h);

  double width() const;
  double height() const;
  double sum() const;

protected:
  static size_t implementation_size();
};
