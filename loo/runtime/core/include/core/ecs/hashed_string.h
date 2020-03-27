#pragma  once
#include <cstddef>
#include <cstdint>
#include "core/ecs/config.h"

namespace looecs
{
	struct HashedString final {
		struct ConstCharWrapper final {
			constexpr ConstCharWrapper (const char* str) ECS_NOEXCEPT
				:str (str) {}
			const char* str;
		};
		
		static constexpr std::uint64_t offset = 14695981039346656037ull;
		static constexpr std::uint64_t prime = 1099511628211ull;

		static constexpr std::uint64_t helper (std::uint64_t partial, const char* str)ECS_NOEXCEPT {
			return str[0] == 0 ? partial : helper ((partial^str[0])*prime, str + 1);
		}

	public:
		using hash_type = std::uint64_t;

		template<std::size_t N>
		constexpr HashedString (const char (&str)[N]) ECS_NOEXCEPT
			:hash (helper (offset, str)), str (str) {}
		explicit constexpr HashedString (ConstCharWrapper wrapper) ECS_NOEXCEPT
			: hash{ helper (offset, wrapper.str) }, str{ wrapper.str }
		{}
		constexpr operator const char *() const ECS_NOEXCEPT { return str; }
		constexpr operator hash_type() const ECS_NOEXCEPT { return hash; }
		constexpr bool operator==(const HashedString &other) const ECS_NOEXCEPT {
			return hash == other.hash;
		}
	private:
		const hash_type hash;
		const char *str;
	};

	constexpr bool operator!=(const HashedString &lhs, const HashedString &rhs) ECS_NOEXCEPT {
		return !(lhs == rhs);
	}

}

constexpr looecs::HashedString operator"" ECS_HS_SUFFIX (const char* str, std::size_t) ECS_NOEXCEPT {
	return looecs::HashedString{ str };
}