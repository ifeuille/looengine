
#include "vkfg/vulkan/raytracing/vlocalrtgeometry.h"
#include "vkfg/vulkan/utils/venumcast.h"
#include "vkfg/vulkan/commandbuffer/vtaskgraph.h"
#include "vkfg/vulkan/debugger/vlocaldebugger.h"
#include "vkfg/vulkan/commandbuffer/vbarriermanager.h"

namespace loo
{
	namespace vkfg
	{

		/*
		=================================================
			destructor
		=================================================
		*/
		VLocalRTGeometry::~VLocalRTGeometry ()
		{
			ASSERT (_rtGeometryData == null);
		}

		/*
		=================================================
			Create
		=================================================
		*/
		bool VLocalRTGeometry::Create (const VRayTracingGeometry *geometryData)
		{
			CHECK_ERR (_rtGeometryData == null);
			CHECK_ERR (geometryData);

			_rtGeometryData = geometryData;

			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VLocalRTGeometry::Destroy ()
		{
			_rtGeometryData = null;

			// check for uncommited barriers
			ASSERT (_pendingAccesses.empty ());
			ASSERT (_accessForReadWrite.empty ());

			_pendingAccesses = Default;
			_accessForReadWrite = Default;
		}

		/*
		=================================================
			AddPendingState
		=================================================
		*/
		void VLocalRTGeometry::AddPendingState (const GeometryState &gs) const
		{
			ASSERT (gs.task);

			_pendingAccesses.stages = EResourceState_ToPipelineStages (gs.state);
			_pendingAccesses.access = EResourceState_ToAccess (gs.state);
			_pendingAccesses.isReadable = EResourceState_IsReadable (gs.state);
			_pendingAccesses.isWritable = EResourceState_IsWritable (gs.state);
			_pendingAccesses.index = gs.task->ExecutionOrder ();
		}

		/*
		=================================================
			ResetState
		=================================================
		*/
		void VLocalRTGeometry::ResetState (ExeOrderIndex index, VBarrierManager &barrierMngr, Ptr<VLocalDebugger> debugger) const
		{
			ASSERT (_pendingAccesses.empty ());	// you must commit all pending states before reseting

			// add full range barrier
			_pendingAccesses.isReadable = true;
			_pendingAccesses.isWritable = false;
			_pendingAccesses.stages = 0;
			_pendingAccesses.access = 0;
			_pendingAccesses.index = index;

			CommitBarrier (barrierMngr, debugger);

			// flush
			_accessForReadWrite = Default;
		}

		/*
		=================================================
			CommitBarrier
		=================================================
		*/
		void VLocalRTGeometry::CommitBarrier (VBarrierManager &barrierMngr, Ptr<VLocalDebugger> debugger) const
		{
			const bool	is_modified = (_accessForReadWrite.isReadable and _pendingAccesses.isWritable) or	// read -> write
				_accessForReadWrite.isWritable;										// write -> read/write

			if (is_modified)
			{
				VkMemoryBarrier		barrier = {};
				barrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
				barrier.srcAccessMask = _accessForReadWrite.access;
				barrier.dstAccessMask = _pendingAccesses.access;
				barrierMngr.AddMemoryBarrier (_accessForReadWrite.stages, _pendingAccesses.stages, barrier);

				if (debugger) {
					debugger->AddRayTracingBarrier (_rtGeometryData.get (), _accessForReadWrite.index, _pendingAccesses.index,
						_accessForReadWrite.stages, _pendingAccesses.stages, 0, barrier);
				}
				_accessForReadWrite = _pendingAccesses;
			}
			else
			{
				_accessForReadWrite.stages |= _pendingAccesses.stages;
				_accessForReadWrite.access = _pendingAccesses.access;
				_accessForReadWrite.index = _pendingAccesses.index;
				_accessForReadWrite.isReadable |= _pendingAccesses.isReadable;
				_accessForReadWrite.isWritable |= _pendingAccesses.isWritable;
			}

			_pendingAccesses = Default;
		}


	}
}