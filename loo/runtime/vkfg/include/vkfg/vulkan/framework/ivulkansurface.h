#pragma once
#include "vkfg/dllexport.h"
#include "global/types.h"
#include "global/math/vec.h"
#include "global/extstd/fixedarray.h"
#include "global/extstd/ntstringview.h"
#include "vulkanloader/VulkanLoader.h"
#include "vulkanloader/VulkanCheckError.h"

namespace loo
{
	namespace vkfg
	{
		//
		// Vulkan Surface interface
		//
		class /*LOOVKFG_EXPORT*/ IVulkanSurface
		{
		public:
			virtual ~IVulkanSurface () {}
			ND_ virtual ArrayView<const char*>	GetRequiredExtensions () const = 0;
			ND_ virtual VkSurfaceKHR			Create (VkInstance inst) const = 0;
		};

	}
}