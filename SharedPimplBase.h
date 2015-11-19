#pragma once
#include <memory>

/*
 * shared pointer based pimpl implementation
 * 
 * advantages:
 * * hides implementation from class users
 * * feels like a value object
 * * allows for derived implementations
 * 
 * disadvantages:
 * * dynamic allocation is always required
 * * requires protected constructor to pass more spectfic implementations
 */
template<typename Tag>
class SharedPimplBase
{	
protected:
	struct Implementation
	{
		virtual ~Implementation() {}
	};

protected:
	SharedPimplBase(std::shared_ptr<Implementation> implementation)
		: m_p(implementation)
	{}

	virtual ~SharedPimplBase()
	{}

	template<typename T>
	T* p()
	{
		return static_cast<T*>(m_p.get());
	}

	template<typename T>
	const T* p() const
	{
		return static_cast<const T*>(m_p.get());
	}

private:
    std::shared_ptr<Implementation> m_p;	
};
