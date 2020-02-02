#ifndef LOO_GLOBAL_TEMPLATE_HASH_H
#define LOO_GLOBAL_TEMPLATE_HASH_H
#pragma once
#include "global/global.h"
namespace loo
{

	//
	// Hash Value
	//

	struct HashVal
	{
		// variables
	private:
		size_t		_value = 0;

		// methods
	public:
		constexpr HashVal () {}
		explicit constexpr HashVal (size_t val) : _value{ val } {}

		constexpr bool	operator == (const HashVal &rhs)	const { return _value == rhs._value; }
		constexpr bool	operator != (const HashVal &rhs)	const { return ! (*this == rhs); }
		constexpr bool	operator >  (const HashVal &rhs)	const { return _value > rhs._value; }
		constexpr bool  operator <  (const HashVal &rhs)	const { return _value < rhs._value; }

		constexpr HashVal&	operator << (const HashVal &rhs)
		{
			const size_t	mask = (sizeof (_value) * 8 - 1);
			size_t			val = rhs._value;
			size_t			shift = 8;

			shift &= mask;
			_value ^= (val << shift) | (val >> (~(shift - 1) & mask));

			return *this;
		}

		constexpr const HashVal  operator + (const HashVal &rhs) const
		{
			return HashVal (*this) << rhs;
		}

		explicit constexpr operator size_t () const { return _value; }
	};
	//-----------------------------------------------------------------------------



	/*
	=================================================
		HashOf
	=================================================
	*/
	template <typename T>
	inline EnableIf<!IsFloatPoint<T>, HashVal>  HashOf (const T &value)
	{
		return HashVal (std::hash<T> ()(value));
	}

	/*
	=================================================
		HashOf (float)
	=================================================
	*/
	inline HashVal  HashOf (const float &value, uint32_t ignoreMantissaBits = (23 - 10))
	{
		assert (ignoreMantissaBits < 23);
		uint32	dst;
		std::memcpy (OUT &dst, &value, sizeof (dst));
		dst &= ~((1 << ignoreMantissaBits) - 1);
		return HashVal (std::hash<uint32_t> ()(dst));
	}

	/*
	=================================================
		HashOf (double)
	=================================================
	*/
	inline HashVal  HashOf (const double &value, uint32_t ignoreMantissaBits = (52 - 10))
	{
		assert (ignoreMantissaBits < 52);
		uint64	dst;
		std::memcpy (OUT &dst, &value, sizeof (dst));
		dst &= ~((1 << ignoreMantissaBits) - 1);
		return HashVal (std::hash<uint64_t> ()(dst));
	}

	/*
	=================================================
		HashOf (buffer)
	----
		use private api to calculate hash of buffer
	=================================================
	*/
	inline HashVal  HashOf (const void *ptr, size_t sizeInBytes)
	{
		assert (ptr && sizeInBytes);

# if defined(LOO_HAS_HASHFN_HashArrayRepresentation)
		return HashVal{ std::_Hash_array_representation (static_cast<const unsigned char*>(ptr), sizeInBytes) };

#elif defined(LOO_HAS_HASHFN_Murmur2OrCityhash)
		return HashVal{ std::__murmur2_or_cityhash<size_t> ()(ptr, sizeInBytes) };

#elif defined(LOO_HAS_HASHFN_HashBytes)
		return HashVal{ std::_Hash_bytes (ptr, sizeInBytes, 0) };

#else
		LOO_COMPILATION_MESSAGE ("used fallback hash function")
		const uint8_t*	buf = static_cast<const uint8_t*>(ptr);
		HashVal			result;
		for (size_t i = 0; i < sizeInBytes; ++i) {
			result << HashVal{ buf[i] };
		}
		return result;
#endif
	}


}

namespace std
{
	template <typename First, typename Second>
	struct hash< std::pair<First, Second> >
	{
		size_t  operator () (const std::pair<First, Second> &value) const
		{
			return size_t (loo::HashOf (value.first) + loo::HashOf (value.second));
		}
	};

}	// std

#endif