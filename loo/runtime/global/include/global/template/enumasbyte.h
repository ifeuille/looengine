#ifndef LE_CORE_TEMPLATE_COREENUMASBYTE_H
#define LE_CORE_TEMPLATE_COREENUMASBYTE_H
#include "global/global.h"

namespace loo
{
	namespace global
	{
		template<class TEnum, class ToType>
		inline const ToType enum_to_type (const TEnum enumValue)
		{
			return static_cast<ToType>(enumValue);
		}
		template<class TEnum>
		inline const int32 enum_to_int32 (const TEnum enumValue)
		{
			return enum_to_type<TEnum, int32> (enumValue);
		}
		template<class TEnum>
		inline const uint8 enum_to_byte (const TEnum enumValue)
		{
			return enum_to_type<TEnum, uint8> (enumValue);
		}



		template <typename T>
		struct TIsEnum
		{
			enum { Value = __is_enum (T) };
		};



		template <bool> struct TEnumAsByte_EnumClass;
		///template <> struct DEPRECATED(4.15, "TEnumAsByte is not intended for use with enum classes - please derive your enum class from uint8 instead.") TEnumAsByte_EnumClass<true> {};
		template <> struct TEnumAsByte_EnumClass<false> {};

		/**
		 * Template to store enumeration values as bytes in a type-safe way.
		 */
		template<class TEnum>
		class TEnumAsByte
		{
			//typedef TEnumAsByte_EnumClass<TIsEnumClass<TEnum>::Value> Check;

		public:
			typedef TEnum EnumType;

			/** Default Constructor (no initialization). */
			LOO_FORCEINLINE TEnumAsByte () { }

			/**
			 * Copy constructor.
			 *
			 * @param InValue value to construct with.
			 */
			LOO_FORCEINLINE TEnumAsByte (const TEnumAsByte &InValue)
				: Value (InValue.Value)
			{ }

			/**
			 * Constructor, initialize to the enum value.
			 *
			 * @param InValue value to construct with.
			 */
			LOO_FORCEINLINE TEnumAsByte (TEnum InValue)
				: Value (static_cast<uint8>(InValue))
			{ }

			/**
			 * Constructor, initialize to the int32 value.
			 *
			 * @param InValue value to construct with.
			 */
			explicit LOO_FORCEINLINE TEnumAsByte (int32 InValue)
				: Value (static_cast<uint8>(InValue))
			{ }

			/**
			 * Constructor, initialize to the int32 value.
			 *
			 * @param InValue value to construct with.
			 */
			explicit LOO_FORCEINLINE TEnumAsByte (uint8 InValue)
				: Value (InValue)
			{ }

		public:

			/**
			 * Assignment operator.
			 *
			 * @param InValue value to set.
			 * @return This instance.
			 */
			LOO_FORCEINLINE TEnumAsByte& operator=(TEnumAsByte InValue)
			{
				Value = InValue.Value;
				return *this;
			}
			/**
			 * Assignment operator.
			 *
			 * @param InValue value to set.
			 * @return This instance.
			 */
			LOO_FORCEINLINE TEnumAsByte& operator=(TEnum InValue)
			{
				Value = static_cast<uint8>(InValue);
				return *this;
			}

			/**
			 * Compares two enumeration values for equality.
			 *
			 * @param InValue The value to compare with.
			 * @return true if the two values are equal, false otherwise.
			 */
			bool operator==(TEnum InValue) const
			{
				return static_cast<TEnum>(Value) == InValue;
			}

			/**
			 * Compares two enumeration values for equality.
			 *
			 * @param InValue The value to compare with.
			 * @return true if the two values are equal, false otherwise.
			 */
			bool operator==(TEnumAsByte InValue) const
			{
				return Value == InValue.Value;
			}

			/** Implicit conversion to TEnum. */
			operator TEnum() const
			{
				return (TEnum)Value;
			}

		public:

			/**
			 * Gets the enumeration value.
			 *
			 * @return The enumeration value.
			 */
			TEnum GetValue () const
			{
				return (TEnum)Value;
			}

		private:

			/** Holds the value as a byte. **/
			uint8 Value;


			LOO_FORCEINLINE friend uint32 GetTypeHash (const TEnumAsByte& Enum)
			{
				return GetTypeHash (Enum.Value);
			}
		};

		template<class TEnum, class ToType>
		class TEnumTo
		{
			//typedef TEnumAsByte_EnumClass<TIsEnumClass<TEnum>::Value> Check;

		public:
			typedef TEnum enum_type;
			typedef ToType to_type;

			/** Default Constructor (no initialization). */
			LOO_FORCEINLINE TEnumTo () { }

			/**
			 * Copy constructor.
			 *
			 * @param InValue value to construct with.
			 */
			LOO_FORCEINLINE TEnumTo (const TEnumTo &InValue)
				: Value (InValue.Value)
			{ }

			/**
			 * Constructor, initialize to the enum value.
			 *
			 * @param InValue value to construct with.
			 */
			LOO_FORCEINLINE TEnumTo (enum_type InValue)
				: Value (static_cast<to_type>(InValue))
			{ }

			/**
			 * Constructor, initialize to the int32 value.
			 *
			 * @param InValue value to construct with.
			 */
			explicit LOO_FORCEINLINE TEnumTo (int32 InValue)
				: Value (static_cast<ToType>(InValue))
			{ }

			/**
			 * Constructor, initialize to the int32 value.
			 *
			 * @param InValue value to construct with.
			 */
			explicit LOO_FORCEINLINE TEnumTo (uint8 InValue)
				: Value (InValue)
			{ }

		public:

			/**
			 * Assignment operator.
			 *
			 * @param InValue value to set.
			 * @return This instance.
			 */
			LOO_FORCEINLINE TEnumTo& operator=(const TEnumTo<TEnum, ToType> InValue)
			{
				Value = InValue.Value;
				return *this;
			}
			/**
			 * Assignment operator.
			 *
			 * @param InValue value to set.
			 * @return This instance.
			 */
			LOO_FORCEINLINE TEnumTo& operator=(TEnum InValue)
			{
				Value = static_cast<uint8>(InValue);
				return *this;
			}

			/**
			 * Compares two enumeration values for equality.
			 *
			 * @param InValue The value to compare with.
			 * @return true if the two values are equal, false otherwise.
			 */
			bool operator==(TEnum InValue) const
			{
				return static_cast<TEnum>(Value) == InValue;
			}

			/**
			 * Compares two enumeration values for equality.
			 *
			 * @param InValue The value to compare with.
			 * @return true if the two values are equal, false otherwise.
			 */
			bool operator==(TEnumTo InValue) const
			{
				return Value == InValue.Value;
			}

			/** Implicit conversion to TEnum. */
			operator TEnum() const
			{
				return (TEnum)Value;
			}

		public:

			/**
			 * Gets the enumeration value.
			 *
			 * @return The enumeration value.
			 */
			TEnum GetValue () const
			{
				return (TEnum)Value;
			}

		private:

			/** Holds the value as a byte. **/
			ToType Value;

		};



		//template<class T> struct std::is_pod<TEnumAsByte<T>> { enum { Value = true }; };
	}
}
#endif