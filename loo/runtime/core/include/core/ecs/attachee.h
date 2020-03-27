#pragma once

#include <cassert>
#include <utility>
#include <type_traits>
#include "core/ecs/config.h"
#include "core/ecs/entity.h"

namespace looecs
{
	template<typename...>
	class Attachee;

	template<typename Entity>
	class Attachee<Entity>
	{
	public:
		/*! @brief Underlying entity identifier. */
		using entity_type = Entity;

		/*! @brief Default constructor. */
		Attachee () ECS_NOEXCEPT
			: owner{ null }
		{}

		/*! @brief Default copy constructor. */
		Attachee (const Attachee &) = default;
		/*! @brief Default move constructor. */
		Attachee (Attachee &&) = default;

		/*! @brief Default copy assignment operator. @return This attachee. */
		Attachee & operator=(const Attachee &) = default;
		/*! @brief Default move assignment operator. @return This attachee. */
		Attachee & operator=(Attachee &&) = default;

		/*! @brief Default destructor. */
		virtual ~Attachee () ECS_NOEXCEPT = default;

		inline entity_type get () const ECS_NOEXCEPT {
			return owner;
		}

		inline void construct (const entity_type entity) ECS_NOEXCEPT {
			assert (owner == null);
			owner = entity;
		}

		virtual void destroy () ECS_NOEXCEPT {
			assert (owner != null);
			owner = null;
		}

	private:
		entity_type owner;

	};

	template<typename Entity,typename Type>
	class Attachee< Entity, Type> :public Attachee<Entity>
	{
		using underlying_type = Attachee<Entity>;

	public:

		/*! @brief Type of the object associated to the attachee. */
		using object_type = Type;
		/*! @brief Underlying entity identifier. */
		using entity_type = typename underlying_type::entity_type;

		/*! @brief Default constructor. */
		Attachee () ECS_NOEXCEPT = default;

		/*! @brief Copying an attachee isn't allowed. */
		Attachee (const Attachee &) = delete;
		/*! @brief Moving an attachee isn't allowed. */
		Attachee (Attachee &&) = delete;

		/*! @brief Copying an attachee isn't allowed. @return This attachee. */
		Attachee & operator=(const Attachee &) = delete;
		/*! @brief Moving an attachee isn't allowed. @return This attachee. */
		Attachee & operator=(Attachee &&) = delete;

		/*! @brief Default destructor. */
		~Attachee () {
			if (underlying_type::get () != null) {
				reinterpret_cast<Type *>(&storage)->~Type ();
			}
		}

		const Type & get () const ECS_NOEXCEPT {
			assert (underlying_type::get () != null);
			return *reinterpret_cast<const Type *>(&storage);
		}

		Type & get () ECS_NOEXCEPT {
			return const_cast<Type &>(const_cast<const Attachee *>(this)->get ());
		}

		template<typename... Args>
		Type & construct (entity_type entity, Args &&... args) ECS_NOEXCEPT {
			underlying_type::construct (entity);
			new (&storage) Type{ std::forward<Args> (args)... };
			return *reinterpret_cast<Type *>(&storage);
		}

		void destroy () ECS_NOEXCEPT override {
			reinterpret_cast<Type *>(&storage)->~Type ();
			underlying_type::destroy ();
		}

		void move (const entity_type entity) ECS_NOEXCEPT {
			underlying_type::destroy ();
			underlying_type::construct (entity);
		}

	private:
		std::aligned_storage_t<sizeof (Type), alignof(Type)> storage;

	};
}