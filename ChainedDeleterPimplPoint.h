#pragma once
#include "ChainedPimplBase.h"

class ChainedDeleterPimplPoint
		: protected ChainedPimpl::Base<ChainedDeleterPimplPoint>
{
	typedef ChainedDeleterPimplPoint Interface;
	friend class chained;
public:
	static ChainedDeleterPimplPoint* create(double x, double y);
	static std::shared_ptr<ChainedDeleterPimplPoint> make_shared(double x, double y);

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
	static size_t implementation_size();
	void destruct_implementation();
};
