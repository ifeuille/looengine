
#include "vkfg/vulkan/raytracing/vraytracinggeometry.h"
#include "vkfg/vulkan/instance/vdevice.h"
#include "vkfg/vulkan/memory/vmemoryobj.h"
#include "vkfg/vulkan/utils/venumcast.h"
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
		VRayTracingGeometry::~VRayTracingGeometry ()
		{
			ASSERT (not _bottomLevelAS);
		}

		/*
		=================================================
			CopyAndSortGeometry
		=================================================
		*/
		static void CopyAndSortGeometry (const RayTracingGeometryDesc &desc,
			OUT Array<VRayTracingGeometry::Triangles> &outTriangles,
			OUT Array<VRayTracingGeometry::AABB> &outAabbs)
		{
			outTriangles.resize (desc.triangles.size ());
			outAabbs.resize (desc.aabbs.size ());

			// add triangles
			for (size_t i = 0; i < desc.triangles.size (); ++i)
			{
				auto&	src = desc.triangles[i];
				auto&	dst = outTriangles[i];

				ASSERT (src.vertexCount > 0);
				ASSERT (src.geometryId.IsDefined ());

				dst.geometryId = src.geometryId;
				dst.vertexSize = Bytes<uint16_t>{ EVertexType_SizeOf (src.vertexFormat) };
				dst.indexSize = Bytes<uint16_t>{ EIndex_SizeOf (src.indexType) };
				dst.maxVertexCount = src.vertexCount;
				dst.maxIndexCount = src.indexCount;
				dst.vertexFormat = src.vertexFormat;
				dst.indexType = src.indexType;
				dst.flags = src.flags;
			}

			// add AABBs
			for (size_t i = 0; i < desc.aabbs.size (); ++i)
			{
				auto&	src = desc.aabbs[i];
				auto&	dst = outAabbs[i];

				ASSERT (src.aabbCount > 0);
				ASSERT (src.geometryId.IsDefined ());

				dst.geometryId = src.geometryId;
				dst.maxAabbCount = src.aabbCount;
				dst.flags = src.flags;
			}

			std::sort (outTriangles.begin (), outTriangles.end ());
			std::sort (outAabbs.begin (), outAabbs.end ());
		}

		/*
		=================================================
			Create
		----
			from specs: "Acceleration structure creation uses the count and type information from the geometries"
		=================================================
		*/
		bool VRayTracingGeometry::Create (VResourceManager &resMngr, const RayTracingGeometryDesc &desc, RawMemoryID memId, VMemoryObj &memObj, StringView dbgName)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);
			CHECK_ERR (_bottomLevelAS == VK_NULL_HANDLE);
			CHECK_ERR (not _memoryId);
			CHECK_ERR (desc.triangles.size () or desc.aabbs.size ());

			auto&	dev = resMngr.GetDevice ();
			ASSERT ((desc.triangles.size () + desc.aabbs.size ()) <= dev.GetDeviceRayTracingProperties ().maxGeometryCount);

			CopyAndSortGeometry (desc, OUT _triangles, OUT _aabbs);

			Array<VkGeometryNV>		geometries;
			geometries.resize (_triangles.size () + _aabbs.size ());

			// add triangles
			for (size_t i = 0; i < _triangles.size (); ++i)
			{
				auto&	src = _triangles[i];
				auto&	dst = geometries[i];

				dst = {};
				dst.sType = VK_STRUCTURE_TYPE_GEOMETRY_NV;
				dst.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_NV;
				dst.flags = VEnumCast (src.flags);
				dst.geometry.aabbs.sType = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
				dst.geometry.triangles.sType = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
				dst.geometry.triangles.vertexCount = src.maxVertexCount;
				dst.geometry.triangles.vertexFormat = VEnumCast (src.vertexFormat);

				if (src.maxIndexCount > 0)
				{
					dst.geometry.triangles.indexCount = src.maxIndexCount;
					dst.geometry.triangles.indexType = VEnumCast (src.indexType);
				}
				else
				{
					ASSERT (src.indexType == EIndex::Unknown);
					dst.geometry.triangles.indexType = VK_INDEX_TYPE_NONE_NV;
				}
			}

			// add AABBs
			for (size_t i = 0; i < _aabbs.size (); ++i)
			{
				auto&	src = _aabbs[i];
				auto&	dst = geometries[i + _triangles.size ()];

				dst = {};
				dst.sType = VK_STRUCTURE_TYPE_GEOMETRY_NV;
				dst.geometryType = VK_GEOMETRY_TYPE_AABBS_NV;
				dst.flags = VEnumCast (src.flags);
				dst.geometry.triangles.sType = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
				dst.geometry.aabbs.sType = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
				dst.geometry.aabbs.numAABBs = src.maxAabbCount;
			}

			VkAccelerationStructureCreateInfoNV		info = {};
			info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
			info.info.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
			info.info.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV;
			info.info.geometryCount = uint (geometries.size ());
			info.info.pGeometries = geometries.data ();
			info.info.flags = VEnumCast (desc.flags);

			VK_CHECK (dev.vkCreateAccelerationStructureNV (dev.GetVkDevice (), &info, null, OUT &_bottomLevelAS));

			CHECK_ERR (memObj.AllocateForAccelStruct (resMngr.GetMemoryManager (), _bottomLevelAS));

			uint64_t	as_handle;
			VK_CHECK (dev.vkGetAccelerationStructureHandleNV (dev.GetVkDevice (), _bottomLevelAS, sizeof (as_handle), OUT &as_handle));
			_handle = BitCast<BLASHandle_t> (as_handle);

			if (not dbgName.empty ())
			{
				dev.SetObjectName (BitCast<uint64_t> (_bottomLevelAS), dbgName, VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
			}

			_memoryId = MemoryID{ memId };
			_debugName = dbgName;
			_flags = desc.flags;

			return true;
		}

		/*
		=================================================
			Destroy
		=================================================
		*/
		void VRayTracingGeometry::Destroy (VResourceManager &resMngr)
		{
			EXLOCK (RWDataRaceCheck, _drCheck);

			if (_bottomLevelAS) {
				auto&	dev = resMngr.GetDevice ();
				dev.vkDestroyAccelerationStructureNV (dev.GetVkDevice (), _bottomLevelAS, null);
			}

			if (_memoryId) {
				resMngr.ReleaseResource (_memoryId.Release ());
			}

			_bottomLevelAS = VK_NULL_HANDLE;
			_handle = BLASHandle_t (0);
			_flags = Default;

			{
				Array<Triangles>	temp;
				std::swap (_triangles, temp);
			} {
				Array<AABB>		temp;
				std::swap (_aabbs, temp);
			}
			_debugName.clear ();
		}

		/*
		=================================================
			GetGeometryIndex
		=================================================
		*/
		size_t  VRayTracingGeometry::GetGeometryIndex (const GeometryID &id) const
		{
			size_t	pos = BinarySearch (ArrayView<Triangles>{_triangles}, id);
			if (pos < _triangles.size ())
				return pos;

			pos = BinarySearch (ArrayView<AABB>{_aabbs}, id);
			if (pos < _aabbs.size ())
				return pos + _triangles.size ();

			return UMax;
		}

	}
}