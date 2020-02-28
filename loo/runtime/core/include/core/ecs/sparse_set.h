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
	template<typename Entity, typename Type>
	class SparseSet<Entity, Type> : public SparseSet<Entity> {
		using underlying_type = SparseSet<Entity>;
		using traits_type = entt_traits<Entity>;

		template<bool Const>
		class Iterator final {
			friend class SparseSet<Entity, Type>;

			using instance_type = std::conditional_t<Const, const std::vector<Type>, std::vector<Type>>;
			using index_type = typename traits_type::difference_type;

			Iterator (instance_type *instances, index_type index) ENTT_NOEXCEPT
				: instances{ instances }, index{ index }
			{}

		public:
			using difference_type = index_type;
			using value_type = std::conditional_t<Const, const Type, Type>;
			using pointer = value_type * ;
			using reference = value_type & ;
			using iterator_category = std::random_access_iterator_tag;

			Iterator () ENTT_NOEXCEPT = default;

			Iterator (const Iterator &) ENTT_NOEXCEPT = default;
			Iterator & operator=(const Iterator &) ENTT_NOEXCEPT = default;

			Iterator & operator++() ENTT_NOEXCEPT {
				return --index, *this;
			}

			Iterator operator++(int) ENTT_NOEXCEPT {
				Iterator orig = *this;
				return ++(*this), orig;
			}

			Iterator & operator--() ENTT_NOEXCEPT {
				return ++index, *this;
			}

			Iterator operator--(int) ENTT_NOEXCEPT {
				Iterator orig = *this;
				return --(*this), orig;
			}

			Iterator & operator+=(const difference_type value) ENTT_NOEXCEPT {
				index -= value;
				return *this;
			}

			Iterator operator+(const difference_type value) const ENTT_NOEXCEPT {
				return Iterator{ instances, index - value };
			}

			inline Iterator & operator-=(const difference_type value) ENTT_NOEXCEPT {
				return (*this += -value);
			}

			inline Iterator operator-(const difference_type value) const ENTT_NOEXCEPT {
				return (*this + -value);
			}

			difference_type operator-(const Iterator &other) const ENTT_NOEXCEPT {
				return other.index - index;
			}

			reference operator[](const difference_type value) const ENTT_NOEXCEPT {
				const auto pos = size_type (index - value - 1);
				return (*instances)[pos];
			}

			bool operator==(const Iterator &other) const ENTT_NOEXCEPT {
				return other.index == index;
			}

			inline bool operator!=(const Iterator &other) const ENTT_NOEXCEPT {
				return !(*this == other);
			}

			bool operator<(const Iterator &other) const ENTT_NOEXCEPT {
				return index > other.index;
			}

			bool operator>(const Iterator &other) const ENTT_NOEXCEPT {
				return index < other.index;
			}

			inline bool operator<=(const Iterator &other) const ENTT_NOEXCEPT {
				return !(*this > other);
			}

			inline bool operator>=(const Iterator &other) const ENTT_NOEXCEPT {
				return !(*this < other);
			}

			pointer operator->() const ENTT_NOEXCEPT {
				const auto pos = size_type (index - 1);
				return &(*instances)[pos];
			}

			inline reference operator*() const ENTT_NOEXCEPT {
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
		SparseSet () ENTT_NOEXCEPT = default;

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
			underlying_type::reserve (cap);
			instances.reserve (cap);
		}

		/**
		 * @brief Direct access to the array of objects.
		 *
		 * The returned pointer is such that range `[raw(), raw() + size()]` is
		 * always a valid range, even if the container is empty.
		 *
		 * @note
		 * There are no guarantees on the order, even though either `sort` or
		 * `respect` has been previously invoked. Internal data structures arrange
		 * elements to maximize performance. Accessing them directly gives a
		 * performance boost but less guarantees. Use `begin` and `end` if you want
		 * to iterate the sparse set in the expected order.
		 *
		 * @return A pointer to the array of objects.
		 */
		const object_type * raw () const ENTT_NOEXCEPT {
			return instances.data ();
		}

		/**
		 * @brief Direct access to the array of objects.
		 *
		 * The returned pointer is such that range `[raw(), raw() + size()]` is
		 * always a valid range, even if the container is empty.
		 *
		 * @note
		 * There are no guarantees on the order, even though either `sort` or
		 * `respect` has been previously invoked. Internal data structures arrange
		 * elements to maximize performance. Accessing them directly gives a
		 * performance boost but less guarantees. Use `begin` and `end` if you want
		 * to iterate the sparse set in the expected order.
		 *
		 * @return A pointer to the array of objects.
		 */
		object_type * raw () ENTT_NOEXCEPT {
			return instances.data ();
		}

		/**
		 * @brief Returns an iterator to the beginning.
		 *
		 * The returned iterator points to the first instance of the given type. If
		 * the sparse set is empty, the returned iterator will be equal to `end()`.
		 *
		 * @note
		 * Input iterators stay true to the order imposed by a call to either `sort`
		 * or `respect`.
		 *
		 * @return An iterator to the first instance of the given type.
		 */
		const_iterator_type cbegin () const ENTT_NOEXCEPT {
			const typename traits_type::difference_type pos = instances.size ();
			return const_iterator_type{ &instances, pos };
		}

		/**
		 * @brief Returns an iterator to the beginning.
		 *
		 * The returned iterator points to the first instance of the given type. If
		 * the sparse set is empty, the returned iterator will be equal to `end()`.
		 *
		 * @note
		 * Input iterators stay true to the order imposed by a call to either `sort`
		 * or `respect`.
		 *
		 * @return An iterator to the first instance of the given type.
		 */
		inline const_iterator_type begin () const ENTT_NOEXCEPT {
			return cbegin ();
		}

		/**
		 * @brief Returns an iterator to the beginning.
		 *
		 * The returned iterator points to the first instance of the given type. If
		 * the sparse set is empty, the returned iterator will be equal to `end()`.
		 *
		 * @note
		 * Input iterators stay true to the order imposed by a call to either `sort`
		 * or `respect`.
		 *
		 * @return An iterator to the first instance of the given type.
		 */
		iterator_type begin () ENTT_NOEXCEPT {
			const typename traits_type::difference_type pos = instances.size ();
			return iterator_type{ &instances, pos };
		}

		/**
		 * @brief Returns an iterator to the end.
		 *
		 * The returned iterator points to the element following the last instance
		 * of the given type. Attempting to dereference the returned iterator
		 * results in undefined behavior.
		 *
		 * @note
		 * Input iterators stay true to the order imposed by a call to either `sort`
		 * or `respect`.
		 *
		 * @return An iterator to the element following the last instance of the
		 * given type.
		 */
		const_iterator_type cend () const ENTT_NOEXCEPT {
			return const_iterator_type{ &instances, {} };
		}

		/**
		 * @brief Returns an iterator to the end.
		 *
		 * The returned iterator points to the element following the last instance
		 * of the given type. Attempting to dereference the returned iterator
		 * results in undefined behavior.
		 *
		 * @note
		 * Input iterators stay true to the order imposed by a call to either `sort`
		 * or `respect`.
		 *
		 * @return An iterator to the element following the last instance of the
		 * given type.
		 */
		inline const_iterator_type end () const ENTT_NOEXCEPT {
			return cend ();
		}

		/**
		 * @brief Returns an iterator to the end.
		 *
		 * The returned iterator points to the element following the last instance
		 * of the given type. Attempting to dereference the returned iterator
		 * results in undefined behavior.
		 *
		 * @note
		 * Input iterators stay true to the order imposed by a call to either `sort`
		 * or `respect`.
		 *
		 * @return An iterator to the element following the last instance of the
		 * given type.
		 */
		iterator_type end () ENTT_NOEXCEPT {
			return iterator_type{ &instances, {} };
		}

		/**
		 * @brief Returns a reference to the element at the given position.
		 * @param pos Position of the element to return.
		 * @return A reference to the requested element.
		 */
		inline const object_type & operator[](const size_type pos) const ENTT_NOEXCEPT {
			return cbegin ()[pos];
		}

		/**
		 * @brief Returns a reference to the element at the given position.
		 * @param pos Position of the element to return.
		 * @return A reference to the requested element.
		 */
		inline object_type & operator[](const size_type pos) ENTT_NOEXCEPT {
			return const_cast<object_type &>(const_cast<const SparseSet *>(this)->operator[](pos));
		}

		/**
		 * @brief Returns the object associated to an entity.
		 *
		 * @warning
		 * Attempting to use an entity that doesn't belong to the sparse set results
		 * in undefined behavior.<br/>
		 * An assertion will abort the execution at runtime in debug mode if the
		 * sparse set doesn't contain the given entity.
		 *
		 * @param entity A valid entity identifier.
		 * @return The object associated to the entity.
		 */
		const object_type & get (const entity_type entity) const ENTT_NOEXCEPT {
			return instances[underlying_type::get (entity)];
		}

		/**
		 * @brief Returns the object associated to an entity.
		 *
		 * @warning
		 * Attempting to use an entity that doesn't belong to the sparse set results
		 * in undefined behavior.<br/>
		 * An assertion will abort the execution at runtime in debug mode if the
		 * sparse set doesn't contain the given entity.
		 *
		 * @param entity A valid entity identifier.
		 * @return The object associated to the entity.
		 */
		inline object_type & get (const entity_type entity) ENTT_NOEXCEPT {
			return const_cast<object_type &>(const_cast<const SparseSet *>(this)->get (entity));
		}

		/**
		 * @brief Assigns an entity to a sparse set and constructs its object.
		 *
		 * @note
		 * _Sfinae'd_ function.<br/>
		 * This version is used for types that can be constructed in place directly.
		 * It doesn't work well with aggregates because of the placement new usually
		 * performed under the hood during an _emplace back_.
		 *
		 * @warning
		 * Attempting to use an entity that already belongs to the sparse set
		 * results in undefined behavior.<br/>
		 * An assertion will abort the execution at runtime in debug mode if the
		 * sparse set already contains the given entity.
		 *
		 * @tparam Args Types of arguments to use to construct the object.
		 * @param entity A valid entity identifier.
		 * @param args Parameters to use to construct an object for the entity.
		 * @return The object associated to the entity.
		 */
		template<typename... Args>
		std::enable_if_t<std::is_constructible<Type, Args...>::value, object_type &>
			construct (const entity_type entity, Args &&... args) {
			underlying_type::construct (entity);
			instances.emplace_back (std::forward<Args> (args)...);
			return instances.back ();
		}

		/**
		 * @brief Assigns an entity to a sparse set and constructs its object.
		 *
		 * @note
		 * _Sfinae'd_ function.<br/>
		 * Fallback for aggregates and types in general that do not work well with a
		 * placement new as performed usually under the hood during an
		 * _emplace back_.
		 *
		 * @warning
		 * Attempting to use an entity that already belongs to the sparse set
		 * results in undefined behavior.<br/>
		 * An assertion will abort the execution at runtime in debug mode if the
		 * sparse set already contains the given entity.
		 *
		 * @tparam Args Types of arguments to use to construct the object.
		 * @param entity A valid entity identifier.
		 * @param args Parameters to use to construct an object for the entity.
		 * @return The object associated to the entity.
		 */
		template<typename... Args>
		std::enable_if_t<!std::is_constructible<Type, Args...>::value, object_type &>
			construct (const entity_type entity, Args &&... args) {
			underlying_type::construct (entity);
			instances.emplace_back (Type{ std::forward<Args> (args)... });
			return instances.back ();
		}

		/**
		 * @brief Removes an entity from a sparse set and destroies its object.
		 *
		 * @warning
		 * Attempting to use an entity that doesn't belong to the sparse set results
		 * in undefined behavior.<br/>
		 * An assertion will abort the execution at runtime in debug mode if the
		 * sparse set doesn't contain the given entity.
		 *
		 * @param entity A valid entity identifier.
		 */
		void destroy (const entity_type entity) override {
			// swapping isn't required here, we are getting rid of the last element
			// however, we must protect ourselves from self assignments (see #37)
			auto tmp = std::move (instances.back ());
			instances[underlying_type::get (entity)] = std::move (tmp);
			instances.pop_back ();
			underlying_type::destroy (entity);
		}

		/**
		 * @brief Sort components according to the given comparison function.
		 *
		 * Sort the elements so that iterating the sparse set with a couple of
		 * iterators returns them in the expected order. See `begin` and `end` for
		 * more details.
		 *
		 * The comparison function object must return `true` if the first element
		 * is _less_ than the second one, `false` otherwise. The signature of the
		 * comparison function should be equivalent to the following:
		 *
		 * @code{.cpp}
		 * bool(const Type &, const Type &)
		 * @endcode
		 *
		 * Moreover, the comparison function object shall induce a
		 * _strict weak ordering_ on the values.
		 *
		 * The sort function oject must offer a member function template
		 * `operator()` that accepts three arguments:
		 *
		 * * An iterator to the first element of the range to sort.
		 * * An iterator past the last element of the range to sort.
		 * * A comparison function to use to compare the elements.
		 *
		 * The comparison funtion object received by the sort function object hasn't
		 * necessarily the type of the one passed along with the other parameters to
		 * this member function.
		 *
		 * @note
		 * Attempting to iterate elements using a raw pointer returned by a call to
		 * either `data` or `raw` gives no guarantees on the order, even though
		 * `sort` has been invoked.
		 *
		 * @tparam Compare Type of comparison function object.
		 * @tparam Sort Type of sort function object.
		 * @tparam Args Types of arguments to forward to the sort function object.
		 * @param compare A valid comparison function object.
		 * @param sort A valid sort function object.
		 * @param args Arguments to forward to the sort function object, if any.
		 */
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

		/**
		 * @brief Sort components according to the order of the entities in another
		 * sparse set.
		 *
		 * Entities that are part of both the sparse sets are ordered internally
		 * according to the order they have in `other`. All the other entities goes
		 * to the end of the list and there are no guarantess on their order.
		 * Components are sorted according to the entities to which they
		 * belong.<br/>
		 * In other terms, this function can be used to impose the same order on two
		 * sets by using one of them as a master and the other one as a slave.
		 *
		 * Iterating the sparse set with a couple of iterators returns elements in
		 * the expected order after a call to `respect`. See `begin` and `end` for
		 * more details.
		 *
		 * @note
		 * Attempting to iterate elements using a raw pointer returned by a call to
		 * either `data` or `raw` gives no guarantees on the order, even though
		 * `respect` has been invoked.
		 *
		 * @param other The sparse sets that imposes the order of the entities.
		 */
		void respect (const SparseSet<Entity> &other) ENTT_NOEXCEPT {
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

		/**
		 * @brief Resets a sparse set.
		 */
		void reset () override {
			underlying_type::reset ();
			instances.clear ();
		}

	private:
		std::vector<object_type> instances;
	};



}