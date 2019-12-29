#ifndef LOOREFLECT_DECLTYPE_H
#define LOOREFLECT_DECLTYPE_H
#pragma once
#include "looreflect/looreflect.h"

namespace looreflect {
	//Type
	class LooType {
		template<typename T,std::size_t,std::size_t,std::size_t>friend struct detail::LooClassBuilder;
		template<size_t N>friend struct detail::LooFunctionBuilder;
		template<typename T, std::size_t EnumConstantNum> friend struct LooEnumBuilder;

	public:
		LooType ()noexcept
			: m_size (0)
			, m_hash (0) {}

		LooType (std::uint64_t size, std::uint64_t hashCode, char const* name)noexcept
			:m_size (size), m_hash (hashCode), m_name (name) {}

	public://identifier
		virtual bool is_class() const noexcept { return false; }
		virtual bool is_enum() const noexcept { return false; }
		virtual bool is_pod() const noexcept { return false; }

	public:
		std::uint64_t size ()const { return m_size; }
        char const *name() const { return m_name; }
		virtual void dump (void const* instance, FILE* file = stdout)const noexcept {
			fprintf (file, "%s{%p}", m_name, instance);
		}
	public:
		bool operator==(LooType const& other)const {return m_hash == other.m_hash;}
		bool operator!=(LooType const& other)const { return !(*this == other); }

	public:
		std::uint64_t m_size;
		std::uint64_t m_hash;
		char const *m_name;
	};


}

#endif