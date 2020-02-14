
#pragma once

#include "global/types.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Image Color Swizzle
		//

		struct ImageSwizzle
		{
			// variables
		private:
			uint	_value = 0x4321;	// 0 - unknown, 1 - R, 2 - G, 3 - B, 4 - A, 5 - O, 6 - 1, example: RGB0 - 0x1235


		// methods
		public:
			constexpr ImageSwizzle ()
			{}

			explicit constexpr ImageSwizzle (const loo::math::uint4 &comp) : _value{ 0 }
			{
				ASSERT (comp.x < 7 && comp.y < 7 && comp.z < 7 && comp.w < 7);

				_value |= (comp.x & 0xF);
				_value |= (comp.y & 0xF) << 4;
				_value |= (comp.z & 0xF) << 8;
				_value |= (comp.w & 0xF) << 12;
			}

			ND_ constexpr uint Get () const
			{
				return _value;
			}

			ND_ constexpr loo::math::uint4 ToVec () const
			{
				return loo::math::uint4 (_value & 0xF, (_value >> 4) & 0xF, (_value >> 8) & 0xF, (_value >> 12) & 0xF);
			}

			ND_ constexpr bool IsDefault () const
			{
				return _value == ImageSwizzle ().Get ();
			}

			ND_ constexpr bool operator == (const ImageSwizzle &rhs) const { return _value == rhs._value; }
			ND_ constexpr bool operator >  (const ImageSwizzle &rhs) const { return _value > rhs._value; }


			friend constexpr ImageSwizzle  operator "" _swizzle (const char *str, const size_t len);


		private:
			static constexpr uint _CharToValue (char c)
			{
				return	c == 'r' or c == 'R' ? 1 :
					c == 'g' or c == 'G' ? 2 :
					c == 'b' or c == 'B' ? 3 :
					c == 'a' or c == 'A' ? 4 :
					c == '0' ? 5 :
					c == '1' ? 6 : 0;
			}
		};


		ND_ constexpr ImageSwizzle  operator "" _swizzle (const char *str, const size_t len)
		{
			ASSERT (len > 0 and len <= 4);

			ImageSwizzle	res;
			res._value = 0;

			for (size_t i = 0; i < len; ++i)
			{
				const char	c = str[i];
				const uint	v = ImageSwizzle::_CharToValue (c);

				ASSERT (v != 0);	// 'c' must be R, G, B, A, 0, 1
				res._value |= (v << i * 4);
			}
			return res;
		}

	}
}


namespace std
{
	template <>
	struct hash< loo::vkfg::ImageSwizzle >
	{
		ND_ size_t  operator () (const loo::vkfg::ImageSwizzle &value) const
		{
			return size_t (loo::HashOf (value.Get () == 0 ? loo::vkfg::ImageSwizzle ().Get () : value.Get ()));
		}
	};

}	// std
