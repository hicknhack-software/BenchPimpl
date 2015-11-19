#pragma once
#include "ChainedPimplBase.h"

class ChainedDeleterPimplPoint
		: public ChainedPimpl::Base<ChainedDeleterPimplPoint>
{
	typedef ChainedDeleterPimplPoint Interface;
	friend class ChainedPimpl::Base<ChainedDeleterPimplPoint>;
public:
	static ChainedDeleterPimplPoint* create(double x, double y);
	static std::shared_ptr<ChainedDeleterPimplPoint> createShared(double x, double y);

protected:
	class Implementation;
	ChainedDeleterPimplPoint();
private:
	ChainedDeleterPimplPoint(double x, double y);
public:
	~ChainedDeleterPimplPoint() {}

	double x() const;
	double y() const;

protected:
	static size_t ImplementationSize();
	void deleteImplementation();
};
