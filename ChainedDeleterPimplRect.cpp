#include "ChainedDeleterPimplRect.h"
#include "ChainedDeleterPimplRect_p.h"

ChainedDeleterPimplRect::Implementation::Implementation(double x, double y, double w, double h)
	: ChainedDeleterPimplPoint::Implementation(x, y)
	, w(w)
	, h(h)
{}

double ChainedDeleterPimplRect::Implementation::sum() const 
{
	return w + h + x + y;
}

ChainedDeleterPimplRect* ChainedDeleterPimplRect::create(double x, double y, double w, double h)
{
	return chained_create<Interface>(x, y, w, h);
}

std::shared_ptr<ChainedDeleterPimplRect> ChainedDeleterPimplRect::createShared(double x, double y, double w, double h)
{
	return chained_createShared<Interface>(x, y, w, h);
}

double ChainedDeleterPimplRect::width() const
{
	return p(this)->w;	
}

double ChainedDeleterPimplRect::height() const
{
	return p(this)->h;
}

double ChainedDeleterPimplRect::sum() const
{
	return p(this)->sum();
}

ChainedDeleterPimplRect::ChainedDeleterPimplRect()
{}

ChainedDeleterPimplRect::ChainedDeleterPimplRect(double x, double y, double w, double h)
{
	new (p(this)) Implementation(x, y, w, h);	
}

size_t ChainedDeleterPimplRect::ImplementationSize()
{
	return chained_size<Interface>();
}

void ChainedDeleterPimplRect::deleteImplementation()
{
	chained_deleteImplementation(this);	
}
