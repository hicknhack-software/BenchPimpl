#pragma once
#include "ChainedDeleterPimplPoint.h"

class ChainedDeleterPimplPoint::Implementation
		: protected Chained::Implementation<Interface>
{
public:
	Implementation(double x, double y);
	
    double x, y;
};
