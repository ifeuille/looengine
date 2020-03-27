
#pragma once
#include "global/extstd/memutils.h"

namespace loo
{
	/*
	=================================================
		Singleton
	=================================================
	*/
	template <typename T>
	ND_ inline static T*  Singleton ()
	{
		static T inst;
		return AddressOf (inst);
	}
}
