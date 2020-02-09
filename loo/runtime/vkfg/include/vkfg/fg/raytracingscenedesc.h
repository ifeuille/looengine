#pragma once
#include "vkfg/fg/ids.h"
#include "vkfg/fg/enums.h"
#include "global/math/matrix.h"
namespace loo
{
	namespace vkfg
	{
		//
		// Ray Tracing Scene Description
		//
		struct RayTracingSceneDesc
		{
			uint maxInstanceCount = 0;
			ERayTracingFlags flags = Default;

			RayTracingSceneDesc () {}
			explicit RayTracingSceneDesc (uint instanceCount,ERayTracingFlags flags_ = Default)
				:maxInstanceCount(instanceCount),flags(flags_)
			{}
		};
	}
}