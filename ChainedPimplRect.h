#pragma once
#include "ChainedPimplPoint.h"

class ChainedPimplRect : public ChainedPimplPoint
{
	typedef ChainedPimplRect Interface;
	friend class ChainedPimpl::Base<ChainedPimplPoint, ChainedPimpl::VirtualBase>;
	class Implementation;

protected:
	ChainedPimplRect(double x, double y, double w, double h);

public:
	~ChainedPimplRect();

public:
	static ChainedPimplRect* create(double x, double y, double w, double h);
	static std::shared_ptr<ChainedPimplRect> createShared(double x, double y, double w, double h);

	double width() const;
	double height() const;
	double sum() const;

protected:
	static size_t ImplementationSize();
};
