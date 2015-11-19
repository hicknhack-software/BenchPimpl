#include "PlainRect.h"

PlainRect::PlainRect(double x, double y, double w, double h)
	: PlainPoint(x, y)
	, m_w(w)
	, m_h(h)
{}

double PlainRect::width() const
{
	return m_w;
}

double PlainRect::height() const
{
	return m_h;
}

double PlainRect::sum() const
{
	return x() + y() + m_w + m_h;
}

