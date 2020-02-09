/*
	UMax constant is maximum value of unsigned integer type.
*/

#pragma once
#include "global/config.h"
#include "global/Compiler.h"
#include "global/platform.h"


namespace loo
{
	namespace _hidden_
	{
		struct _UMax
		{
			template <typename T>
			ND_ constexpr operator const T () const
			{
				STATIC_ASSERT (T (~T (0)) > T (0), "");
				return T (~T (0));
			}

			template <typename T>
			ND_ friend constexpr bool operator == (const T& left, const _UMax &right)
			{
				return T (right) == left;
			}

			template <typename T>
			ND_ friend constexpr bool operator != (const T& left, const _UMax &right)
			{
				return T (right) != left;
			}
		};

	}	//_hidden_


	static constexpr _hidden_::_UMax		UMax{};

}
