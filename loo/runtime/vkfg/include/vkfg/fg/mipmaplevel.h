
#pragma once

#include "global/types.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Mipmap Level
		//

		struct MipmapLevel
		{
			// variables
		private:
			uint		_value;


			// methods
		public:
			constexpr MipmapLevel () : _value (0) {}

			explicit constexpr MipmapLevel (uint value) : _value (value) {}

			ND_ constexpr uint	Get ()								 const { return _value; }

			ND_ constexpr bool	operator == (const MipmapLevel &rhs) const { return _value == rhs._value; }
			ND_ constexpr bool	operator != (const MipmapLevel &rhs) const { return _value != rhs._value; }
			ND_ constexpr bool	operator >  (const MipmapLevel &rhs) const { return _value > rhs._value; }
			ND_ constexpr bool	operator <  (const MipmapLevel &rhs) const { return _value < rhs._value; }
			ND_ constexpr bool	operator >= (const MipmapLevel &rhs) const { return _value >= rhs._value; }
			ND_ constexpr bool	operator <= (const MipmapLevel &rhs) const { return _value <= rhs._value; }
		};


		ND_ inline constexpr MipmapLevel operator "" _mipmap (unsigned long long value) { return MipmapLevel (uint (value)); }


	}	// 
}


namespace std
{
	template <>
	struct hash< loo::vkfg::MipmapLevel >
	{
		ND_ size_t  operator () (const loo::vkfg::MipmapLevel &value) const
		{
			return size_t (loo::HashOf (value.Get ()));
		}
	};

}	// std
