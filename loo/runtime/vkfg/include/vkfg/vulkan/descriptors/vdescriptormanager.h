
#pragma once

#include "vkfg/vulkan/descriptors/vdescriptorsetlayout.h"
namespace loo
{

	namespace vkfg
	{

		//
		// Vulkan Descriptor Manager
		//

		class VDescriptorManager final
		{
			// types
		private:
			static constexpr uint	MaxDescriptorPoolSize = 1u << 11;
			static constexpr uint	MaxDescriptorSets = 1u << 10;

			struct DSPool
			{
				//SpinLock			guard;
				VkDescriptorPool	pool = VK_NULL_HANDLE;
			};

			using DescriptorPoolArray_t = FixedArray< DSPool, 8 >;
			using DescriptorSet = VDescriptorSetLayout::DescriptorSet;


			// variables
		private:
			VDevice const&				_device;

			std::mutex					_guard;
			DescriptorPoolArray_t		_descriptorPools;


			// methods
		public:
			explicit VDescriptorManager (const VDevice &);
			~VDescriptorManager ();

			bool Initialize ();
			void Deinitialize ();

			bool AllocDescriptorSet (VkDescriptorSetLayout layout, OUT DescriptorSet &ds);
			bool DeallocDescriptorSet (const DescriptorSet &ds);
			bool DeallocDescriptorSets (ArrayView<DescriptorSet> ds);

		private:
			bool _CreateDescriptorPool ();
		};


	}	
}