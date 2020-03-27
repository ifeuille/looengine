#pragma once
#include "global/types.h"
#include "vkfg/fg/config.h"

#include <chrono>
#include <atomic>

namespace loo
{
	namespace vkfg
	{
		using PipelineCompiler = SharedPtr<class IPipelineCompiler>;
		using FrameGraph = SharedPtr< class IFrameGraph >;

		using Task = Ptr< class IFrameGraphTask >;

		using Nanoseconds = std::chrono::nanoseconds;

	}
}