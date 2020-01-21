
#pragma once 
#include <type_traits>
#include "global/global.h"
template< class T >
static inline void ZeroVulkanStruct (T& Struct, VkStructureType Type)
{
	static_assert(!std::is_pointer<T>::value, "Don't use a pointer!");
	static_assert(STRUCT_OFFSET (T, sType) == 0, "Assumes sType is the first member in the Vulkan type!");
	Struct.sType = Type;
	memset (((loo::uint8*)&Struct) + sizeof (VkStructureType), 0, sizeof (T) - sizeof (VkStructureType));
}

void VerifyVulkanResult (VkResult Result, const loo::ANSICHAR* VkFunction, const loo::ANSICHAR* Filename, loo::uint32 Line);


#define VERIFYVULKANRESULT(VkFunction)				{ const VkResult ScopedResult = VkFunction; if (ScopedResult != VK_SUCCESS) { VerifyVulkanResult(ScopedResult, #VkFunction, __FILE__, __LINE__); }}
#define VERIFYVULKANRESULT_EXPANDED(VkFunction)		{ const VkResult ScopedResult = VkFunction; if (ScopedResult < VK_SUCCESS) { VerifyVulkanResult(ScopedResult, #VkFunction, __FILE__, __LINE__); }}
