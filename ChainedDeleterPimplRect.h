#pragma once
#include "ChainedDeleterPimplPoint.h"

class ChainedDeleterPimplRect : public ChainedDeleterPimplPoint {
  typedef ChainedDeleterPimplRect Interface;
  friend class chained;

public:
  static ChainedDeleterPimplRect* create(double x, double y, double w, double h);
  static std::shared_ptr<ChainedDeleterPimplRect> make_shared(double x, double y, double w,
                                                              double h);

protected:
  class Implementation;
  ChainedDeleterPimplRect();

private:
  ChainedDeleterPimplRect(double x, double y, double w, double h);

public:
  double width() const;
  double height() const;
  double sum() const;

protected:
  static size_t implementation_size();
  void destruct_implementation();
};
