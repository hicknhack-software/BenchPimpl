#pragma once
#include "ChainedPimplBase.h"

class ChainedPimplPoint
		: public ChainedPimpl::Base<ChainedPimplPoint, ChainedPimpl::VirtualBase>
{
	typedef ChainedPimplPoint Interface;
	friend class ChainedPimpl::Base<ChainedPimplPoint, ChainedPimpl::VirtualBase>;
	class Implementation;

protected:
	ChainedPimplPoint(double x, double y);

public:
	~ChainedPimplPoint();

public:
	static ChainedPimplPoint* create(double x, double y);
	static std::shared_ptr<ChainedPimplPoint> createShared(double x, double y);

	double x() const;
	double y() const;

protected:
	static size_t ImplementationSize();
};
