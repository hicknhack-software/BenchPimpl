#pragma once
#include "ChainedDeleterPimplPoint.h"

class ChainedDeleterPimplRect : public ChainedDeleterPimplPoint
{
	typedef ChainedDeleterPimplRect Interface;
	friend class ChainedPimpl::Base<ChainedDeleterPimplPoint>;
public:
	static ChainedDeleterPimplRect* create(double x, double y, double w, double h);
	static std::shared_ptr<ChainedDeleterPimplRect> createShared(double x, double y, double w, double h);

protected:
	class Implementation;
	ChainedDeleterPimplRect();
private:
	ChainedDeleterPimplRect(double x, double y, double w, double h);

public:
	double width() const;
	double height() const;
	double sum() const;

protected:
	static size_t ImplementationSize();
	void deleteImplementation();
};
