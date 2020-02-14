
#pragma once

#include "vkfg/fg/ids.h"

namespace loo
{
	namespace vkfg
	{

		using RawMemoryID = _hidden_::ResourceID<15>;
		using RawPipelineLayoutID = _hidden_::ResourceID<16>;
		using RawRenderPassID = _hidden_::ResourceID<17>;
		using RawFramebufferID = _hidden_::ResourceID<18>;
		//using DescriptorPoolID		= _hidden_::ResourceID<19>;

		using MemoryID = _hidden_::ResourceIDWrap< RawMemoryID >;
		using PipelineLayoutID = _hidden_::ResourceIDWrap< RawPipelineLayoutID >;
		using RenderPassID = _hidden_::ResourceIDWrap< RawRenderPassID >;
		using FramebufferID = _hidden_::ResourceIDWrap< RawFramebufferID >;
		using PipelineResourcesID = _hidden_::ResourceIDWrap< RawPipelineResourcesID >;
		using DescriptorSetLayoutID = _hidden_::ResourceIDWrap< RawDescriptorSetLayoutID >;


		class IFrameGraphTask
		{};

	}

}