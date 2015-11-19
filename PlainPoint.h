#pragma once

class PlainPoint
{
public:
	PlainPoint(double x, double y);
	
	double x() const;
	double y() const;
	
private:
	double m_x, m_y;
};
