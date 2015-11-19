#pragma once
#include "SharedPimplBase.h"

class SharedPimplPoint
		: protected SharedPimplBase<SharedPimplPoint>
{
	typedef SharedPimplBase<SharedPimplPoint> Base;
public:
	SharedPimplPoint(double x, double y);
	
	double x() const;
	double y() const;
	
protected:
	class Implementation;
	SharedPimplPoint(std::shared_ptr<Implementation>);	
};
