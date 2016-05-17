#pragma once
#include "ChainedDeleterPimplPoint.h"

class ChainedDeleterPimplPoint::Implementation : protected chained::Implementation<Interface> {
public:
  Implementation(double x, double y);

  double x, y;
};
