
#pragma once


#include "vkfg/fg/enums.h"
#include "vkfg/vulkan/raytracing/vraytracinggeometry.h"


namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Ray Tracing Geometry thread local
		//

		class VLocalRTGeometry final
		{
			// types
		public:
			struct GeometryState
			{
				EResourceState	state;
				VTask			task;
			};

			using Triangles = VRayTracingGeometry::Triangles;
			using AABB = VRayTracingGeometry::AABB;

		private:
			struct GeometryAccess
			{
				VkPipelineStageFlags	stages = 0;
				VkAccessFlags			access = 0;
				ExeOrderIndex			index = ExeOrderIndex::Initial;
				bool					isReadable : 1;
				bool					isWritable : 1;

				GeometryAccess () : isReadable{ false }, isWritable{ false } {}

				ND_ bool empty ()	const { return not (isReadable or isWritable); }
			};


			// variables
		private:
			Ptr<VRayTracingGeometry const>	_rtGeometryData;		// readonly access is thread safe

			mutable GeometryAccess			_pendingAccesses;
			mutable GeometryAccess			_accessForReadWrite;


			// methods
		public:
			VLocalRTGeometry () {}
			VLocalRTGeometry (VLocalRTGeometry &&) = delete;
			~VLocalRTGeometry ();

			bool Create (const VRayTracingGeometry *);
			void Destroy ();

			void AddPendingState (const GeometryState &state) const;
			void CommitBarrier (VBarrierManager &barrierMngr, Ptr<VLocalDebugger> debugger) const;
			void ResetState (ExeOrderIndex index, VBarrierManager &barrierMngr, Ptr<VLocalDebugger> debugger) const;

			ND_ BLASHandle_t				BLASHandle ()		const { return _rtGeometryData->BLASHandle (); }
			ND_ VkAccelerationStructureNV	Handle ()			const { return _rtGeometryData->Handle (); }

			ND_ ArrayView<Triangles>		GetTriangles ()		const { return _rtGeometryData->GetTriangles (); }
			ND_ ArrayView<AABB>				GetAABBs ()			const { return _rtGeometryData->GetAABBs (); }
			ND_ uint						MaxGeometryCount ()	const { return uint (GetTriangles ().size () + GetAABBs ().size ()); }
			ND_ ERayTracingFlags			GetFlags ()			const { return _rtGeometryData->GetFlags (); }

			ND_ VRayTracingGeometry const*	ToGlobal ()			const { return _rtGeometryData.get (); }
		};


	}	
}