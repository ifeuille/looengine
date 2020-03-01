
#pragma once

#include "vkfg/vulkan/commandbuffer/vcmdbatch.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Submitted Batches
		//

		class VSubmitted final
		{
			friend class VFrameGraph;

			// types
		public:
			static constexpr uint	MaxBatches = 32;
			static constexpr uint	MaxSemaphores = 8;

			using Batches_t = FixedArray< VCmdBatchPtr, MaxBatches >;
			using Semaphores_t = FixedArray< VkSemaphore, MaxSemaphores >;
			using Statistic_t = IFrameGraph::Statistics;


			// variables
		private:
			const uint			_indexInPool;
			Batches_t			_batches;
			Semaphores_t		_semaphores;
			VkFence				_fence;
			EQueueType			_queueType;

			mutable RWDataRaceCheck		_drCheck;


			// methods
		public:
			explicit VSubmitted (uint indexInPool);
			~VSubmitted ();

			ND_ VkFence		GetFence ()			const { EXLOCK (RWDataRaceCheck, _drCheck);  return _fence; }
			ND_ EQueueType	GetQueueType ()		const { EXLOCK (RWDataRaceCheck, _drCheck);  return _queueType; }
			ND_ uint		GetIndexInPool ()	const { return _indexInPool; }


		private:
			void _Initialize (const VDevice &, EQueueType queue, ArrayView<VCmdBatchPtr>, ArrayView<VkSemaphore>);
			void _Release (const VDevice &, VDebugger &, const IFrameGraph::ShaderDebugCallback_t &, INOUT Statistic_t &);
			void _Destroy (const VDevice &);
		};


	}
}