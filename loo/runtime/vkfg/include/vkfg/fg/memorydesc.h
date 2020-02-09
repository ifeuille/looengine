#pragma once
#include "vkfg/fg/enums.h"
#include "vkfg/fg/ids.h"

namespace loo
{
	namespace vkfg
	{
		//
		// Memory Description
		//
		struct MemoryDesc
		{
			// variables
			EMemoryType		type = EMemoryType::Default;
			MemPoolID		poolId;


			// methods
			MemoryDesc () {}
			MemoryDesc (EMemoryType type) : type{ type } {}
			MemoryDesc (EMemoryType type, MemPoolID poolId) : type{ type }, poolId{ poolId } {}
		};
	}
}