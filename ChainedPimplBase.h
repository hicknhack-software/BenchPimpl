#pragma once
#include <stdint.h>
#include <memory>
#include <cassert>

namespace ChainedPimpl
{

template<typename Tag>
class VirtualBase
{
protected:
	virtual ~VirtualBase() {}
	virtual void destruct_implementation() {}
	size_t implementation_size();
};

template<typename Tag>
class PlainBase
{
protected:
	~PlainBase() {}
	void destruct_implementation() {}
	size_t implementation_size();
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
template<typename Tag, template<typename> class BaseClass = PlainBase>
class Base : protected BaseClass<Tag>
{
protected:
	typedef Base<Tag, BaseClass> ChainedBase;

	~Base() {}

	class chained
	{
		template<typename Interface>
		struct Trait
		{
			typedef typename Interface::Implementation Implementation;

			static size_t implementation_offset()
			{
				auto allImplementationSizes = Interface::implementation_size();
				auto myImplementationSize = sizeof(Implementation);
				return sizeof(Interface) + allImplementationSizes - myImplementationSize;
			}

			static Interface* interface(void* implementation_ptr)
			{
				auto ptr = reinterpret_cast<uint8_t*>(implementation_ptr);
				return reinterpret_cast<Interface*>(ptr - implementation_offset());
			}

			static Implementation* implementation(Interface* interface)
			{
				auto ptr = reinterpret_cast<uint8_t*>(interface);
				return reinterpret_cast<Implementation*>(ptr + implementation_offset());
			}

			static void destruct_implementation(Interface* interface)
			{
				p(interface)->~Implementation();
			}
			struct Wrapper : public Interface
			{
				template<typename... Args>
				Wrapper(Args&&... args)
					: Interface(std::forward<Args>(args)...)
				{}

				~Wrapper()
				{
					Interface::destruct_implementation();
				}
			};

			static void destruct(Interface* interface)
			{
				interface->destruct_implementation();
				interface->~Interface();
			}
			struct Deleter
			{
				void operator()(Interface* interface)
				{
					destruct(interface);
				}
			};
			typedef std::unique_ptr<Interface, Deleter> unique_ptr;

			typedef std::shared_ptr<Interface> shared_ptr;

			template <typename... Args>
			static shared_ptr make_shared(Args&&... args)
			{
				auto alloc = Allocator<Interface>();
				return std::allocate_shared<Wrapper>(alloc, std::forward<Args>(args)...);
			}

			template<typename T = Interface>
			static uint8_t* allocate()
			{
				auto size = sizeof(T) + Interface::implementation_size();
				return new uint8_t[size];
			}

			template<typename T>
			static void deallocate(T* p)
			{
				uint8_t* ptr = reinterpret_cast<uint8_t*>(p);
				delete[] ptr;
			}

			template <typename T>
			struct Allocator : public std::allocator<T>
			{
				Allocator() {}

				template<typename Other>
				Allocator(const Other&) {}

				typename std::allocator<T>::pointer allocate(std::size_t n)
				{
					assert(n == 1);
					auto ptr = Trait::allocate<T>();
					return reinterpret_cast<T*>(ptr);
				}
				void deallocate(typename std::allocator<T>::pointer p, std::size_t n)
				{
					assert(n == 1);
					Trait::deallocate(p);
				}

				template <typename U>
				struct rebind {
					typedef Allocator<U> other;
				};
			};
		};

	public:
		template<typename Interface>
		struct Implementation
		{
			Interface* i()
			{
				return Trait<Interface>::interface(this);
			}

			const Interface* i() const
			{
				return const_cast<Implementation*>(this)->i();
			}
		};

		template <typename Interface>
		static typename Interface::Implementation* p(Interface* interface)
		{
			return Trait<Interface>::implementation(interface);
		}

		template <typename Interface>
		static void destruct_implementation(Interface* interface)
		{
			Trait<Interface>::destruct_implementation(interface);
		}

		template <typename Interface, typename Base>
		static void destruct_implementation(Interface* interface, Base* base)
		{
			Trait<Interface>::destruct_implementation(interface);
			base->destruct_implementation();
		}

		template <typename Interface, typename... Args>
		static Interface* create(Args&&... args)
		{
			return new (Trait<Interface>::allocate()) Interface(std::forward<Args>(args)...);
		}

		// Interface has to be the same as for chained_create
		template <typename Interface>
		static void free(Interface* interface)
		{
			Trait<Interface>::destruct(interface);
			Trait<Interface>::deallocate(interface);
		}

		template <typename Interface, typename... Args>
		static typename Trait<Interface>::unique_ptr make_unique(Args&&... args)
		{
			return create<Interface>(std::forward<Args>(args)...);
		}

		template <typename Interface, typename... Args>
		static std::shared_ptr<Interface> make_shared(Args&&... args)
		{
			return Trait<Interface>::make_shared(std::forward<Args>(args)...);
		}

		template <typename Interface>
		static size_t implementation_size()
		{
			return sizeof(typename Interface::Implementation);
		}
	};

	// helper to access the implementation for the interface
	// use:
	//	p(this)->doSth();
	template <typename Interface>
	static auto p(Interface* interface) -> decltype(chained::p(interface))
	{
		return chained::p(interface);
	}

	template <typename Interface>
	static auto p(const Interface* interface) -> const decltype(chained::p(interface))
	{
		return p(const_cast<Interface*>(interface));
	}
};

} // namespace ChainedPimpl
