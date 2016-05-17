#pragma once
#include "UniquePimplPoint.h"

class UniquePimplPoint::Implementation : public UniquePimplBase<UniquePimplPoint>::Implementation {
public:
  Implementation(double x, double y);

  double x, y;
};
