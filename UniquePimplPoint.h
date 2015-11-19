#pragma once
#include "UniquePimplBase.h"

class UniquePimplPoint
		: protected UniquePimplBase<UniquePimplPoint>
{
public:
	UniquePimplPoint(double x, double y);

	double x() const;
	double y() const;
	
protected:
    class Implementation;
	UniquePimplPoint(Implementation*);
};
