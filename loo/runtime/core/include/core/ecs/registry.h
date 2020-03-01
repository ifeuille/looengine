#pragma once

#include <tuple>
#include <vector>
#include <memory>
#include <utility>
#include <cstddef>
#include <cstdint>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include "core/ecs/config.h"
#include "core/ecs/algorithm.h"
#include "core/ecs/family.h"
#include "core/ecs/sigh.h"
#include "core/ecs/attachee.h"
#include "core/ecs/entity.h"
#include "core/ecs/ecs_traits.h"
#include "core/ecs/snapshot.h"
#include "core/ecs/sparse_set.h"
#include "core/ecs/utility.h"
#include "core/ecs/view.h"

namespace looecs
{
	/**
	 * @brief Fast and reliable entity-component system.
	 *
	 * The registry is the core class of the entity-component framework.<br/>
	 * It stores entities and arranges pools of components on a per request basis.
	 * By means of a registry, users can manage entities and components and thus
	 * create views to iterate them.
	 *
	 * @tparam Entity A valid entity type (see ecs_traits for more details).
	 */
	template<typename Entity>
	class Registry {
		using tag_family = Family<struct InternalRegistryTagFamily>;
		using component_family = Family<struct InternalRegistryComponentFamily>;
		using handler_family = Family<struct InternalRegistryHandlerFamily>;
		using signal_type = SigH<void (Registry &, const Entity)>;
		using traits_type = ecs_traits<Entity>;

		template<typename Component>
		struct Pool : SparseSet<Entity, Component> {
			Pool (Registry *registry) ECS_NOEXCEPT
				: registry{ registry }
			{}

			template<typename... Args>
			Component & construct (const Entity entity, Args &&... args) {
				auto &component = SparseSet<Entity, Component>::construct (entity, std::forward<Args> (args)...);
				ctor.publish (*registry, entity);
				return component;
			}

			void destroy (const Entity entity) override {
				dtor.publish (*registry, entity);
				SparseSet<Entity, Component>::destroy (entity);
			}

			typename signal_type::sink_type construction () ECS_NOEXCEPT {
				return ctor.sink ();
			}

			typename signal_type::sink_type destruction () ECS_NOEXCEPT {
				return dtor.sink ();
			}

		private:
			Registry *registry;
			signal_type ctor;
			signal_type dtor;
		};

		template<typename Tag>
		struct Attaching : Attachee<Entity, Tag> {
			Attaching (Registry *registry)
				: registry{ registry }
			{}

			template<typename... Args>
			Tag & construct (const Entity entity, Args &&... args) ECS_NOEXCEPT {
				auto &tag = Attachee<Entity, Tag>::construct (entity, std::forward<Args> (args)...);
				ctor.publish (*registry, entity);
				return tag;
			}

			void destroy () ECS_NOEXCEPT override {
				dtor.publish (*registry, Attachee<Entity>::get ());
				Attachee<Entity, Tag>::destroy ();
			}

			Entity move (const Entity entity) ECS_NOEXCEPT {
				const auto owner = Attachee<Entity>::get ();
				dtor.publish (*registry, owner);
				Attachee<Entity, Tag>::move (entity);
				ctor.publish (*registry, entity);
				return owner;
			}

			typename signal_type::sink_type construction () ECS_NOEXCEPT {
				return ctor.sink ();
			}

			typename signal_type::sink_type destruction () ECS_NOEXCEPT {
				return dtor.sink ();
			}

		private:
			Registry *registry;
			signal_type ctor;
			signal_type dtor;
		};

		template<typename handler_family::family_type (*Type)(), typename... Component>
		static void creating (Registry &registry, const Entity entity) {
			if (registry.has<Component...> (entity)) {
				registry.handlers[Type ()]->construct (entity);
			}
		}

		template<typename... Component>
		static void destroying (Registry &registry, const Entity entity) {
			auto &handler = *registry.handlers[handler_family::type<Component...> ()];
			return handler.has (entity) ? handler.destroy (entity) : void ();
		}

		template<typename Tag>
		inline bool managed (tag_t) const ECS_NOEXCEPT {
			const auto ttype = tag_family::type<Tag> ();
			return ttype < tags.size () && tags[ttype];
		}

		template<typename Component>
		inline bool managed () const ECS_NOEXCEPT {
			const auto ctype = component_family::type<Component> ();
			return ctype < pools.size () && pools[ctype];
		}

		template<typename Tag>
		inline const Attaching<Tag> & pool (tag_t) const ECS_NOEXCEPT {
			assert (managed<Tag> (tag_t{}));
			return static_cast<const Attaching<Tag> &>(*tags[tag_family::type<Tag> ()]);
		}

		template<typename Tag>
		inline Attaching<Tag> & pool (tag_t) ECS_NOEXCEPT {
			return const_cast<Attaching<Tag> &>(const_cast<const Registry *>(this)->pool<Tag> (tag_t{}));
		}

		template<typename Component>
		inline const Pool<Component> & pool () const ECS_NOEXCEPT {
			assert (managed<Component> ());
			return static_cast<const Pool<Component> &>(*pools[component_family::type<Component> ()]);
		}

		template<typename Component>
		inline Pool<Component> & pool () ECS_NOEXCEPT {
			return const_cast<Pool<Component> &>(const_cast<const Registry *>(this)->pool<Component> ());
		}

		template<typename Comp, std::size_t Pivot, typename... Component, std::size_t... Indexes>
		void connect (std::index_sequence<Indexes...>) {
			pool<Comp> ().construction ().template connect<&Registry::creating<&handler_family::type<Component...>, std::tuple_element_t<(Indexes < Pivot ? Indexes : (Indexes + 1)), std::tuple<Component...>>...>> ();
			pool<Comp> ().destruction ().template connect<&Registry::destroying<Component...>> ();
		}

		template<typename... Component, std::size_t... Indexes>
		void connect (std::index_sequence<Indexes...>) {
			using accumulator_type = int[];
			accumulator_type accumulator = { (assure<Component> (), connect<Component, Indexes, Component...> (std::make_index_sequence<sizeof...(Component) - 1>{}), 0)... };
			(void)accumulator;
		}

		template<typename Comp, std::size_t Pivot, typename... Component, std::size_t... Indexes>
		void disconnect (std::index_sequence<Indexes...>) {
			pool<Comp> ().construction ().template disconnect<&Registry::creating<&handler_family::type<Component...>, std::tuple_element_t<(Indexes < Pivot ? Indexes : (Indexes + 1)), std::tuple<Component...>>...>> ();
			pool<Comp> ().destruction ().template disconnect<&Registry::destroying<Component...>> ();
		}

		template<typename... Component, std::size_t... Indexes>
		void disconnect (std::index_sequence<Indexes...>) {
			using accumulator_type = int[];
			// if a set exists, pools have already been created for it
			accumulator_type accumulator = { (disconnect<Component, Indexes, Component...> (std::make_index_sequence<sizeof...(Component) - 1>{}), 0)... };
			(void)accumulator;
		}

		template<typename Component>
		void assure () {
			const auto ctype = component_family::type<Component> ();

			if (!(ctype < pools.size ())) {
				pools.resize (ctype + 1);
			}

			if (!pools[ctype]) {
				pools[ctype] = std::make_unique<Pool<Component>> (this);
			}
		}

		template<typename Tag>
		void assure (tag_t) {
			const auto ttype = tag_family::type<Tag> ();

			if (!(ttype < tags.size ())) {
				tags.resize (ttype + 1);
			}

			if (!tags[ttype]) {
				tags[ttype] = std::make_unique<Attaching<Tag>> (this);
			}
		}

	public:
		/*! @brief Underlying entity identifier. */
		using entity_type = typename traits_type::entity_type;
		/*! @brief Underlying version type. */
		using version_type = typename traits_type::version_type;
		/*! @brief Unsigned integer type. */
		using size_type = std::size_t;
		/*! @brief Unsigned integer type. */
		using tag_type = typename tag_family::family_type;
		/*! @brief Unsigned integer type. */
		using component_type = typename component_family::family_type;
		/*! @brief Type of sink for the given component. */
		using sink_type = typename signal_type::sink_type;

		/*! @brief Default constructor. */
		Registry () = default;

		/*! @brief Copying a registry isn't allowed. */
		Registry (const Registry &) = delete;
		/*! @brief Default move constructor. */
		Registry (Registry &&) = default;

		/*! @brief Copying a registry isn't allowed. @return This registry. */
		Registry & operator=(const Registry &) = delete;
		/*! @brief Default move assignment operator. @return This registry. */
		Registry & operator=(Registry &&) = default;

		template<typename Tag>
		static tag_type type (tag_t) ECS_NOEXCEPT {
			return tag_family::type<Tag> ();
		}

		template<typename Component>
		static component_type type () ECS_NOEXCEPT {
			return component_family::type<Component> ();
		}

		template<typename Component>
		size_type size () const ECS_NOEXCEPT {
			return managed<Component> () ? pool<Component> ().size () : size_type{};
		}

		size_type size () const ECS_NOEXCEPT {
			return entities.size ();
		}

		size_type alive () const ECS_NOEXCEPT {
			return entities.size () - available;
		}

		template<typename Component>
		void reserve (const size_type cap) {
			assure<Component> ();
			pool<Component> ().reserve (cap);
		}

		void reserve (const size_type cap) {
			entities.reserve (cap);
		}

		template<typename Component>
		size_type capacity () const ECS_NOEXCEPT {
			return managed<Component> () ? pool<Component> ().capacity () : size_type{};
		}

		size_type capacity () const ECS_NOEXCEPT {
			return entities.capacity ();
		}

		template<typename Component>
		bool empty () const ECS_NOEXCEPT {
			return !managed<Component> () || pool<Component> ().empty ();
		}

		bool empty () const ECS_NOEXCEPT {
			return entities.size () == available;
		}

		template<typename Component>
		const Component * raw () const ECS_NOEXCEPT {
			return managed<Component> () ? pool<Component> ().raw () : nullptr;
		}

		template<typename Component>
		inline Component * raw () ECS_NOEXCEPT {
			return const_cast<Component *>(const_cast<const Registry *>(this)->raw<Component> ());
		}

		template<typename Component>
		const entity_type * data () const ECS_NOEXCEPT {
			return managed<Component> () ? pool<Component> ().data () : nullptr;
		}

		bool valid (const entity_type entity) const ECS_NOEXCEPT {
			const auto pos = size_type (entity & traits_type::entity_mask);
			return (pos < entities.size () && entities[pos] == entity);
		}

		bool fast (const entity_type entity) const ECS_NOEXCEPT {
			const auto pos = size_type (entity & traits_type::entity_mask);
			assert (pos < entities.size ());
			return (entities[pos] == entity);
		}


		version_type version (const entity_type entity) const ECS_NOEXCEPT {
			return version_type (entity >> traits_type::entity_shift);
		}

		version_type current (const entity_type entity) const ECS_NOEXCEPT {
			const auto pos = size_type (entity & traits_type::entity_mask);
			assert (pos < entities.size ());
			return version_type (entities[pos] >> traits_type::entity_shift);
		}

		entity_type create () {
			entity_type entity;

			if (available) {
				const auto entt = next;
				const auto version = entities[entt] & (traits_type::version_mask << traits_type::entity_shift);
				next = entities[entt] & traits_type::entity_mask;
				entity = entt | version;
				entities[entt] = entity;
				--available;
			}
			else {
				entity = entity_type (entities.size ());
				entities.push_back (entity);
				// traits_type::entity_mask is reserved to allow for null identifiers
				assert (entity < traits_type::entity_mask);
			}

			return entity;
		}

		template<typename Tag>
		void destroy (tag_t) {
			return has<Tag> () ? destroy (attachee<Tag> ()) : void ();
		}


		void destroy (const entity_type entity) {
			assert (valid (entity));

			for (auto pos = pools.size (); pos; --pos) {
				auto &cpool = pools[pos - 1];

				if (cpool && cpool->has (entity)) {
					cpool->destroy (entity);
				}
			};

			for (auto pos = tags.size (); pos; --pos) {
				auto &tag = tags[pos - 1];

				if (tag && tag->get () == entity) {
					tag->destroy ();
				}
			};

			// just a way to protect users from listeners that attach components
			assert (orphan (entity));

			// lengthens the implicit list of destroyed entities
			const auto entt = entity & traits_type::entity_mask;
			const auto version = ((entity >> traits_type::entity_shift) + 1) << traits_type::entity_shift;
			const auto node = (available ? next : ((entt + 1) & traits_type::entity_mask)) | version;
			entities[entt] = node;
			next = entt;
			++available;
		}

		template<typename... Component, typename... Type>
		void destroy (Type...) {
			for (const auto entity : view<Component...> (Type{}...)) {
				destroy (entity);
			}
		}

		template<typename Tag, typename... Args>
		Tag & assign (tag_t, const entity_type entity, Args &&... args) {
			assert (valid (entity));
			assert (!has<Tag> ());
			assure<Tag> (tag_t{});
			return pool<Tag> (tag_t{}).construct (entity, std::forward<Args> (args)...);
		}

		template<typename Component, typename... Args>
		Component & assign (const entity_type entity, Args &&... args) {
			assert (valid (entity));
			assure<Component> ();
			return pool<Component> ().construct (entity, std::forward<Args> (args)...);
		}

		template<typename Tag>
		void remove () {
			return has<Tag> () ? pool<Tag> (tag_t{}).destroy () : void ();
		}
		
		template<typename Component>
		void remove (const entity_type entity) {
			assert (valid (entity));
			assert (managed<Component> ());
			pool<Component> ().destroy (entity);
		}

		template<typename Tag>
		bool has () const ECS_NOEXCEPT {
			return managed<Tag> (tag_t{}) && tags[tag_family::type<Tag> ()]->get () != null;
		}

		template<typename Tag>
		bool has (tag_t, const entity_type entity) const ECS_NOEXCEPT {
			return has<Tag> () && attachee<Tag> () == entity;
		}

		template<typename... Component>
		bool has (const entity_type entity) const ECS_NOEXCEPT {
			assert (valid (entity));
			bool all = true;
			using accumulator_type = bool[];
			accumulator_type accumulator = { all, (all = all && managed<Component> () && pool<Component> ().has (entity))... };
			(void)accumulator;
			return all;
		}

		template<typename Tag>
		const Tag & get () const ECS_NOEXCEPT {
			assert (has<Tag> ());
			return pool<Tag> (tag_t{}).get ();
		}

		template<typename Tag>
		inline Tag & get () ECS_NOEXCEPT {
			return const_cast<Tag &>(const_cast<const Registry *>(this)->get<Tag> ());
		}

		template<typename Component>
		const Component & get (const entity_type entity) const ECS_NOEXCEPT {
			assert (valid (entity));
			assert (managed<Component> ());
			return pool<Component> ().get (entity);
		}

		template<typename Component>
		inline Component & get (const entity_type entity) ECS_NOEXCEPT {
			return const_cast<Component &>(const_cast<const Registry *>(this)->get<Component> (entity));
		}

		template<typename... Component>
		inline std::enable_if_t<(sizeof...(Component) > 1), std::tuple<const Component &...>>
			get (const entity_type entity) const ECS_NOEXCEPT {
			return std::tuple<const Component &...>{get<Component> (entity)...};
		}

		template<typename... Component>
		inline std::enable_if_t<(sizeof...(Component) > 1), std::tuple<Component &...>>
			get (const entity_type entity) ECS_NOEXCEPT {
			return std::tuple<Component &...>{get<Component> (entity)...};
		}

		template<typename Tag, typename... Args>
		Tag & replace (tag_t, Args &&... args) {
			return (get<Tag> () = Tag{ std::forward<Args> (args)... });
		}

		template<typename Component, typename... Args>
		Component & replace (const entity_type entity, Args &&... args) {
			return (get<Component> (entity) = Component{ std::forward<Args> (args)... });
		}

		template<typename Tag>
		entity_type move (const entity_type entity) ECS_NOEXCEPT {
			assert (valid (entity));
			assert (has<Tag> ());
			return pool<Tag> (tag_t{}).move (entity);
		}

		template<typename Tag>
		entity_type attachee () const ECS_NOEXCEPT {
			return managed<Tag> (tag_t{}) ? tags[tag_family::type<Tag> ()]->get () : null;
		}

		template<typename Component, typename... Args>
		Component & accommodate (const entity_type entity, Args &&... args) {
			assure<Component> ();
			auto &cpool = pool<Component> ();

			return cpool.has (entity)
				? cpool.get (entity) = Component{ std::forward<Args> (args)... }
			: cpool.construct (entity, std::forward<Args> (args)...);
		}

		template<typename Tag>
		sink_type construction (tag_t) ECS_NOEXCEPT {
			assure<Tag> (tag_t{});
			return pool<Tag> (tag_t{}).construction ();
		}

		template<typename Component>
		sink_type construction () ECS_NOEXCEPT {
			assure<Component> ();
			return pool<Component> ().construction ();
		}

		template<typename Tag>
		sink_type destruction (tag_t) ECS_NOEXCEPT {
			assure<Tag> (tag_t{});
			return pool<Tag> (tag_t{}).destruction ();
		}

		template<typename Component>
		sink_type destruction () ECS_NOEXCEPT {
			assure<Component> ();
			return pool<Component> ().destruction ();
		}

		template<typename Component, typename Compare, typename Sort = StdSort, typename... Args>
		void sort (Compare compare, Sort sort = Sort{}, Args &&... args) {
			assure<Component> ();
			pool<Component> ().sort (std::move (compare), std::move (sort), std::forward<Args> (args)...);
		}

		template<typename To, typename From>
		void sort () {
			assure<To> ();
			assure<From> ();
			pool<To> ().respect (pool<From> ());
		}

		template<typename Component>
		void reset (const entity_type entity) {
			assert (valid (entity));
			assure<Component> ();
			auto &cpool = pool<Component> ();

			if (cpool.has (entity)) {
				cpool.destroy (entity);
			}
		}

		template<typename Component>
		void reset () {
			assure<Component> ();
			auto &cpool = pool<Component> ();

			for (const auto entity : static_cast<SparseSet<Entity> &>(cpool)) {
				cpool.destroy (entity);
			}
		}

		void reset () {
			each ([this](const auto entity) {
				// useless this-> used to suppress a warning with clang
				this->destroy (entity);
			});
		}

		template<typename Func>
		void each (Func func) const {
			if (available) {
				for (auto pos = entities.size (); pos; --pos) {
					const auto curr = entity_type (pos - 1);
					const auto entity = entities[curr];
					const auto entt = entity & traits_type::entity_mask;

					if (curr == entt) {
						func (entity);
					}
				}
			}
			else {
				for (auto pos = entities.size (); pos; --pos) {
					func (entities[pos - 1]);
				}
			}
		}

		bool orphan (const entity_type entity) const {
			assert (valid (entity));
			bool orphan = true;

			for (std::size_t i = 0; i < pools.size () && orphan; ++i) {
				const auto &cpool = pools[i];
				orphan = !(cpool && cpool->has (entity));
			}

			for (std::size_t i = 0; i < tags.size () && orphan; ++i) {
				const auto &tag = tags[i];
				orphan = !(tag && (tag->get () == entity));
			}

			return orphan;
		}

		template<typename Func>
		void orphans (Func func) const {
			each ([func = std::move (func), this] (const auto entity) {
				if (orphan (entity)) {
					func (entity);
				}
			});
		}

		template<typename... Component>
		View<Entity, Component...> view () {
			return View<Entity, Component...>{(assure<Component> (), pool<Component> ())...};
		}

		template<typename... Component>
		void prepare () {
			static_assert(sizeof...(Component) > 1, "!");
			const auto htype = handler_family::type<Component...> ();

			if (!(htype < handlers.size ())) {
				handlers.resize (htype + 1);
			}

			if (!handlers[htype]) {
				connect<Component...> (std::make_index_sequence<sizeof...(Component)>{});
				handlers[htype] = std::make_unique<SparseSet<entity_type>> ();
				auto &handler = *handlers[htype];

				for (auto entity : view<Component...> ()) {
					handler.construct (entity);
				}
			}
		}

		template<typename... Component>
		void discard () {
			if (contains<Component...> ()) {
				disconnect<Component...> (std::make_index_sequence<sizeof...(Component)>{});
				handlers[handler_family::type<Component...> ()].reset ();
			}
		}

		template<typename... Component>
		bool contains () const ECS_NOEXCEPT {
			static_assert(sizeof...(Component) > 1, "!");
			const auto htype = handler_family::type<Component...> ();
			return (htype < handlers.size () && handlers[htype]);
		}

		template<typename... Component>
		PersistentView<Entity, Component...> view (persistent_t) {
			prepare<Component...> ();
			const auto htype = handler_family::type<Component...> ();
			return PersistentView<Entity, Component...>{*handlers[htype], (assure<Component> (), pool<Component> ())...};
		}

		template<typename Component>
		RawView<Entity, Component> view (raw_t) {
			assure<Component> ();
			return RawView<Entity, Component>{pool<Component> ()};
		}

		template<typename It>
		RuntimeView<Entity> view (It first, It last) {
			static_assert(std::is_convertible<typename std::iterator_traits<It>::value_type, component_type>::value, "!");
			std::vector<const SparseSet<Entity> *> set (last - first);

			std::transform (first, last, set.begin (), [this](const component_type ctype) {
				return ctype < pools.size () ? pools[ctype].get () : nullptr;
			});

			return RuntimeView<Entity>{std::move (set)};
		}

		Snapshot<Entity> snapshot () const ECS_NOEXCEPT {
			using follow_fn_type = entity_type (const Registry &, const entity_type);
			const entity_type seed = available ? (next | (entities[next] & (traits_type::version_mask << traits_type::entity_shift))) : next;

			follow_fn_type *follow = [](const Registry &registry, const entity_type entity) -> entity_type {
				const auto &entities = registry.entities;
				const auto entt = entity & traits_type::entity_mask;
				const auto next = entities[entt] & traits_type::entity_mask;
				return (next | (entities[next] & (traits_type::version_mask << traits_type::entity_shift)));
			};

			return { *this, seed, follow };
		}

		SnapshotLoader<Entity> restore () ECS_NOEXCEPT {
			using assure_fn_type = void (Registry &, const entity_type, const bool);

			assure_fn_type *assure = [](Registry &registry, const entity_type entity, const bool destroyed) {
				using promotion_type = std::conditional_t<sizeof (size_type) >= sizeof (entity_type), size_type, entity_type>;
				// explicit promotion to avoid warnings with std::uint16_t
				const auto entt = promotion_type{ entity } &traits_type::entity_mask;
				auto &entities = registry.entities;

				if (!(entt < entities.size ())) {
					auto curr = entities.size ();
					entities.resize (entt + 1);
					std::iota (entities.data () + curr, entities.data () + entt, entity_type (curr));
				}

				entities[entt] = entity;

				if (destroyed) {
					registry.destroy (entity);
					const auto version = entity & (traits_type::version_mask << traits_type::entity_shift);
					entities[entt] = ((entities[entt] & traits_type::entity_mask) | version);
				}
			};

			return { (*this = {}), assure };
		}

	private:
		std::vector<std::unique_ptr<SparseSet<Entity>>> handlers;
		std::vector<std::unique_ptr<SparseSet<Entity>>> pools;
		std::vector<std::unique_ptr<Attachee<Entity>>> tags;
		std::vector<entity_type> entities;
		size_type available{};
		entity_type next{};
	};


/**
 * @brief Default registry class.
 *
 * The default registry is the best choice for almost all the applications.<br/>
 * Users should have a really good reason to choose something different.
 */
using DefaultRegistry = Registry<std::uint32_t>;

}
