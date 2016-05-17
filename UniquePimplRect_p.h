#pragma once
#include "UniquePimplPoint_p.h"
#include "UniquePimplRect.h"

class UniquePimplRect::Implementation : public UniquePimplPoint::Implementation {
public:
  Implementation(double x, double y, double w, double h);

  double sum() const;

  double w, h;
};
