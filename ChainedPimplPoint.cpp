#include "ChainedPimplPoint.h"

class ChainedPimplPoint::Implementation
		: protected chained::Implementation<ChainedPimplPoint>
{
public:
	Implementation(double x, double y)
		: x(x)
		, y(y)
	{}

	double x, y;
};

ChainedPimplPoint::ChainedPimplPoint(double x, double y)
{
	new (p(this)) Implementation(x, y);
}

ChainedPimplPoint::~ChainedPimplPoint()
{
	p(this)->~Implementation();
}

ChainedPimplPoint* ChainedPimplPoint::create(double x, double y)
{
	return chained::create<Interface>(x, y);
}

std::shared_ptr<ChainedPimplPoint> ChainedPimplPoint::make_shared(double x, double y)
{
	return chained::make_shared<Interface>(x, y);
}

double ChainedPimplPoint::x() const
{
	return p(this)->x;
}

double ChainedPimplPoint::y() const
{
	return p(this)->y;
}

size_t ChainedPimplPoint::implementation_size()
{
	return chained::implementation_size<Interface>();
}

