#ifndef LE_CORE_MATHCORE_H
#define LE_CORE_MATHCORE_H
#include "global/global.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/common.hpp>
#include <glm/gtx/compatibility.hpp>

#include "global/extstd/typetraits.h"
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

		typedef glm::bool3 bvec3;
		typedef glm::bool4 bvec4;

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
		template <typename T>
		ND_ LOO_FORCEINLINE constexpr auto  RoundToInt (const T& x)
		{
			STATIC_ASSERT (IsFloatPoint<T>);

			if constexpr (sizeof (T) >= sizeof (int64_t))
				return int64_t (std::round (x));

			if constexpr (sizeof (T) >= sizeof (int32_t))
				return int32_t (std::round (x));
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


		template <typename T>
		inline constexpr std::enable_if_t< std::is_scalar<T>::value, bool >  Equals (const T &lhs, const T &rhs, const T &err = std::numeric_limits<T>::epsilon () * T (2))
		{
			if (IsUnsignedInteger<T>)
			{
				return lhs < rhs ? ((rhs - lhs) <= err) : ((lhs - rhs) <= err);
			}
			else
				return std::abs (lhs - rhs) <= err;
		}
		/*
	=================================================
		helpers
	=================================================
	*/
	namespace _hidden_
	{
		template <typename T1, typename T2, typename Result>
		using EnableForInt = EnableIf< IsSignedInteger<T1> and IsSignedInteger<T2>, Result >;

		template <typename T1, typename T2, typename Result>
		using EnableForUInt = EnableIf< IsUnsignedInteger<T1> and IsUnsignedInteger<T2>, Result >;

	}	// 

	/*
	=================================================
		AdditionIsSafe
	=================================================
	*/
		template <typename T1, typename T2>
		ND_ LOO_FORCEINLINE constexpr _hidden_::EnableForInt<T1, T2, bool>  AdditionIsSafe (const T1 a, const T2 b)
		{
			STATIC_ASSERT (IsScalar<T1> and IsScalar<T2>);

			using T = decltype(a + b);

			const T	x = T (a);
			const T	y = T (b);
			const T	min = std::numeric_limits<T>::min ();
			const T	max = std::numeric_limits<T>::max ();

			bool	overflow = ((y > 0) & (x > max - y)) |
				((y < 0) & (x < min - y));
			return not overflow;
		}

		/*
		=================================================
			AdditionIsSafe
		=================================================
		*/
		template <typename T1, typename T2>
		ND_ LOO_FORCEINLINE constexpr _hidden_::EnableForUInt<T1, T2, bool>  AdditionIsSafe (const T1 a, const T2 b)
		{
			STATIC_ASSERT (IsScalar<T1> and IsScalar<T2>);

			using T = decltype(a + b);

			const T	x = T (a);
			const T	y = T (b);

			return (x + y) >= (x | y);
		}

		/*
		=================================================
			AlignToSmaller
		=================================================
		*/
		template <typename T0, typename T1>
		ND_ LOO_FORCEINLINE constexpr auto  AlignToSmaller (const T0 &value, const T1 &align)
		{
			ASSERT (align > 0);
			return (value / align) * align;
		}

		/*
		=================================================
			AlignToLarger
		=================================================
		*/
		template <typename T0, typename T1>
		ND_ LOO_FORCEINLINE constexpr auto  AlignToLarger (const T0 &value, const T1 &align)
		{
			ASSERT (align > 0);
			return ((value + align - 1) / align) * align;
		}

		/*
		=================================================
			IsIntersects
		----
			1D intersection check
		=================================================
		*/
		template <typename T>
		ND_ LOO_FORCEINLINE constexpr bool  IsIntersects (const T& begin1, const T& end1,
			const T& begin2, const T& end2)
		{
			return (end1 > begin2) & (begin1 < end2);
		}

		/*
		=================================================
			GetIntersection
		=================================================
		*/
		template <typename T>
		ND_ LOO_FORCEINLINE constexpr bool  GetIntersection (const T& begin1, const T& end1,
			const T& begin2, const T& end2,
			OUT T& outBegin, OUT T& outEnd)
		{
			outBegin = std::max (begin1, begin2);
			outEnd = std::min (end1, end2);
			return outBegin < outEnd;
		}

		/*
=================================================
	SafeDiv
=================================================
*/
		template <typename T1, typename T2, typename T3>
		ND_ LOO_FORCEINLINE constexpr auto  SafeDiv (const T1& lhs, const T2& rhs, const T3& defVal)
		{
			STATIC_ASSERT (IsScalarOrEnum<T1> and IsScalarOrEnum<T2> and IsScalarOrEnum<T3>);

			using T = decltype(lhs + rhs + defVal);

			return not Equals (rhs, T (0)) ? (T (lhs) / T (rhs)) : T (defVal);
		}

		template <typename T1, typename T2>
		ND_ LOO_FORCEINLINE constexpr auto  SafeDiv (const T1& lhs, const T2& rhs)
		{
			return SafeDiv (lhs, rhs, T1 (0));
		}

		/*
		=================================================
			Ln / Log / Log2 / Log10
		=================================================
		*/
		template <typename T>
		ND_ LOO_FORCEINLINE EnableIf<IsFloatPoint<T>, T>  Ln (const T& x)
		{
			return std::log (x);
		}

		template <typename T>
		ND_ LOO_FORCEINLINE EnableIf<IsFloatPoint<T>, T>  Log2 (const T& x)
		{
			return std::log2 (x);
		}

		template <typename T>
		ND_ LOO_FORCEINLINE EnableIf<IsFloatPoint<T>, T>  Log10 (const T& x)
		{
			return std::log10 (x);
		}

		template <typename Base, typename T>
		ND_ LOO_FORCEINLINE EnableIf<IsFloatPoint<T>, T>  Log (const T& x, Base base)
		{
			static constexpr auto log_base = std::log (base);
			return std::log (x) / log_base;
		}

		/*
		=================================================
			Wrap
		=================================================
		*/
		template <typename T>
		LOO_FORCEINLINE EnableIf<IsFloatPoint<T>, T>  Wrap (const T& value, const T& minValue, const T& maxValue)
		{
			// check for NaN
			if (minValue >= maxValue)
				return minValue;

			T	result = T (minValue + std::fmod (value - minValue, maxValue - minValue));

			if (result < minValue)
				result += (maxValue - minValue);

			return result;
		}
	}
}

#endif