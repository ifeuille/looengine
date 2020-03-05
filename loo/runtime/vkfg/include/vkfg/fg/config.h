// Copyright (c) 2018-2019,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once
#include "global/global.h"

#ifndef LOO_OPTIMIZE_IDS
# ifdef LOO_DEBUG
#	define LOO_OPTIMIZE_IDS		false
# else
#	define LOO_OPTIMIZE_IDS		true
# endif
#endif

#ifndef LOO_ENABLE_VULKAN
#define LOO_ENABLE_VULKAN
#endif

namespace loo
{

# ifdef LOO_PLATFORM_ANDROID

	// buffer
	static constexpr unsigned	LOO_MaxVertexBuffers = 8;
	static constexpr unsigned	LOO_MaxVertexAttribs = 16;

	// render pass
	static constexpr unsigned	LOO_MaxColorBuffers = 4;
	static constexpr unsigned	LOO_MaxViewports = 1;

	// pipeline
	static constexpr bool		LOO_EnableShaderDebugging = false;
	static constexpr unsigned	LOO_MaxDescriptorSets = 4;
	static constexpr unsigned	LOO_MaxBufferDynamicOffsets = 12;	// 8 UBO + 4 SSBO
	static constexpr unsigned	LOO_MaxElementsInUnsizedDesc = 1;	// if used extension GL_EXT_nonuniform_qualifier

	// memory
	static constexpr unsigned	LOO_VkDevicePageSizeMb = 64;

# else

	// buffer
	static constexpr unsigned	LOO_MaxVertexBuffers = 8;
	static constexpr unsigned	LOO_MaxVertexAttribs = 16;

	// render pass
	static constexpr unsigned	LOO_MaxColorBuffers = 8;
	static constexpr unsigned	LOO_MaxViewports = 16;

	// pipeline
	static constexpr bool		LOO_EnableShaderDebugging = true;
	static constexpr unsigned	LOO_MaxDescriptorSets = 8;
	static constexpr unsigned	LOO_MaxBufferDynamicOffsets = 16;
	static constexpr unsigned	LOO_MaxElementsInUnsizedDesc = 64;	// if used extension GL_EXT_nonuniform_qualifier

	// memory
	static constexpr unsigned	LOO_VkDevicePageSizeMb = 256;

# endif


	// render pass
	static constexpr unsigned	LOO_MaxRenderPassSubpasses = 8;

	// pipeline
	static constexpr unsigned	LOO_MaxPushConstants = 8;
	static constexpr unsigned	LOO_MaxPushConstantsSize = 128;	// bytes
	static constexpr unsigned	LOO_MaxSpecConstants = 8;
	static constexpr unsigned	LOO_DebugDescriptorSet = LOO_MaxDescriptorSets - 1;

	// queue
	static constexpr unsigned	LOO_MaxQueueFamilies = 32;

	// task
	static constexpr unsigned	LOO_MaxTaskDependencies = 8;
	static constexpr unsigned	LOO_MaxCopyRegions = 8;
	static constexpr unsigned	LOO_MaxClearRanges = 8;
	static constexpr unsigned	LOO_MaxBlitRegions = 8;
	static constexpr unsigned	LOO_MaxResolveRegions = 8;


}	// LOO


// check definitions
#if defined (LOO_COMPILER_MSVC) 
//or defined (LOO_COMPILER_CLANG)
#  if LOO_OPTIMIZE_IDS
#	pragma detect_mismatch( "LOO_OPTIMIZE_IDS", "1" )
#  else
#	pragma detect_mismatch( "LOO_OPTIMIZE_IDS", "0" )
#  endif
#endif	// COMPILER_MSVC or COMPILER_CLANG
