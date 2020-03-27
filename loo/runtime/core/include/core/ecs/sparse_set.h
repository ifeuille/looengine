#pragma once
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>
#include <cstddef>
#include <cassert>
#include <type_traits>

#include "core/ecs/config.h"
#include "core/ecs/algorithm.h"
#include "core/ecs/ecs_traits.h"
#include "core/ecs/entity.h"

namespace looecs
{
	/**
	 * @brief Sparse set.
	 *
	 * Primary template isn't defined on purpose. All the specializations give a
	 * compile-time error, but for a few reasonable cases.
	 */
	template<typename...>
	class SparseSet;

	/**
	 * @brief Basic sparse set implementation.
	 *
	 * Sparse set or packed array or whatever is the name users give it.<br/>
	 * Two arrays: an _external_ one and an _internal_ one; a _sparse_ one and a
	 * _packed_ one; one used for direct access through contiguous memory, the other
	 * one used to get the data through an extra level of indirection.<br/>
	 * This is largely used by the Registry to offer users the fastest access ever
	 * to the components. View and PersistentView are entirely designed around
	 * sparse sets.
	 *
	 * This type of data structure is widely documented in the literature and on the
	 * web. This is nothing more than a customized implementation suitable for the
	 * purpose of the framework.
	 *
	 * @note
	 * There are no guarantees that entities are returned in the insertion order
	 * when iterate a sparse set. Do not make assumption on the order in any case.
	 *
	 * @note
	 * Internal data structures arrange elements to maximize performance. Because of
	 * that, there are no guarantees that elements have the expected order when
	 * iterate directly the internal packed array (see `data` and `size` member
	 * functions for that). Use `begin` and `end` instead.
	 *
	 * @tparam Entity A valid entity type (see entt_traits for more details).
	 */
	template<typename Entity>
	class SparseSet<Entity>
	{
		using traits_type = ecs_traits<Entity>;

		class Iterator final
		{
			friend class SparseSet<Entity>;

			using direct_type = const std::vector<Entity>;
			using index_type = typename traits_type::difference_type;

			Iterator (direct_type* direct, index_type index)ECS_NOEXCEPT
				:direct{ direct }£¬index {index}{}

		public:
			using difference_type = index_type;
			using value_type = const Entity;
			using pointer = value_type * ;
			using reference = value_type & ;
			using iterator_category = std::random_access_iterator_tag;

			Iterator ()ECS_NOEXCEPT = default;

			Iterator (const Iterator&)ECS_NOEXCEPT = default;
			Iterator & operator=(const Iterator &) ECS_NOEXCEPT = default;

			Iterator & operator++() ECS_NOEXCEPT {
				return --index, *this;
			}


			Iterator operator++(int) ECS_NOEXCEPT {
				Iterator orig = *this;
				return ++(*this), orig;
			}

			Iterator & operator--() ECS_NOEXCEPT {
				return ++index, *this;
			}

			Iterator operator--(int) ECS_NOEXCEPT {
				Iterator orig = *this;
				return --(*this), orig;
			}

			Iterator & operator+=(const difference_type value) ECS_NOEXCEPT {
				index -= value;
				return *this;
			}

			Iterator operator+(const difference_type value) const ECS_NOEXCEPT {
				return Iterator{ direct, index - value };
			}

			inline Iterator & operator-=(const difference_type value) ECS_NOEXCEPT {
				return (*this += -value);
			}

			inline Iterator operator-(const difference_type value) const ECS_NOEXCEPT {
				return (*this + -value);
			}

			difference_type operator-(const Iterator &other) const ECS_NOEXCEPT {
				return other.index - index;
			}

			reference operator[](const difference_type value) const ECS_NOEXCEPT {
				const auto pos = size_type (index - value - 1);
				return (*direct)[pos];
			}

			bool operator==(const Iterator &other) const ECS_NOEXCEPT {
				return other.index == index;
			}

			inline bool operator!=(const Iterator &other) const ECS_NOEXCEPT {
				return !(*this == other);
			}

			bool operator<(const Iterator &other) const ECS_NOEXCEPT {
				return index > other.index;
			}

			bool operator>(const Iterator &other) const ECS_NOEXCEPT {
				return index < other.index;
			}

			inline bool operator<=(const Iterator &other) const ECS_NOEXCEPT {
				return !(*this > other);
			}

			inline bool operator>=(const Iterator &other) const ECS_NOEXCEPT {
				return !(*this < other);
			}

			pointer operator->() const ECS_NOEXCEPT {
				const auto pos = size_type (index - 1);
				return &(*direct)[pos];
			}

			inline reference operator*() const ECS_NOEXCEPT {
				return *operator->();
			}

		private:
			direct_type *direct;
			index_type index;

		};

	public:
		/*! @brief Underlying entity identifier. */
		using entity_type = Entity;
		/*! @brief Unsigned integer type. */
		using size_type = std::size_t;
		/*! @brief Input iterator type. */
		using iterator_type = Iterator;
		/*! @brief Constant input iterator type. */
		using const_iterator_type = Iterator;

		/*! @brief Default constructor. */
		SparseSet () ECS_NOEXCEPT = default;

		/*! @brief Default destructor. */
		virtual ~SparseSet () ECS_NOEXCEPT = default;

		/*! @brief Copying a sparse set isn't allowed. */
		SparseSet (const SparseSet &) = delete;
		/*! @brief Default move constructor. */
		SparseSet (SparseSet &&) = default;

		/*! @brief Copying a sparse set isn't allowed. @return This sparse set. */
		SparseSet & operator=(const SparseSet &) = delete;
		/*! @brief Default move assignment operator. @return This sparse set. */
		SparseSet & operator=(SparseSet &&) = default;

		/**
		* @brief Increases the capacity of a sparse set.
		*
		* If the new capacity is greater than the current capacity, new storage is
		* allocated, otherwise the method does nothing.
		*
		* @param cap Desired capacity.
		*/
		void reserve (const size_type cap) {
			direct.reserve (cap);
		}

		/**
		* @brief Returns the number of elements that a sparse set has currently
		* allocated space for.
		* @return Capacity of the sparse set.
		*/
		size_type capacity () const ECS_NOEXCEPT {
			return direct.capacity ();
		}

		size_type extent () const ECS_NOEXCEPT {
			return reverse.size ();
		}

		size_type size () const ECS_NOEXCEPT {
			return direct.size ();
		}

		bool empty () const ECS_NOEXCEPT {
			return direct.empty ();
		}

		const entity_type * data () const ECS_NOEXCEPT {
			return direct.data ();
		}

		const_iterator_type cbegin () const ECS_NOEXCEPT {
			const typename traits_type::difference_type pos = direct.size ();
			return const_iterator_type{ &direct, pos };
		}

		inline const_iterator_type begin () const ECS_NOEXCEPT {
			return cbegin ();
		}

		inline iterator_type begin () ECS_NOEXCEPT {
			return cbegin ();
		}
		
		const_iterator_type cend () const ECS_NOEXCEPT {
			return const_iterator_type{ &direct, {} };
		}

		inline const_iterator_type end () const ECS_NOEXCEPT {
			return cend ();
		}

		inline const entity_type & operator[](const size_type pos) const ECS_NOEXCEPT {
			return cbegin ()[pos];
		}

		/**
		 * @brief Checks if a sparse set contains an entity.
		 * @param entity A valid entity identifier.
		 * @return True if the sparse set contains the entity, false otherwise.
		 */
		bool has (const entity_type entity) const ECS_NOEXCEPT {
			const auto pos = size_type (entity & traits_type::entity_mask);
			// testing against null permits to avoid accessing the direct vector
			return (pos < reverse.size ()) && (reverse[pos] != null);
		}
		
		/**
		 * @brief Checks if a sparse set contains an entity (unsafe).
		 *
		 * Alternative version of `has`. It accesses the underlying data structures
		 * without bounds checking and thus it's both unsafe and risky to use.<br/>
		 * You should not invoke directly this function unless you know exactly what
		 * you are doing. Prefer the `has` member function instead.
		 *
		 * @warning
		 * Attempting to use an entity that doesn't belong to the sparse set can
		 * result in undefined behavior.<br/>
		 * An assertion will abort the execution at runtime in debug mode in case of
		 * bounds violation.
		 *
		 * @param entity A valid entity identifier.
		 * @return True if the sparse set contains the entity, false otherwise.
		 */
		bool fast (const entity_type entity) const ECS_NOEXCEPT {
			const auto pos = size_type (entity & traits_type::entity_mask);
			assert (pos < reverse.size ());
			// testing against null permits to avoid accessing the direct vector
			return (reverse[pos] != null);
		}

		size_type get (const entity_type entity) const ECS_NOEXCEPT {
			assert (has (entity));
			const auto pos = size_type (entity & traits_type::entity_mask);
			return size_type (reverse[pos]);
		}

		void construct (const entity_type entity) {
			assert (!has (entity));
			const auto pos = size_type (entity & traits_type::entity_mask);

			if (!(pos < reverse.size ())) {
				// null is safe in all cases for our purposes
				reverse.resize (pos + 1, null);
			}

			reverse[pos] = entity_type (direct.size ());
			direct.push_back (entity);
		}

		virtual void destroy (const entity_type entity) {
			assert (has (entity));
			const auto back = direct.back ();
			auto &candidate = reverse[size_type (entity & traits_type::entity_mask)];
			// swapping isn't required here, we are getting rid of the last element
			reverse[back & traits_type::entity_mask] = candidate;
			direct[size_type (candidate)] = back;
			candidate = null;
			direct.pop_back ();
		}

		/**
		* @brief Sort entities according to their order in another sparse set.
		*
		* Entities that are part of both the sparse sets are ordered internally
		* according to the order they have in `other`. All the other entities goes
		* to the end of the list and there are no guarantess on their order.<br/>
		* In other terms, this function can be used to impose the same order on two
		* sets by using one of them as a master and the other one as a slave.
		*
		* Iterating the sparse set with a couple of iterators returns elements in
		* the expected order after a call to `respect`. See `begin` and `end` for
		* more details.
		*
		* @note
		* Attempting to iterate elements using the raw pointer returned by `data`
		* gives no guarantees on the order, even though `respect` has been invoked.
		*
		* @param other The sparse sets that imposes the order of the entities.
		*/
		void respect (const SparseSet<Entity> &other) ENTT_NOEXCEPT {
			auto from = other.cbegin ();
			auto to = other.cend ();

			size_type pos = direct.size () - 1;

			while (pos && from != to) {
				if (has (*from)) {
					if (*from != direct[pos]) {
						swap (pos, get (*from));
					}

					--pos;
				}

				++from;
			}
		}

		/**
		 * @brief Resets a sparse set.
		 */
		virtual void reset () {
			reverse.clear ();
			direct.clear ();
		}

	private:
		std::vector<entity_type> reverse;
		std::vector<entity_type> direct;
	};

	/**
	 * @brief Extended sparse set implementation.
	 *
	 * This specialization of a sparse set associates an object to an entity. The
	 * main purpose of this class is to use sparse sets to store components in a
	 * Registry. It guarantees fast access both to the elements and to the entities.
	 *
	 * @note
	 * Entities and objects have the same order. It's guaranteed both in case of raw
	 * access (either to entities or objects) and when using input iterators.
	 *
	 * @note
	 * Internal data structures arrange elements to maximize performance. Because of
	 * that, there are no guarantees that elements have the expected order when
	 * iterate directly the internal packed array (see `raw` and `size` member
	 * functions for that). Use `begin` and `end` instead.
	 *
	 * @sa SparseSet<Entity>
	 *
	 * @tparam Entity A valid entity type (see entt_traits for more details).
	 * @tparam Type Type of objects assigned to the entities.
	 */
	template<typename Entity,typename Type>
	class SparseSet<Entity, Type> :public SparseSet<Entity> 
	{
		using underlying_type = SparseSet<Entity>;
		using traits_type = ecs_traits<Entity>;

		template<bool Const>
		class Iterator final
		{
			friend class SparseSet<Entity, Type>;

			using instance_type = std::conditional_t<Const, const std::vector<Type>>;
			using index_type = typename traits_type::difference_type;

			Iterator (instance_type *instances, index_type index) ECS_NOEXCEPT
				: instances{ instances }, index{ index }
			{}

		public:
			using difference_type = index_type;
			using value_type = std::conditional_t<Const, const Type, Type>;
			using pointer = value_type * ;
			using reference = value_type & ;
			using iterator_category = std::random_access_iterator_tag;

			Iterator () ECS_NOEXCEPT = default;

			Iterator (const Iterator &) ECS_NOEXCEPT = default;
			Iterator & operator=(const Iterator &) ECS_NOEXCEPT = default;

			Iterator & operator++() ECS_NOEXCEPT {
				return --index, *this;
			}

			Iterator operator++(int) ECS_NOEXCEPT {
				Iterator orig = *this;
				return ++(*this), orig;
			}

			Iterator & operator--() ECS_NOEXCEPT {
				return ++index, *this;
			}

			Iterator operator--(int) ECS_NOEXCEPT {
				Iterator orig = *this;
				return --(*this), orig;
			}

			Iterator & operator+=(const difference_type value) ECS_NOEXCEPT {
				index -= value;
				return *this;
			}

			Iterator operator+(const difference_type value) const ECS_NOEXCEPT {
				return Iterator{ instances, index - value };
			}

			inline Iterator & operator-=(const difference_type value) ECS_NOEXCEPT {
				return (*this += -value);
			}

			inline Iterator operator-(const difference_type value) const ECS_NOEXCEPT {
				return (*this + -value);
			}

			difference_type operator-(const Iterator &other) const ENTT_NOEXCEPT {
				return other.index - index;
			}

			reference operator[](const difference_type value) const ECS_NOEXCEPT {
				const auto pos = size_type (index - value - 1);
				return (*instances)[pos];
			}

			bool operator==(const Iterator &other) const ECS_NOEXCEPT {
				return other.index == index;
			}

			inline bool operator!=(const Iterator &other) const ECS_NOEXCEPT {
				return !(*this == other);
			}

			bool operator<(const Iterator &other) const ENTT_NOEXCEPT {
				return index > other.index;
			}

			bool operator>(const Iterator &other) const ECS_NOEXCEPT {
				return index < other.index;
			}

			inline bool operator<=(const Iterator &other) const ECS_NOEXCEPT {
				return !(*this > other);
			}

			inline bool operator>=(const Iterator &other) const ECS_NOEXCEPT {
				return !(*this < other);
			}

			pointer operator->() const ECS_NOEXCEPT {
				const auto pos = size_type (index - 1);
				return &(*instances)[pos];
			}

			inline reference operator*() const ECS_NOEXCEPT {
				return *operator->();
			}


		private:
			instance_type *instances;
			index_type index;

		};

	public:
		/*! @brief Type of the objects associated to the entities. */
		using object_type = Type;
		/*! @brief Underlying entity identifier. */
		using entity_type = typename underlying_type::entity_type;
		/*! @brief Unsigned integer type. */
		using size_type = typename underlying_type::size_type;
		/*! @brief Input iterator type. */
		using iterator_type = Iterator<false>;
		/*! @brief Constant input iterator type. */
		using const_iterator_type = Iterator<true>;

		/*! @brief Default constructor. */
		SparseSet () ECS_NOEXCEPT = default;

		/*! @brief Copying a sparse set isn't allowed. */
		SparseSet (const SparseSet &) = delete;
		/*! @brief Default move constructor. */
		SparseSet (SparseSet &&) = default;

		/*! @brief Copying a sparse set isn't allowed. @return This sparse set. */
		SparseSet & operator=(const SparseSet &) = delete;
		/*! @brief Default move assignment operator. @return This sparse set. */
		SparseSet & operator=(SparseSet &&) = default;

		void reserve (const size_type cap) {
			underlying_type::reserve (cap);
			instances.reserve (cap);
		}
		
		const object_type * raw () const ECS_NOEXCEPT {
			return instances.data ();
		}

		object_type * raw () ECS_NOEXCEPT {
			return instances.data ();
		}

		const_iterator_type cbegin () const ECS_NOEXCEPT {
			const typename traits_type::difference_type pos = instances.size ();
			return const_iterator_type{ &instances, pos };
		}

		inline const_iterator_type begin () const ECS_NOEXCEPT {
			return cbegin ();
		}

		iterator_type begin () ECS_NOEXCEPT {
			const typename traits_type::difference_type pos = instances.size ();
			return iterator_type{ &instances, pos };
		}

		const_iterator_type cend () const ECS_NOEXCEPT {
			return const_iterator_type{ &instances, {} };
		}

		inline const_iterator_type end () const ECS_NOEXCEPT {
			return cend ();
		}

		iterator_type end () ECS_NOEXCEPT {
			return iterator_type{ &instances, {} };
		}

		inline const object_type & operator[](const size_type pos) const ECS_NOEXCEPT {
			return cbegin ()[pos];
		}

		inline object_type & operator[](const size_type pos) ECS_NOEXCEPT {
			return const_cast<object_type &>(const_cast<const SparseSet *>(this)->operator[](pos));
		}

		const object_type & get (const entity_type entity) const ECS_NOEXCEPT {
			return instances[underlying_type::get (entity)];
		}

		inline object_type & get (const entity_type entity) ECS_NOEXCEPT {
			return const_cast<object_type &>(const_cast<const SparseSet *>(this)->get (entity));
		}

		template<typename... Args>
		std::enable_if_t<std::is_constructible<Type, Args...>::value, object_type &>
			construct (const entity_type entity, Args &&... args) {
			underlying_type::construct (entity);
			instances.emplace_back (std::forward<Args> (args)...);
			return instances.back ();
		}

		template<typename... Args>
		std::enable_if_t<!std::is_constructible<Type, Args...>::value, object_type &>
			construct (const entity_type entity, Args &&... args) {
			underlying_type::construct (entity);
			instances.emplace_back (Type{ std::forward<Args> (args)... });
			return instances.back ();
		}

		void destroy (const entity_type entity) override {
			// swapping isn't required here, we are getting rid of the last element
			// however, we must protect ourselves from self assignments (see #37)
			auto tmp = std::move (instances.back ());
			instances[underlying_type::get (entity)] = std::move (tmp);
			instances.pop_back ();
			underlying_type::destroy (entity);
		}

		template<typename Compare, typename Sort = StdSort, typename... Args>
		void sort (Compare compare, Sort sort = Sort{}, Args &&... args) {
			std::vector<size_type> copy (instances.size ());
			std::iota (copy.begin (), copy.end (), 0);

			sort (copy.begin (), copy.end (), [this, compare = std::move (compare)] (const auto lhs, const auto rhs) {
				return compare (const_cast<const object_type &>(instances[rhs]), const_cast<const object_type &>(instances[lhs]));
			}, std::forward<Args> (args)...);

			for (size_type pos = 0, last = copy.size (); pos < last; ++pos) {
				auto curr = pos;
				auto next = copy[curr];

				while (curr != next) {
					const auto lhs = copy[curr];
					const auto rhs = copy[next];
					std::swap (instances[lhs], instances[rhs]);
					underlying_type::swap (lhs, rhs);
					copy[curr] = curr;
					curr = next;
					next = copy[curr];
				}
			}
		}

		void respect (const SparseSet<Entity> &other) ECS_NOEXCEPT {
			auto from = other.cbegin ();
			auto to = other.cend ();

			size_type pos = underlying_type::size () - 1;
			const auto *local = underlying_type::data ();

			while (pos && from != to) {
				const auto curr = *from;

				if (underlying_type::has (curr)) {
					if (curr != *(local + pos)) {
						auto candidate = underlying_type::get (curr);
						std::swap (instances[pos], instances[candidate]);
						underlying_type::swap (pos, candidate);
					}

					--pos;
				}

				++from;
			}
		}

		void reset () override {
			underlying_type::reset ();
			instances.clear ();
		}

	private:
		std::vector<object_type> instances;

	};

}