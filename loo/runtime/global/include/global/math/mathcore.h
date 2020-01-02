#ifndef LE_CORE_MATHCORE_H
#define LE_CORE_MATHCORE_H
#include "global/global.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace loo
{
	namespace math
	{
		/*-----------------------------------------------------------------------------
			Floating point constants.
		-----------------------------------------------------------------------------*/
		// 常量定义
		/////////////////////////////////////////////////////////////////////////////////
#undef  PI
		float const PI = 3.1415926535897932f;	// PI
		double const PI_DOUBLE = 3.1415926535897932;
		float const PI2 = 6.283185f;			// PI * 2
		float const HALF_PI = 1.57079632679f;	// PI / 2
		float const INV_PI = 0.31830988618f;    // 1/PI

		float const DEG90 = 1.570796f;			// 90 度
		float const DEG270 = -1.570796f;			// 270 度
		float const DEG45 = 0.7853981f;			// 45 度
		float const DEG5 = 0.0872664f;			// 5 度
		float const DEG10 = 0.1745329f;			// 10 度
		float const DEG20 = 0.3490658f;			// 20 度
		float const DEG30 = 0.5235987f;			// 30 度
		float const DEG60 = 1.047197f;			// 60 度
		float const DEG120 = 2.094395f;			// 120 度

		float const DEG40 = 0.6981317f;			// 40 度
		float const DEG80 = 1.396263f;			// 80 度
		float const DEG140 = 2.443460f;			// 140 度
		float const DEG160 = 2.792526f;			// 160 度

		float const SQRT2 = 1.414213f;			// 根2
		float const SQRT_2 = 0.7071068f;			// 1 / SQRT2
		float const SQRT3 = 1.732050f;			// 根3

		float const DEG2RAD = 0.01745329f;			// 角度化弧度因数
		float const RAD2DEG = 57.29577f;			// 弧度化角度因数
		float const DELTA = 0.00001f;

		float const SMALL_NUMBER = (1.e-8f);
		float const  KINDA_SMALL_NUMBER(1.e-4f);

		double const BIG_NUMBER = (3.4e+38f);
		double const EULERS_NUMBER = (2.71828182845904523536);

		// Copied from float.h
		double const MAX_FLT = 3.402823466e+38F;


		/**
		 * Lengths of normalized vectors (These are half their maximum values
		 * to assure that dot products with normalized vectors don't overflow).
		 */
		float const FLOAT_NORMAL_THRESH = (0.0001f);

		//
		// Magic numbers for numerical precision.
		//
		float const THRESH_POINT_ON_PLANE = (0.10f);	/* Thickness of plane for front/back/inside test */
		float const THRESH_POINT_ON_SIDE = (0.20f);	/* Thickness of polygon side's side-plane for point-inside/outside/on side test */
		float const THRESH_POINTS_ARE_SAME = (0.00002f);	/* Two points are same if within this distance */
		float const THRESH_POINTS_ARE_NEAR = (0.015f);	/* Two points are near if within this distance and can be combined if imprecise math is ok */
		float const THRESH_NORMALS_ARE_SAME = (0.00002f);	/* Two normal points are same if within this distance */
		double const THRESH_UVS_ARE_SAME = (0.0009765625);/* Two UV are same if within this threshold (1.0f/1024f) */
															/* Making this too large results in incorrect CSG classification and disaster */
		float const THRESH_VECTORS_ARE_NEAR = (0.0004f);	/* Two vectors are near if within this distance and can be combined if imprecise math is ok */
															/* Making this too large results in lighting problems due to inaccurate texture coordinates */
		float const THRESH_SPLIT_POLY_WITH_PLANE = (0.25f);		/* A plane splits a polygon in half */
		float const THRESH_SPLIT_POLY_PRECISELY = (0.01f);	/* A plane exactly splits a polygon */
		float const THRESH_ZERO_NORM_SQUARED = (0.0001f);	/* Size of a unit normal that is considered "zero", squared */
		float const THRESH_NORMALS_ARE_PARALLEL = (0.999845f);	/* Two unit vectors are parallel if abs(A dot B) is greater than or equal to this. This is roughly cosine(1.0 degrees). */
		float const THRESH_NORMALS_ARE_ORTHOGONAL = (0.017455f);	/* Two unit vectors are orthogonal (perpendicular) if abs(A dot B) is less than or equal this. This is roughly cosine(89.0 degrees). */

		float const THRESH_VECTOR_NORMALIZED = (0.01f);	/** Allowed error for a normalized vector (against squared magnitude) */
		float const THRESH_QUAT_NORMALIZED = (0.01f);	/** Allowed error for a normalized quaternion (against squared magnitude) */


		typedef glm::vec1 vec1;
		typedef glm::vec2 vec2;
		typedef glm::vec3 vec3;
		typedef glm::vec4 vec4;

		typedef glm::ivec1 ivec1;
		typedef glm::ivec2 ivec2;
		typedef glm::ivec3 ivec3;
		typedef glm::ivec4 ivec4;

		typedef glm::uvec1 uvec1;
		typedef glm::uvec2 uvec2;
		typedef glm::uvec3 uvec3;
		typedef glm::uvec4 uvec4;


		typedef glm::u8vec1 u8vec1;
		typedef glm::u8vec2 u8vec2;
		typedef glm::u8vec3 u8vec3;
		typedef glm::u8vec4 u8vec4;


		typedef glm::f32vec1 f32vec1;
		typedef glm::f32vec2 f32vec2;
		typedef glm::f32vec3 f32vec3;
		typedef glm::f32vec4 f32vec4;

		typedef glm::f64vec1 f64vec1;
		typedef glm::f64vec2 f64vec2;
		typedef glm::f64vec3 f64vec3;
		typedef glm::f64vec4 f64vec4;

		using glm::clamp;
		using glm::min;
		using glm::max;
		using glm::abs;
		using glm::lerp;
		using glm::notEqual;
		using glm::equal;
		using glm::normalize;
		using glm::sqrt;
		using glm::inversesqrt;
		using glm::inverse;
		using glm::inverseTranspose;


		using std::pow;
		using std::powf;
		using std::powl;
		using std::trunc;
		using std::truncf;
		using std::truncl;
		using std::round;
		using std::roundf;
		using std::roundl;
		using std::floor;
		using std::floorf;
		using std::floorl;
		using std::ceil;
		using std::ceilf;
		using std::ceill;
		using std::fmod;
		using std::modf;
		using std::fmodf;
		using std::modff;



		template< class T >
		static LOO_FORCEINLINE T square(const T A)
		{
			return A * A;
		}
		template<class T>
		static LOO_FORCEINLINE T max3(const T A, const T B, const T C)
		{
			return max(A, max(B, C));
		}
		template<class T>
		static LOO_FORCEINLINE T min3(const T A, const T B, const T C)
		{
			return min(A, min(B, C));
		}
		static LOO_FORCEINLINE int TruncToInt(double A)
		{
			return static_cast<int>(trunc(A));
		}
		static LOO_FORCEINLINE int TruncToInt(float A)
		{
			return static_cast<int>(truncf(A));
		}
		static LOO_FORCEINLINE int RoundToInt(double A)
		{
			return static_cast<int>(round(A));
		}
		static LOO_FORCEINLINE int RoundToInt(float A)
		{
			return static_cast<int>(roundf(A));
		}
		static LOO_FORCEINLINE int FloorToInt(double A)
		{
			return static_cast<int>(floor(A));
		}
		static LOO_FORCEINLINE int FloorToInt(float A)
		{
			return static_cast<int>(floorf(A));
		}
		static LOO_FORCEINLINE int CeilToInt(double A)
		{
			return static_cast<int>(ceil(A));
		}
		static LOO_FORCEINLINE int CeilToInt(float A)
		{
			return static_cast<int>(ceilf(A));
		}
		template< class T, class U >
		static LOO_FORCEINLINE T lerp(const T& A, const T& B, const U& Alpha)
		{
			return (T)(A + Alpha * (B - A));
		}
		//static LOO_FORCEINLINE uint32 CountLeadingZeros(uint32 Value)
		//{
		//	// Use BSR to return the log2 of the integer
		//	unsigned long Log2;
		//	if (_BitScanReverse(&Log2, Value) != 0)
		//	{
		//		return 31 - Log2;
		//	}

		//	return 32;
		//}

		//返回大于等于value的以2为底数的最大N次幂的指数N
		static LOO_FORCEINLINE uint32 CeilLogTwo(uint32 Arg)
		{
			return glm::findMSB(Arg) + 1;
		}


		//用于对基于glm::vec的结构体生成对应的模板特化

	}
}

#endif