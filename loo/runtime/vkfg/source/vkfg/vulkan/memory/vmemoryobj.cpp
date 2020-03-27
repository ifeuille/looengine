
#include "vkfg/vulkan/memory/vmemoryobj.h"
#include "vkfg/vulkan/memory/vmemorymanager.h"
#include "vkfg/vulkan/instance/vresourcemanager.h"


namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			destructor
		=================================================
		*/
		VMemoryObj::~VMemoryObj ()
		{
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VMemoryObj::Create (const MemoryDesc &desc, StringView dbgName)
		{
			EXLOCK (RWDataRaceCheck,_drCheck);

			_desc = desc;
			_debugName = dbgName;

			return true;
		}

		/*
		=================================================
			AllocateForBuffer
		=================================================
		*/
		bool VMemoryObj::AllocateForBuffer (VMemoryManager &memMngr, VkBuffer buf)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			CHECK_ERR (memMngr.AllocateForBuffer (buf, _desc, INOUT _storage));
			return true;
		}

		/*
		=================================================
			AllocateForImage
		=================================================
		*/
		bool VMemoryObj::AllocateForImage (VMemoryManager &memMngr, VkImage img)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			CHECK_ERR (memMngr.AllocateForImage (img, _desc, INOUT _storage));
			return true;
		}

		/*
		=================================================
			AllocateForAccelStruct
		=================================================
		*/
		bool VMemoryObj::AllocateForAccelStruct (VMemoryManager &memMngr, VkAccelerationStructureNV accelStruct)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			CHECK_ERR (memMngr.AllocateForAccelStruct (accelStruct, _desc, INOUT _storage));
			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VMemoryObj::Destroy (VResourceManager &resMngr)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			resMngr.GetMemoryManager ().Deallocate (INOUT _storage);

			_debugName.clear ();
		}

		/*
		=================================================
			GetInfo
		=================================================
		*/
		bool VMemoryObj::GetInfo (VMemoryManager &memMngr, OUT MemoryInfo &info) const
		{
			SHAREDLOCK (RWDataRaceCheck, _drCheck);

			return memMngr.GetMemoryInfo (_storage, OUT info);
		}


	}
}