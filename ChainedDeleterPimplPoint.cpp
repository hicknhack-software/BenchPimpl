#include "ChainedDeleterPimplPoint.h"
#include "ChainedDeleterPimplPoint_p.h"

ChainedDeleterPimplPoint::Implementation::Implementation(double x, double y)
	: x(x)
	, y(y)
{}

ChainedDeleterPimplPoint* ChainedDeleterPimplPoint::create(double x, double y)
{
	return chained_create<Interface>(x, y);
}

std::shared_ptr<ChainedDeleterPimplPoint> ChainedDeleterPimplPoint::createShared(double x, double y)
{
	return chained_createShared<Interface>(x, y);
}

double ChainedDeleterPimplPoint::x() const
{
	return p(this)->x;
}

double ChainedDeleterPimplPoint::y() const
{
	return p(this)->y;	
}

ChainedDeleterPimplPoint::ChainedDeleterPimplPoint()
{}

ChainedDeleterPimplPoint::ChainedDeleterPimplPoint(double x, double y)
{
	new (p(this)) Implementation(x, y);	
}

size_t ChainedDeleterPimplPoint::ImplementationSize()
{
	return chained_size<Interface>();
}

void ChainedDeleterPimplPoint::deleteImplementation()
{
	chained_deleteImplementation(this);
}
