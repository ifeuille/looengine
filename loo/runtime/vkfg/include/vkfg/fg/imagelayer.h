
#pragma once

#include "global/types.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Image Array Layer
		//

		struct ImageLayer
		{
			// variables
		private:
			uint		_value = 0;


			// methods
		public:
			constexpr ImageLayer () {}
			explicit constexpr ImageLayer (uint value) : _value (value) {}

			ND_ constexpr uint	Get ()								const { return _value; }

			ND_ ImageLayer		operator + (const ImageLayer &rhs)	const { return ImageLayer{ Get () + rhs.Get () }; }

			ND_ constexpr bool	operator == (const ImageLayer &rhs) const { return _value == rhs._value; }
			ND_ constexpr bool	operator != (const ImageLayer &rhs) const { return _value != rhs._value; }
			ND_ constexpr bool	operator >  (const ImageLayer &rhs) const { return _value > rhs._value; }
			ND_ constexpr bool	operator <  (const ImageLayer &rhs) const { return _value < rhs._value; }
			ND_ constexpr bool	operator >= (const ImageLayer &rhs) const { return _value >= rhs._value; }
			ND_ constexpr bool	operator <= (const ImageLayer &rhs) const { return _value <= rhs._value; }
		};


		ND_ inline constexpr ImageLayer operator "" _layer (unsigned long long value) { return ImageLayer (uint (value)); }


	}	// FG
}


namespace std
{
	template <>
	struct hash< loo::vkfg::ImageLayer >
	{
		ND_ size_t  operator () (const loo::vkfg::ImageLayer &value) const
		{
			return size_t (loo::HashOf (value.Get ()));
		}
	};

}	// std
