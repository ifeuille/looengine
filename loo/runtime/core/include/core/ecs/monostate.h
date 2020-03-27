#pragma once


#include <atomic>
#include <cassert>
#include "core/ecs/family.h"
#include "core/ecs/hashed_string.h"

namespace looecs {


	/**
	 * @brief Minimal implementation of the monostate pattern.
	 *
	 * A minimal, yet complete configuration system built on top of the monostate
	 * pattern. Thread safe by design, it works only with basic types like `int`s or
	 * `bool`s.<br/>
	 * Multiple types and therefore more than one value can be associated with a
	 * single key. Because of this, users must pay attention to use the same type
	 * both during an assignment and when they try to read back their data.
	 * Otherwise, they can incur in unexpected results.
	 */
	template<HashedString::hash_type>
	struct Monostate {
		/**
		 * @brief Assigns a value of a specific type to a given key.
		 * @tparam Type Type of the value to assign.
		 * @param val User data to assign to the given key.
		 */
		template<typename Type>
		void operator=(Type val) const ECS_NOEXCEPT {
			Monostate::value<Type> = val;
		}

		/**
		 * @brief Gets a value of a specific type for a given key.
		 * @tparam Type Type of the value to get.
		 * @return Stored value, if any.
		 */
		template<typename Type>
		operator Type() const ECS_NOEXCEPT {
			return Monostate::value<Type>;
		}

	private:
		template<typename Type>
		static std::atomic<Type> value;
	};


	template<HashedString::hash_type ID>
	template<typename Type>
	std::atomic<Type> Monostate<ID>::value{};


}
