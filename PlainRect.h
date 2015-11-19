#pragma once
#include "PlainPoint.h"

class PlainRect : public PlainPoint
{
public:
	PlainRect(double x, double y, double w, double h);
	
	double width() const;
	double height() const;
	double sum() const;
	
private:
	double m_w, m_h;
};
