
#pragma once
#include "global/global.h"
#include <atomic>

namespace loo
{

	//
	// Atomic Pointer
	//

	template <typename T>
	struct AtomicPtr
	{
		// variables
	private:
		alignas(LOO_CACHE_LINE) std::atomic< T *>	_ptr;


		// methods
	public:
		AtomicPtr () : _ptr{ null } {}
		AtomicPtr (T *ptr) : _ptr{ ptr } {}

		void  Store (T *ptr) { _ptr.store (ptr, memory_order_release); }
		ND_ T *   Load ()						const { return _ptr.load (memory_order_acquire); }

		AtomicPtr&	operator = (T *ptr) { Store (ptr);  return *this; }

		ND_ explicit operator T * () { return Load (); }

		ND_ bool  operator == (const T *rhs)	const { return Load () == rhs; }
		ND_ bool  operator != (const T *rhs)	const { return not (*this == rhs); }
	};



	//
	// Non-Atomic Ptr
	//

	template <typename T>
	struct NonAtomicPtr
	{
		// variables
	private:
		T *		_ptr;


		// methods
	public:
		NonAtomicPtr () : _ptr{ null } {}
		NonAtomicPtr (T *ptr) : _ptr{ ptr } {}

		void  Store (T *ptr) { _ptr = ptr; }
		ND_ T *   Load ()						const { return _ptr; }

		NonAtomicPtr&	operator = (T *ptr) { Store (ptr);  return *this; }

		ND_ explicit operator T * () { return Load (); }

		ND_ bool  operator == (const T *rhs)	const { return Load () == rhs; }
		ND_ bool  operator != (const T *rhs)	const { return not (*this == rhs); }
	};


}	// loo
