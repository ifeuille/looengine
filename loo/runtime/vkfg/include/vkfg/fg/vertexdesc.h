#ifndef LOO_VKFG_FG_VERTEXDECS_H
#define LOO_VKFG_FG_VERTEXDECS_H
#pragma once
#include "global/types.h"
#include "vkfg/fg/enums.h"

namespace loo
{
	namespace vkfg
	{

		//
		// Vertex Description
		//
		template <typename T>
		struct VertexDesc
		{};


		// Float types
#	ifdef LOO_HALF_TYPE
		template <>
		struct VertexDesc <half>
		{
			typedef half					type;
			static const EVertexType		attrib = EVertexType::Half;
		};
#	endif

		template <>
		struct VertexDesc <float>
		{
			typedef float					type;
			static const EVertexType		attrib = EVertexType::Float;
		};

		template <>
		struct VertexDesc <double>
		{
			typedef double					type;
			static const EVertexType		attrib = EVertexType::Double;
		};


		// Integer types
		template <>
		struct VertexDesc <int8_t>
		{
			typedef int8_t					type;
			static const EVertexType		attrib = EVertexType::Byte;
		};

		template <>
		struct VertexDesc <uint8_t>
		{
			typedef uint8_t					type;
			static const EVertexType		attrib = EVertexType::UByte;
		};


		template <>
		struct VertexDesc <int16_t>
		{
			typedef int16_t					type;
			static const EVertexType		attrib = EVertexType::Short;
		};

		template <>
		struct VertexDesc <uint16_t>
		{
			typedef uint16_t				type;
			static const EVertexType		attrib = EVertexType::UShort;
		};


		template <>
		struct VertexDesc <int32_t>
		{
			typedef int32_t					type;
			static const EVertexType		attrib = EVertexType::Int;
		};

		template <>
		struct VertexDesc <uint32_t>
		{
			typedef uint32_t				type;
			static const EVertexType		attrib = EVertexType::UInt;
		};


		template <>
		struct VertexDesc <int64_t>
		{
			typedef int64_t					type;
			static const EVertexType		attrib = EVertexType::Long;
		};

		template <>
		struct VertexDesc <uint64_t>
		{
			typedef uint64_t				type;
			static const EVertexType		attrib = EVertexType::ULong;
		};


		// Vector types
		template <typename T, uint I>
		struct VertexDesc < loo::math::Vec<T,I> >
		{
			typedef loo::math::Vec<T, I> 				type;
			static const EVertexType		attrib = EVertexType (
				(VertexDesc< T >::attrib & EVertexType::_TypeMask) |
				EVertexType (I << uint (EVertexType::_VecOffset)));
		};


		template <>
		struct VertexDesc <loo::math::RGBA32f>
		{
			typedef loo::math::RGBA32f					type;
			static const EVertexType		attrib = EVertexType::Float4;
		};

		template <>
		struct VertexDesc <loo::math::RGBA32i>
		{
			typedef loo::math::RGBA32i					type;
			static const EVertexType		attrib = EVertexType::Int4;
		};

		template <>
		struct VertexDesc <loo::math::RGBA32u>
		{
			typedef loo::math::RGBA32u					type;
			static const EVertexType		attrib = EVertexType::UInt4;
		};

		template <>
		struct VertexDesc <loo::math::RGBA8u>
		{
			typedef loo::math::RGBA8u					type;
			static const EVertexType		attrib = EVertexType::UByte4_Norm;
		};


		template <typename T>
		struct VertexDesc< const T &> : VertexDesc<T>
		{};

		template <typename T>
		struct VertexDesc< T &> : VertexDesc<T>
		{};


	}	// 

}

#endif