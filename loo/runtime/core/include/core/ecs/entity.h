#pragma once
#include "core/ecs/config.h"
#include "core/ecs/ecs_traits.h"

namespace looecs
{
	namespace internal
	{
		struct Nil
		{
			explicit constexpr Nil () = default;

			template<typename Entity>
			constexpr operator Entity() const ECS_NOEXCEPT {
				using traits_type = looecs::ecs_traits<Entity>;
				return traits_type::entity_mask | (traits_type::version_mask << traits_type::entity_shift);
			}

			constexpr bool operator==(Nil) const ECS_NOEXCEPT {
				return true;
			}

			constexpr bool operator !=(Nil)const ECS_NOEXCEPT {
				return false;
			}

			template<typename Entity>
			constexpr bool operator==(const Entity entity)const ECS_NOEXCEPT {
				return entity == static_cast<Entity>(*this);
			}

			template<typename Entity>
			constexpr bool operator!=(const Entity entity)const ECS_NOEXCEPT {
				return entity != static_cast<Entity>(*this);
			}

		};

		template<typename Entity>
		constexpr bool operator==(const Entity entity, Nil nil) ECS_NOEXCEPT {
			return nil == entity;
		}


		template<typename Entity>
		constexpr bool operator!=(const Entity entity, Nil nil) ECS_NOEXCEPT {
			return nil != entity;
		}
	}


	/**
	 * Internal details not to be documented.
	 * @endcond TURN_OFF_DOXYGEN
	 */


	 /**
	  * @brief Null entity.
	  *
	  * There exist implicit conversions from this variable to entity identifiers of
	  * any allowed type. Similarly, there exist comparision operators between the
	  * null entity and any other entity identifier.
	  */
	constexpr auto nil = internal::Nil{};

}