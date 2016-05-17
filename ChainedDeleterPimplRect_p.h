#pragma once
#include "ChainedDeleterPimplPoint_p.h"
#include "ChainedDeleterPimplRect.h"

class ChainedDeleterPimplRect::Implementation : public ChainedDeleterPimplPoint::Implementation {
public:
  Implementation(double x, double y, double w, double h);

  double sum() const;

  double w, h;
};
