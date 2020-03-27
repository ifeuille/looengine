#pragma once
#include <memory>
#include <utility>
#include <cassert>

#include "core/ecs/config.h"

namespace looecs
{
	/**
	 * @brief Service locator, nothing more.
	 *
	 * A service locator can be used to do what it promises: locate services.<br/>
	 * Usually service locators are tightly bound to the services they expose and
	 * thus it's hard to define a general purpose class to do that. This template
	 * based implementation tries to fill the gap and to get rid of the burden of
	 * defining a different specific locator for each application.
	 *
	 * @tparam Service Type of service managed by the locator.
	 */
	template<typename Service>
	struct ServiceLocator final {
		/*! @brief Type of service offered. */
		using service_type = Service;

		/*! @brief Default constructor, deleted on purpose. */
		ServiceLocator () = delete;
		/*! @brief Default destructor, deleted on purpose. */
		~ServiceLocator () = delete;

		inline static bool empty () ECS_NOEXCEPT {
			return !static_cast<bool>(service);
		}

		inline static std::weak_ptr<Service> get () ECS_NOEXCEPT {
			return service;
		}

		inline static Service & ref () ECS_NOEXCEPT {
			return *service;
		}

		template<typename Impl = Service, typename... Args>
		inline static void set (Args &&... args) {
			service = std::make_shared<Impl> (std::forward<Args> (args)...);
		}

		inline static void set (std::shared_ptr<Service> ptr) {
			assert (static_cast<bool>(ptr));
			service = std::move (ptr);
		}

		inline static void reset () {
			service.reset ();
		}

	private:
		static std::shared_ptr<Service> service;
	};


	template<typename Service>
	std::shared_ptr<Service> ServiceLocator<Service>::service{};



}