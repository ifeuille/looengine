#ifndef LOO_GLOBAL_TEMPLATE_CORE_CACHERESOURCE_H
#define LOO_GLOBAL_TEMPLATE_CORE_CACHERESOURCE_H

#include <memory>
#include <unordered_map>

namespace loo
{
	namespace global
	{
		/// Mananger of resources based on the given hasher function.
		template <typename T>
		class CacheResource
		{
		public:
			/// Create a new resource or return the cached resource
			template <typename... Args>
			T &request_resource (Args &&... args);

			/*
			 * @brief Removes cached resources.
			 */
			void clear ();

		private:
			/// Map of resource's hash and the resource object
			std::unordered_map<size_t, T> cache_resources;
		};

		namespace detail
		{
			template <typename T>
			inline void hash_param (size_t &seed, const T &value)
			{
				hash_combine (seed, value);
			}
		}


		template <typename T>
		template <typename... Args>
		inline T &CacheResource<T>::request_resource (Args &&... args)
		{
			size_t res_hash = 0;

			detail::hash_param (res_hash, args...);

			auto res_it = cache_resources.find (res_hash);

			if (res_it != cache_resources.end ())
			{
				return res_it->second;
			}

			// If we do not have it already, create and cache it
			const char *res_type = typeid(T).name ();
			size_t      res_id = cache_resources.size ();

			//LE_LOG_INFO ("Building #%zu cache object (%s)", res_id, res_type);

			try
			{
				T resource (std::forward<Args> (args)...);

				auto res_ins_it = cache_resources.emplace (res_hash, std::move (resource));

				if (!res_ins_it.second)
				{
					throw std::runtime_error{ std::string{"Insertion error for #"} +std::to_string (res_id) + "cache object (" + res_type + ")" };
				}

				return res_ins_it.first->second;
			}
			catch (const std::exception &e)
			{
				//LE_LOG_INFO ("Creation error for #%zu cache object ( %s )", res_id, res_type);
				throw e;
			}
		}

		template <typename T>
		inline void CacheResource<T>::clear ()
		{
			cache_resources.clear ();
		}
	}        // namespace vkb
}

#endif