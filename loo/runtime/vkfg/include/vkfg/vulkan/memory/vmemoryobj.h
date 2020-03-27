#pragma once

#include "global/container/untypedstorage.h"
#include "vkfg/fg/memorydesc.h"
#include "vkfg/vulkan/vcommon.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Memory Object
		//
		class VMemoryObj final
		{
			// types
		public:
			using Storage_t = UntypedStorage< sizeof (uint64_t) * 4, alignof(uint64_t) >;

			struct MemoryInfo
			{
				VkDeviceMemory			mem = VK_NULL_HANDLE;
				VkMemoryPropertyFlags	flags = 0;
				BytesU					offset;
				BytesU					size;
				void *					mappedPtr = null;
			};


			// variables
		private:
			Storage_t				_storage;
			MemoryDesc				_desc;
			DebugName_t				_debugName;

			mutable RWDataRaceCheck			_drCheck;


			// methods
		public:
			VMemoryObj () {}
			VMemoryObj (VMemoryObj &&) = default;
			~VMemoryObj ();

			bool Create (const MemoryDesc &, StringView dbgName);
			void Destroy (VResourceManager &);

			bool AllocateForImage (VMemoryManager &, VkImage);
			bool AllocateForBuffer (VMemoryManager &, VkBuffer);
			bool AllocateForAccelStruct (VMemoryManager &, VkAccelerationStructureNV);

			bool GetInfo (VMemoryManager &, OUT MemoryInfo &) const;

			//ND_ MemoryDesc const&	Description ()	const	{ SHAREDLOCK(RWDataRaceCheck,  _drCheck );  return _desc; }
			ND_ EMemoryTypeExt	MemoryType ()		const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return EMemoryTypeExt (_desc.type); }
		};


	}
}