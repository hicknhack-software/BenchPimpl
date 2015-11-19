#pragma once
#include "UniquePimplRect.h"
#include "UniquePimplPoint_p.h"

class UniquePimplRect::Implementation : public UniquePimplPoint::Implementation
{
public:
	Implementation(double x, double y, double w, double h);
	
	double sum() const;
	
	double w, h;
};
