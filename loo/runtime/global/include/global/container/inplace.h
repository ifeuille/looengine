#pragma once

#include "global/extstd/memutils.h"

namespace loo
{

	//
	// In Place Storage
	//

	template <typename T>
	struct InPlace final
	{
		// types
	public:
		using Self = InPlace< T >;
		using Value_t = T;


		// variables
	private:
		union {
			T			_value;
			uint8_t		_data[sizeof (T)];	// don't use it!
		};
		DEBUG_ONLY (
			bool		_isCreated = false;
		)


			// methods
	public:
		InPlace ()
		{}

		~InPlace ()
		{
			DEBUG_ONLY(ASSERT (not _isCreated);)
		}

		template <typename ...Args>
		Self&  Create (Args&& ...args)
		{
			DEBUG_ONLY (
				ASSERT (not _isCreated);
			_isCreated = true;
			)
				PlacementNew<T> (&_value, std::forward<Args &&> (args)...);
			return *this;
		}

		void Destroy ()
		{
			DEBUG_ONLY (
				ASSERT (_isCreated);
			_isCreated = false;
			)
				_value.~T ();
		}

		ND_ T *			operator -> () { DEBUG_ONLY(ASSERT (_isCreated); ) return &_value; }
		ND_ T const*	operator -> ()	const { DEBUG_ONLY( ASSERT (_isCreated);)  return &_value; }

		ND_ T &			operator * () { DEBUG_ONLY (ASSERT (_isCreated);)  return _value; }
		ND_ T const&	operator * ()	const { DEBUG_ONLY (ASSERT (_isCreated);)  return _value; }

		DEBUG_ONLY (
			ND_ bool	IsCreated ()	const { return _isCreated; }
		)
	};


}
