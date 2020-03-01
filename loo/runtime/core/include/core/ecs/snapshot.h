#pragma once

#include <array>
#include <cstddef>
#include <utility>
#include <cassert>
#include <iterator>
#include <type_traits>
#include <unordered_map>
#include "core/ecs/config.h"
#include "core/ecs/ecs_traits.h"
#include "core/ecs/utility.h"

namespace looecs
{
	template<typename>
	class Registry;

	/**
	 * @brief Utility class to create snapshots from a registry.
	 *
	 * A _snapshot_ can be either a dump of the entire registry or a narrower
	 * selection of components and tags of interest.<br/>
	 * This type can be used in both cases if provided with a correctly configured
	 * output archive.
	 *
	 * @tparam Entity A valid entity type (see entt_traits for more details).
	 */
	template<typename Entity>
	class Snapshot final
	{
		friend class Registry<Entity>;
		using follow_fn_type = Entity (const Registry<Entity> &, const Entity);

		Snapshot (const Registry<Entity> &registry, Entity seed, follow_fn_type *follow) ENTT_NOEXCEPT
			: registry{ registry },
			seed{ seed },
			follow{ follow }
		{}

		template<typename Component, typename Archive, typename It>
		void get (Archive &archive, std::size_t sz, It first, It last) const {
			archive (static_cast<Entity>(sz));

			while (first != last) {
				const auto entity = *(first++);

				if (registry.template has<Component> (entity)) {
					archive (entity, registry.template get<Component> (entity));
				}
			}
		}

		template<typename... Component, typename Archive, typename It, std::size_t... Indexes>
		void component (Archive &archive, It first, It last, std::index_sequence<Indexes...>) const {
			std::array<std::size_t, sizeof...(Indexes)> size{};
			auto begin = first;

			while (begin != last) {
				const auto entity = *(begin++);
				using accumulator_type = std::size_t[];
				accumulator_type accumulator = { (registry.template has<Component> (entity) ? ++size[Indexes] : size[Indexes])... };
				(void)accumulator;
			}

			using accumulator_type = int[];
			accumulator_type accumulator = { (get<Component> (archive, size[Indexes], first, last), 0)... };
			(void)accumulator;
		}

	public:

		/*! @brief Copying a snapshot isn't allowed. */
		Snapshot (const Snapshot &) = delete;
		/*! @brief Default move constructor. */
		Snapshot (Snapshot &&) = default;

		/*! @brief Copying a snapshot isn't allowed. @return This snapshot. */
		Snapshot & operator=(const Snapshot &) = delete;
		/*! @brief Default move assignment operator. @return This snapshot. */
		Snapshot & operator=(Snapshot &&) = default;

		template<typename Archive>
		const Snapshot & entities (Archive &archive) const {
			archive (static_cast<Entity>(registry.alive ()));
			registry.each ([&archive](const auto entity) { archive (entity); });
			return *this;
		}

		template<typename Archive>
		const Snapshot & destroyed (Archive &archive) const {
			auto size = registry.size () - registry.alive ();
			archive (static_cast<Entity>(size));

			if (size) {
				auto curr = seed;
				archive (curr);

				for (--size; size; --size) {
					curr = follow (registry, curr);
					archive (curr);
				}
			}

			return *this;
		}

		/**
	 * @brief Puts aside the given component.
	 *
	 * Each instance is serialized together with the entity to which it belongs.
	 * Entities are serialized along with their versions.
	 *
	 * @tparam Component Type of component to serialize.
	 * @tparam Archive Type of output archive.
	 * @param archive A valid reference to an output archive.
	 * @return An object of this type to continue creating the snapshot.
	 */
		template<typename Component, typename Archive>
		const Snapshot & component (Archive &archive) const {
			const auto sz = registry.template size<Component> ();
			const auto *entities = registry.template data<Component> ();

			archive (static_cast<Entity>(sz));

			for (std::remove_const_t<decltype(sz)> i{}; i < sz; ++i) {
				const auto entity = entities[i];
				archive (entity, registry.template get<Component> (entity));
			};

			return *this;
		}

		/**
		 * @brief Puts aside the given components.
		 *
		 * Each instance is serialized together with the entity to which it belongs.
		 * Entities are serialized along with their versions.
		 *
		 * @tparam Component Types of components to serialize.
		 * @tparam Archive Type of output archive.
		 * @param archive A valid reference to an output archive.
		 * @return An object of this type to continue creating the snapshot.
		 */
		template<typename... Component, typename Archive>
		std::enable_if_t<(sizeof...(Component) > 1), const Snapshot &>
			component (Archive &archive) const {
			using accumulator_type = int[];
			accumulator_type accumulator = { 0, (component<Component> (archive), 0)... };
			(void)accumulator;
			return *this;
		}

		/**
		 * @brief Puts aside the given components for the entities in a range.
		 *
		 * Each instance is serialized together with the entity to which it belongs.
		 * Entities are serialized along with their versions.
		 *
		 * @tparam Component Types of components to serialize.
		 * @tparam Archive Type of output archive.
		 * @tparam It Type of input iterator.
		 * @param archive A valid reference to an output archive.
		 * @param first An iterator to the first element of the range to serialize.
		 * @param last An iterator past the last element of the range to serialize.
		 * @return An object of this type to continue creating the snapshot.
		 */
		template<typename... Component, typename Archive, typename It>
		const Snapshot & component (Archive &archive, It first, It last) const {
			component<Component...> (archive, first, last, std::make_index_sequence<sizeof...(Component)>{});
			return *this;
		}

		/**
		* @brief Puts aside the given tag.
		*
		* Each instance is serialized together with the entity to which it belongs.
		* Entities are serialized along with their versions.
		*
		* @tparam Tag Type of tag to serialize.
		* @tparam Archive Type of output archive.
		* @param archive A valid reference to an output archive.
		* @return An object of this type to continue creating the snapshot.
		*/
		template<typename Tag, typename Archive>
		const Snapshot & tag (Archive &archive) const {
			const bool has = registry.template has<Tag> ();

			// numerical length is forced for tags to facilitate loading
			archive (has ? Entity (1) : Entity{});

			if (has) {
				archive (registry.template attachee<Tag> (), registry.template get<Tag> ());
			}

			return *this;
		}

		/**
		 * @brief Puts aside the given tags.
		 *
		 * Each instance is serialized together with the entity to which it belongs.
		 * Entities are serialized along with their versions.
		 *
		 * @tparam Tag Types of tags to serialize.
		 * @tparam Archive Type of output archive.
		 * @param archive A valid reference to an output archive.
		 * @return An object of this type to continue creating the snapshot.
		 */
		template<typename... Tag, typename Archive>
		std::enable_if_t<(sizeof...(Tag) > 1), const Snapshot &>
			tag (Archive &archive) const {
			using accumulator_type = int[];
			accumulator_type accumulator = { 0, (tag<Tag> (archive), 0)... };
			(void)accumulator;
			return *this;
		}

		private:
			const Registry<Entity> &registry;
			const Entity seed;
			follow_fn_type *follow;

	};

}