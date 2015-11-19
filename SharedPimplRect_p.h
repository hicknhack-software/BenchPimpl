#pragma once
#include "SharedPimplRect.h"
#include "SharedPimplPoint_p.h"

class SharedPimplRect::Implementation : public SharedPimplPoint::Implementation
{
public:
	Implementation(double x, double y, double w, double h);
	
	double sum() const;
	
	double w, h;
};
