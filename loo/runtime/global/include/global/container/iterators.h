#pragma once
//#include "global/global.h"
#include <xutility>

namespace loo
{
	namespace _hidden_
	{
		template <typename T>
		struct _ReverseWrapper
		{
			T &		container;

			ND_ auto	begin () { return std::rbegin (container); }
			ND_ auto	end () { return std::rend (container); }
		};

	}	// _hidden_

	/*
	=================================================
		Reverse
	=================================================
	*/
	template <typename Container>
	ND_ _hidden_::_ReverseWrapper<Container>  Reverse (Container &&arr)
	{
		return { arr };
	}
}


