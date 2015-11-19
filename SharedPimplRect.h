#pragma once
#include "SharedPimplPoint.h"

class SharedPimplRect : public SharedPimplPoint
{
public:
	SharedPimplRect(double x, double y, double w, double h);

	double width() const;
	double height() const;
	double sum() const;
	
protected:
	class Implementation;
	SharedPimplRect(std::shared_ptr<Implementation>);
};
