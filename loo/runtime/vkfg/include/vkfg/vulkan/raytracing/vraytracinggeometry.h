
#pragma once
#include "vkfg/fg/raytracinggeometrydesc.h"
#include "vkfg/vulkan/vcommon.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Vulkan Ray Tracing Geometry immutable data
		//

		class VRayTracingGeometry final
		{
			// types
		public:
			using EFlags = ERayTracingGeometryFlags;

			struct Triangles
			{
				GeometryID			geometryId;
				EFlags				flags = Default;
				uint				maxVertexCount = 0;
				EVertexType			vertexFormat = Default;
				uint				maxIndexCount = 0;
				EIndex				indexType = Default;
				Bytes<uint16_t>		vertexSize;
				Bytes<uint16_t>		indexSize;

				Triangles () {}

				ND_ bool  operator <  (const Triangles &rhs)	const { return geometryId < rhs.geometryId; }
				ND_ bool  operator <  (const GeometryID &rhs)	const { return geometryId < rhs; }
				ND_ bool  operator == (const GeometryID &rhs)	const { return geometryId == rhs; }
			};

			struct AABB
			{
				GeometryID			geometryId;
				uint				maxAabbCount = 0;
				EFlags				flags = Default;

				AABB () {}

				ND_ bool  operator <  (const AABB &rhs)			const { return geometryId < rhs.geometryId; }
				ND_ bool  operator <  (const GeometryID &rhs)	const { return geometryId < rhs; }
				ND_ bool  operator == (const GeometryID &rhs)	const { return geometryId == rhs; }
			};


			// variables
		private:
			VkAccelerationStructureNV	_bottomLevelAS = VK_NULL_HANDLE;
			MemoryID					_memoryId;
			BLASHandle_t				_handle = BLASHandle_t (0);

			Array< Triangles >			_triangles;
			Array< AABB >				_aabbs;
			ERayTracingFlags			_flags = Default;

			DebugName_t					_debugName;

			mutable RWDataRaceCheck				_drCheck;


			// methods
		public:
			VRayTracingGeometry () {}
			~VRayTracingGeometry ();

			bool Create (VResourceManager &, const RayTracingGeometryDesc &desc, RawMemoryID memId, VMemoryObj &memObj, StringView dbgName);
			void Destroy (VResourceManager &);

			ND_ size_t  GetGeometryIndex (const GeometryID &id) const;

			ND_ BLASHandle_t				BLASHandle ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _handle; }
			ND_ VkAccelerationStructureNV	Handle ()				const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _bottomLevelAS; }

			ND_ ArrayView<Triangles>		GetTriangles ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _triangles; }
			ND_ ArrayView<AABB>				GetAABBs ()				const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _aabbs; }
			ND_ ERayTracingFlags			GetFlags ()				const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _flags; }

			ND_ StringView					GetDebugName ()			const { SHAREDLOCK (RWDataRaceCheck, _drCheck);  return _debugName; }
		};


	}
}