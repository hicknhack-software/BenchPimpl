#pragma once
#include "SharedPimplPoint.h"

class SharedPimplPoint::Implementation
		: public SharedPimplBase<SharedPimplPoint>::Implementation
{
public:
	Implementation(double x, double y);
	
    double x, y;
};
