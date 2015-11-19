#pragma once
#include "UniquePimplPoint.h"

class UniquePimplRect : public UniquePimplPoint
{
public:
	UniquePimplRect(double x, double y, double w, double h);

	double width() const;
	double height() const;
	double sum() const;
	
protected:
	class Implementation;
	UniquePimplRect(Implementation*);
};
