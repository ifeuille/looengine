
#pragma once
#include "vkfg/vulkan/commandbuffer/vtaskgraph.h"


namespace loo
{
	namespace vkfg
	{

		//
		// Dummy Task
		//
		class VFgDummyTask final : public VFrameGraphTask
		{
		};


		inline Array<UniquePtr<VFgDummyTask>>  GenDummyTasks (size_t count)
		{
			Array<UniquePtr<VFgDummyTask>>	result;		result.reserve (count);

			for (size_t i = 0; i < count; ++i)
			{
				UniquePtr<VFgDummyTask>		task{ new VFgDummyTask () };

				task->SetExecutionOrder (ExeOrderIndex (size_t (ExeOrderIndex::First) + i));

				result.push_back (std::move (task));
			}

			return result;
		}

	}
}