#pragma once

#include "vkfg/fg/enums.h"
#include "vkfg/fg/ids.h"
#include "vkfg/fg/vertexdesc.h"
#include "global/math/matrix.h"

namespace loo
{
	namespace vkfg
	{
		//
		// Ray Tracing Geometry Description
		//
		struct RayTracingGeometryDesc
		{
			// types
			using EFlags = ERayTracingGeometryFlags;

			struct Triangles
			{
				// variables
				GeometryID		geometryId;
				EFlags			flags = Default;

				uint			vertexCount = 0;
				EVertexType		vertexFormat = Default;

				// optional:
				uint			indexCount = 0;
				EIndex			indexType = Default;

				// methods
				Triangles () {}
				explicit Triangles (const GeometryID &id) : geometryId{id} {}

				template <typename T, typename Idx>	Triangles&  SetVertices (Idx count);
				template <typename Idx>				Triangles&  SetVertices (Idx count, EVertexType fmt);
				template <typename Idx>				Triangles&  SetIndices (Idx count, EIndex type);
				template <typename T, typename Idx>	Triangles&  SetIndices (Idx count);
													Triangles&  AddFlags (EFlags value)			{ flags |= value;  return *this; }
													Triangles&  SetID (const GeometryID &id)	{ geometryId = id;  return *this; }


			};


			struct AABB
			{
				// variables
				GeometryID		geometryId;
				EFlags			flags			= Default;
				uint			aabbCount		= 0;

				// methods
				AABB () {}
				explicit AABB (const GeometryID &id) : geometryId{id} {}

				template <typename Idx>	AABB&  SetCount (Idx count)			{ STATIC_ASSERT(IsInteger<Idx>, "");  aabbCount = uint(count);  return *this; }
										AABB&  AddFlags (EFlags value)		{ flags |= value;  return *this; }
										AABB&  SetID (const GeometryID &id)	{ geometryId = id;  return *this; }

			};

			// variables
			ArrayView<Triangles> triangles;
			ArrayView<AABB> aabbs;
			ERayTracingFlags flags = Default;

			// methods
			RayTracingGeometryDesc () {}
			explicit RayTracingGeometryDesc (ArrayView<Triangles> triangles_) :triangles (triangles_) {}
			explicit RayTracingGeometryDesc (ArrayView<AABB> aabbs_) :aabbs (aabbs_) {}
			explicit RayTracingGeometryDesc (ArrayView<Triangles> triangles_,ArrayView<AABB> aabbs_) :triangles (triangles_),aabbs (aabbs_) {}

		};

		template <typename T, typename Idx>
		inline RayTracingGeometryDesc::Triangles&
			RayTracingGeometryDesc::Triangles::SetVertices (Idx count)
		{
			STATIC_ASSERT (IsInteger<Idx>,"");
			vertexCount = uint (count);
			vertexFormat = VertexDesc<T>::attrib;
			return *this;
		}

		template <typename Idx>
		inline RayTracingGeometryDesc::Triangles&
			RayTracingGeometryDesc::Triangles::SetVertices (Idx count, EVertexType fmt)
		{
			STATIC_ASSERT (IsInteger<Idx>,"");
			vertexCount = uint (count);
			vertexFormat = fmt;
			return *this;
		}

		template <typename Idx>
		inline RayTracingGeometryDesc::Triangles&
			RayTracingGeometryDesc::Triangles::SetIndices (Idx count, EIndex type)
		{
			STATIC_ASSERT (IsInteger<Idx>,"");
			indexCount = uint (count);
			indexType = type;
			return *this;
		}

		template <typename T, typename Idx>
		inline RayTracingGeometryDesc::Triangles&
			RayTracingGeometryDesc::Triangles::SetIndices (Idx count)
		{
			using type = std::remove_cv_t< std::remove_reference_t<T> >;

			STATIC_ASSERT (IsInteger<Idx>,"");
			STATIC_ASSERT ((IsSameTypes<type, uint32_t>) or (IsSameTypes<type, uint16_t>),"");

			indexCount = uint (count);
			indexType = IsSameTypes<type, uint> ? EIndex::UInt : EIndex::UShort;
			return *this;
		}
	}
}