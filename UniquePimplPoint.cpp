#include "UniquePimplPoint.h"
#include "UniquePimplPoint_p.h"

UniquePimplPoint::Implementation::Implementation(double x, double y) 
	: x(x) 
	, y(y)
{}

UniquePimplPoint::UniquePimplPoint(double x, double y)
	: UniquePimplBase(new Implementation(x, y))
{}

double UniquePimplPoint::x() const
{
	return p<Implementation>()->x;
}

double UniquePimplPoint::y() const
{
	return p<Implementation>()->y;	
}

UniquePimplPoint::UniquePimplPoint(UniquePimplPoint::Implementation* implementation)
	: UniquePimplBase(implementation)
{}

