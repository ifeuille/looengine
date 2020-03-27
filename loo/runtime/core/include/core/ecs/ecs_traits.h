#pragma once

#include <cstdint>


namespace looecs
{
	/**
		* @brief Entity traits.
		*
		* Primary template isn't defined on purpose. All the specializations give a
		* compile-time error unless the template parameter is an accepted entity type.
		*/
	template<typename>
	struct ecs_traits;

	/**
	 * @brief Entity traits for a 16 bits entity identifier.
	 *
	 * A 16 bits entity identifier guarantees:
	 *
	 * * 12 bits for the entity number (up to 4k entities).
	 * * 4 bit for the version (resets in [0-15]).
	 */
	template<>
	struct ecs_traits<std::uint16_t> {
		/*! @brief Underlying entity type. */
		using entity_type = std::uint16_t;
		/*! @brief Underlying version type. */
		using version_type = std::uint8_t;
		/*! @brief Difference type. */
		using difference_type = std::int32_t;

		/*! @brief Mask to use to get the entity number out of an identifier. */
		static constexpr std::uint16_t entity_mask = 0xFFF;
		/*! @brief Mask to use to get the version out of an identifier. */
		static constexpr std::uint16_t version_mask = 0xF;
		/*! @brief Extent of the entity number within an identifier. */
		static constexpr auto entity_shift = 12;
	};

	/**
	 * @brief Entity traits for a 32 bits entity identifier.
	 *
	 * A 32 bits entity identifier guarantees:
	 *
	 * * 20 bits for the entity number (suitable for almost all the games).
	 * * 12 bit for the version (resets in [0-4095]).
	 */
	template<>
	struct ecs_traits<std::uint32_t> {
		/*! @brief Underlying entity type. */
		using entity_type = std::uint32_t;
		/*! @brief Underlying version type. */
		using version_type = std::uint16_t;
		/*! @brief Difference type. */
		using difference_type = std::int64_t;

		/*! @brief Mask to use to get the entity number out of an identifier. */
		static constexpr std::uint32_t entity_mask = 0xFFFFF;
		/*! @brief Mask to use to get the version out of an identifier. */
		static constexpr std::uint32_t version_mask = 0xFFF;
		/*! @brief Extent of the entity number within an identifier. */
		static constexpr auto entity_shift = 20;
	};

	/**
	 * @brief Entity traits for a 64 bits entity identifier.
	 *
	 * A 64 bits entity identifier guarantees:
	 *
	 * * 32 bits for the entity number (an indecently large number).
	 * * 32 bit for the version (an indecently large number).
	 */
	template<>
	struct ecs_traits<std::uint64_t> {
		/*! @brief Underlying entity type. */
		using entity_type = std::uint64_t;
		/*! @brief Underlying version type. */
		using version_type = std::uint32_t;
		/*! @brief Difference type. */
		using difference_type = std::int64_t;

		/*! @brief Mask to use to get the entity number out of an identifier. */
		static constexpr std::uint64_t entity_mask = 0xFFFFFFFF;
		/*! @brief Mask to use to get the version out of an identifier. */
		static constexpr std::uint64_t version_mask = 0xFFFFFFFF;
		/*! @brief Extent of the entity number within an identifier. */
		static constexpr auto entity_shift = 32;
	};


}