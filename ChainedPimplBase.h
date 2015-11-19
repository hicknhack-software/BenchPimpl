#pragma once
#include <stdint.h>
#include <memory>

namespace ChainedPimpl
{

template<typename Tag>
class VirtualBase
{
protected:
	virtual ~VirtualBase() {}
	virtual void deleteImplementation() {}
	size_t sizeOfImplementation();
};

template<typename Tag>
class EmptyBase
{
protected:
	~EmptyBase() {}
	void deleteImplementation() {}
	size_t sizeOfImplementation();
};

/*
 * chain implementations directly behind the interface in memory
 *
 * advantages:
 * * hides implementation from class users
 * * all implementations are separated
 * * easy access from implementation to the interface
 * * always one allocation
 *
 * disadvantages:
 * * the implementation is more involved
 * * only factory methods are allow as C++ would not allocate enough memory
 * * feels like a pointer
 * * implementations cannot derive (only one destructor is allowed)
 */
template<typename Tag, template<typename> class BaseClass = EmptyBase>
class Base : protected BaseClass<Tag>
{
protected:
	typedef Base<Tag, BaseClass> Chained;

	template<typename Interface>
	struct Implementation
	{
		Interface& i()
		{
			auto ptr = reinterpret_cast<uint8_t*>(this);
			auto offset = chained_getImplementationOffset<Interface>();
			return *reinterpret_cast<Interface*>(ptr - offset);
		}

		const Interface& i() const
		{
			return const_cast<Implementation*>(this)->i();
		}
	};

private:
	template<typename Interface>
	struct ChainedDeleter
	{
		void operator()(Interface* interface)
		{
			interface->deleteImplementation();
			interface->~Interface();
		}
	};

protected:
	~Base() {}

	template <typename Interface>
	static void chained_deleteImplementation(Interface* interface)
	{
		typedef typename Interface::Implementation Implementation;
		p(interface)->~Implementation();
	}

	template <typename Interface, typename Base>
	static void chained_deleteImplementation(Interface* interface, Base* base)
	{
		typedef typename Interface::Implementation Implementation;
		p(interface)->~Implementation();
		base->deleteImplementation();
	}

	template <typename Interface, typename... Args>
	static Interface* chained_create(Args&&... args)
	{
		return new (chained_allocate<Interface>()) Interface(std::forward<Args>(args)...);
	}

	// Interface has to be the same as for chained_create
	template <typename Interface>
	static void chained_free(Interface* interface)
	{
		interface->deleteImplementation();
		interface->~Interface();
		auto ptr = reinterpret_cast<uint8_t*>(interface);
		delete[] ptr;
	}

	template <typename Interface, typename... Args>
	static std::unique_ptr<Interface, ChainedDeleter<Interface> > chained_createUnique(Args&&... args)
	{
		return new (chained_allocate<Interface>()) Interface(std::forward<Args>(args)...);
	}

	template <typename Interface, typename... Args>
	static std::shared_ptr<Interface> chained_createShared(Args&&... args)
	{
		auto alloc = ChainedAllocator<Interface>();
		return std::allocate_shared< ChainedWrapper<Interface> >(alloc, std::forward<Args>(args)...);
	}

	template <typename Interface>
	static size_t chained_size()
	{
		typedef typename Interface::Implementation Implementation;
		return sizeof(Implementation);
	}

	// helper to access the implementation for the interface
	// use:
	//	p(this)->doSth();
	template <typename Interface>
	static typename Interface::Implementation* p(Interface* interface)
	{
		typedef typename Interface::Implementation Implementation;
		auto ptr = reinterpret_cast<uint8_t*>(interface);
		auto offset = chained_getImplementationOffset<Interface>();
		return reinterpret_cast<Implementation*>(ptr + offset);
	}

	template <typename Interface>
	static const typename Interface::Implementation* p(const Interface* interface)
	{
		return p(const_cast<Interface*>(interface));
	}

private:
	template<typename Interface>
	struct ChainedWrapper : public Interface
	{
		template<typename... Args>
		ChainedWrapper(Args&&... args)
			: Interface(std::forward<Args>(args)...)
		{}

		~ChainedWrapper()
		{
			Interface::deleteImplementation();
		}
	};

	/*
	 * helper to allocate shared pointers
	 */
	template <typename Interface, typename BaseInterface = Interface>
	struct ChainedAllocator : public std::allocator< Interface >
	{
		typedef std::allocator< Interface > Base;

		ChainedAllocator() {}

		template<typename Other>
		ChainedAllocator(const Other&) {}

		Interface* allocate(std::size_t n)
		{
			auto size = n * (sizeof(Interface) + BaseInterface::ImplementationSize());
			auto ptr = new uint8_t[size];
			return reinterpret_cast<Interface*>(ptr);
		}
		void deallocate(Interface* p, std::size_t)
		{
			uint8_t* ptr = reinterpret_cast<uint8_t*>(p);
			delete[] ptr;
		}

		template <typename U>
		struct rebind {
			typedef ChainedAllocator<U, BaseInterface> other;
		};
	};

	// helper to allocate the right amount of bytes
	template <typename Interface>
	static uint8_t* chained_allocate()
	{
		auto size = sizeof(Interface) + Interface::ImplementationSize();
		return new uint8_t[size];
	}

	template <typename Interface>
	static size_t chained_getImplementationOffset()
	{
		typedef typename Interface::Implementation Implementation;
		auto allImplementationSizes = Interface::ImplementationSize();
		auto myImplementationSize = sizeof(Implementation);
		return sizeof(Interface) + allImplementationSizes - myImplementationSize;
	}
};

} // namespace ChainedPimpl
