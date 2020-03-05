#pragma once
#include "global/global.h"
#include "global/extstd/typetraits.h"

namespace loo
{
	namespace math
	{

		/*
		=================================================
			CT_IntLog2
		=================================================
		*/
		namespace _math_hidden_
		{
			template <typename T, T X, uint Bit>
			struct _IntLog2 {
				static const int	value = int ((X >> Bit) != 0) + _IntLog2<T, X, Bit - 1 >::value;
			};

			template <typename T, T X>
			struct _IntLog2< T, X, 0 > {
				static const int	value = 0;
			};

		}	// _math_hidden_

		template <uint X>
		static constexpr int	CT_IntLog2 = (X ? _math_hidden_::_IntLog2< decltype(X), X, sizeof (X) * 8 - 1 >::value : -1);
		template <std::size_t X>
		static constexpr int	CT_Int64Log2 = (X ? _math_hidden_::_IntLog2< std::size_t, X, sizeof (X) * 8 - 1 >::value : -1);


		/*
		=================================================
			CT_Pow
		=================================================
		*/
		template <uint Power, typename T>
		inline constexpr T  CT_Pow (const T &base)
		{
			STATIC_ASSERT (IsInteger<T> and IsInteger<decltype(Power)> and Power >= 0, "");
			constexpr bool cb = Power == 0;
			if /*constexpr*/ (cb)
			{
				LOO_UNUSED (base);
				return 1;
			}
			else
				return CT_Pow<Power - 1> (base) * base;
		}


	}	

}