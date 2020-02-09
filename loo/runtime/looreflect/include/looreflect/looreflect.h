#ifndef LOOREFLECT_H
#define LOOREFLECT_H
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <assert.h>

#define DEFAULT_MODULE "default"
#define ALL_MODULE "all"
#if defined(MODULE_NAME)
#define REAL_MODULE_NAME MODULE_NAME
#else
#define REAL_MODULE_NAME DEFAULT_MODULE
#endif

#define REGISTER_REFLECT_TYPE(type, name)                                      \
  struct testgg##name##_GlobalRegister {                                       \
    testgg##name##_GlobalRegister() {                                          \
      looreflect::LooReflectManager::get().regist_type(                        \
          looreflect::LooGetType<type>(), REAL_MODULE_NAME);                  \
    }                                                                          \
  };                                                                           \
  testgg##name##_GlobalRegister s_testgg##name##_GlobalRegister;

#ifndef LOO_UNUSED
#define LOO_UNUSED(x) (void)(x)
#endif

namespace looreflect{
	/*
	LOOPROPERTY:
	serialized
	tagname
	width
	cstring
	*/
	//macros
#ifdef __LOOREFLECT__
	#define LOOCLASS(...) __attribute__((annotate("loo-class;" #__VA_ARGS__)))
	#define LOOENUM(...) __attribute__((annotate("loo-enum;" #__VA_ARGS__)))
	#define LOOUNION(...) __attribute__((annotate("loo-class;" #__VA_ARGS__)))
	#define LOOPROPERTY(...) __attribute__((annotate("loo-property;" #__VA_ARGS__)))
	#define LOOFUNCTION(...) __attribute__((annotate("loo-function;" #__VA_ARGS__)))
	#define LOOMETA_OBJECT
#else /* else __LOOREFLECT__ */
	#define LOOCLASS(...)
	#define LOOUNION(...)
	#define LOOENUM(...)
	#define LOOPROPERTY(...)
	#define LOOFUNCTION(...)
	#define LOOMETA_OBJECT \
        friend struct PrimitiveResolver; \
        static constexpr bool IsReflected = true; \
        template<class T> \
        friend constexpr bool AfterSerialize(T *) noexcept; \
        template<class T> \
        friend constexpr bool BeforeSerialize(T *) noexcept; \
        template<class T> \
        friend looreflect::LooClass const *looreflect::detail::LooGetClassImpl(looreflect::LooClassTag<T>) noexcept;\
		public: \
		virtual const looreflect::LooType *GetType()const;
#endif

	template<class T>
	struct IsSerializable;
	template<class T>
	struct HasBeforeSerialize;
	template<class T>
	struct HasAfterSerialize;
	template<class T>
	struct HasCustomSerialize;
	template<class T>
	struct HasCustomDump;

	class LooClass;
	class LooType;
	class LooEnum;
	template<class T>
	struct LooTypeTag {};
	template<class T>
	struct LooClassTag {};
	template<class T>
	struct LooEnumTag {};

	template<class T>
	LooClass const *
		LooGetClass () noexcept;
	template<class T>
	LooType const *
		LooGetType () noexcept;
	template<class T>
	LooEnum const *
		LooGetEnum ()noexcept;

	template<class T, class Serializer>
	struct Serialize;

	template<class T, class Serializer>
	constexpr bool
		AfterSerialize (T *_this) noexcept
	{
		if /*constexpr*/ (HasAfterSerialize<T>::value)
			return _this->AfterSerialize ();
		return true;
	}

	template<class T, class Serializer>
	constexpr bool
		BeforeSerialize (T *_this) noexcept
	{
		if /*constexpr*/ (HasBeforeSerialize<T>::value)
			return _this->BeforeSerialize ();
		return true;
	}

	template<class T, class Serializer>
	constexpr bool
		CustomSerialize (T *_this) noexcept
	{
		if /*constexpr*/ (HasCustomSerialize<T>::value)
			return _this->Serialize ();
		return true;
	}

	namespace detail {
		template<typename T,std::size_t FieldsNum,std::size_t FuncsNum,std::size_t TemplateArgsNum>	struct LooClassBuilder;
		template<std::size_t ParamsNum>	struct LooFunctionBuilder;
		template<typename T, std::size_t EnumConstantNum> struct LooEnumBuilder;
		template<typename T> LooClass const * LooGetClassImpl (LooClassTag<T>)noexcept;
		template<typename T> LooType const * LooGetTypeImpl (LooTypeTag<T>)noexcept;
		template<typename T> LooEnum const * LooGetEnumImpl (LooEnumTag<T>)noexcept;
	}

	//hash _FNV1_64_HASH 
	/*
	long hash_lower = 0xcbf29ce484222325L;
	hash_lower ^= ((ch >= 'A' && ch <= 'Z') ? (ch + 32) : ch);
	hash_lower *= 0x100000001b3L; //hashCode
	*/
	static constexpr std::uint64_t gFNV1aLower = 0xcbf29ce484222325;
	static constexpr std::uint64_t gFNV1aParam = 0x100000001b3;
	inline constexpr std::uint64_t Hash (char const * const str, std::uint64_t const value = gFNV1aLower) {
		return (str[0] == '\0')? value: Hash (&str[1], (value ^ uint64_t (str[0])) * gFNV1aParam);
	}

	//iterator range
	template<typename T>
	class iterator_range {
		T const* begin_it;
		T const* end_it;
	public:
        iterator_range(T const *begin, T const *end) noexcept: begin_it(begin), end_it(end) {}
		T const* begin ()const noexcept {return begin_it;}
		T const* end ()const noexcept { return end_it; }
		std::size_t length ()const noexcept { return end_it - begin_it; }
		T const& operator[](std::size_t index)const noexcept { return begin[index]; }
	};
	enum CVQualifier : unsigned char {
		kCVQualifierNone = 0x0,
		kCVQualifierConst = 0x1,
		kCVQualifierVolatile = 0x2,
		kCVQualifierConstVolatile = (kCVQualifierConst | kCVQualifierVolatile),
	};

	enum RefQualifier : unsigned char {
		kRefQualifierNone = 0x0,
		kRefQualifierRef = 0x1,
		kRefQualifierRefRef = 0x2,
	};

	enum StorageClass : unsigned char {
		kStorageClassNone,
		kStorageClassExtern,
		kStorageClassStatic,
		kStorageClassExternThreadLocal,
		kStorageClassStaticThreadLocal,
		kStorageClassMember,
		kStorageClassStaticMember,
		kStorageClassThreadLocalStaticMember,
	};

	struct Qualifier {
		constexpr
			Qualifier (
				unsigned char cv = kRefQualifierNone,
				unsigned char ref = kRefQualifierNone,
				unsigned char storage = kStorageClassNone,
				unsigned char pointer = 0,
				unsigned char array = 0,
				unsigned count = 0) noexcept
			: arrayLength (count)
			, cvQualifier (cv)
			, refQualifier (ref)
			, storageClass (storage)
			, isPointer (pointer)
			, isArray (array)
		{}

		unsigned arrayLength;
		unsigned char cvQualifier : 3;
		unsigned char refQualifier : 3;
		unsigned char storageClass : 3;
		unsigned char isPointer : 1;
		unsigned char isArray : 1;
	};

}
#include "looreflect/decltype.h"
#include "looreflect/declclass.h"
#include "looreflect/declenum.h"
#include "looreflect/builtinpodtypes.h"
#include "looreflect/builtintypestring.h"
#include "looreflect/builtintypeunorderedmap.h"

namespace looreflect {
	template<class T>inline LooClass const * LooGetClass () noexcept{
		return detail::LooGetClassImpl (LooClassTag<T>{});
	}
	template<class T> inline LooType const * LooGetType () noexcept	{
		return detail::LooGetTypeImpl (LooTypeTag<T>{});
	}
	template<class T>inline LooEnum const*	LooGetEnum ()noexcept{
		return detail::LooGetEnumImpl (LooEnumTag<T>{});
	}

	// typeof
	template <class T> LooType const *LooTypeOf(T const *) 
	{
         using namespace looreflect;
         return LooGetType<T>();
    }
    template <class T> LooType const *LooRealTypeOf(T const * ins) {
		return ins ? ins->GetType() : nullptr;
    }

	template <typename T> inline std::string enum_to_string (T value) {
		const LooEnum *type = LooGetEnum<T> ();
		assert (type);
		auto constant = type->enum_constant_by_value (static_cast<uint64_t>(value));
		assert (constant);
		return constant->name ();
	}
	//template <typename T>
	//inline std::string enummask_to_string (uint32_t value) {
	//	const LooEnum *type = LooGetEnum<T> ();
	//	assert (type);
	//	std::string nameMask;
	//	for (T t = T::_begin; t < T::_end; t = T (uint32_t (t) << 1)) {
	//		if (value & t == 0)
	//			continue;
	//		auto constant = type->enum_constant_by_value (value);
	//		assert (constant);
	//		if (t != T::_begin) {
	//			nameMask.append ("|");
	//		}
	//		nameMask.append (constant->name ());
	//	}
	//	return nameMask;
	//}

	template <typename T> inline std::string enummask_to_string (uint64_t value) {
		const LooEnum *type = LooGetEnum<T> ();
		assert (type);
		std::string nameMask;
		for (T t = T::_begin; t < T::_end; t = T (uint64_t (t) << 1)) {
			if ((value & static_cast<uint64_t>(t)) == 0)
				continue;
			auto constant = type->enum_constant_by_value (static_cast<uint64_t>(t));
			assert (constant);
			if (t != T::_begin) {
				nameMask.append ("|");
			}
			nameMask.append (constant->name ());
		}
		return nameMask;
	}
	template <typename T> inline T to_enum (const char *enumValueStr) {
		const LooEnum *type = LooGetEnum<T> ();
		assert (type);
		auto constant = type->enum_constant_by_name (enumValueStr);
		assert (constant);
		return static_cast<T>(constant->value ());
	}
	template <typename T, typename U> inline U to_enummask (const std::string& enumValuesStr) {
		const LooEnum *type = LooGetEnum<T> ();
		assert (type);
		U mask = 0;
		std::vector<std::pair<const char *, const char *>> token_list;
		strtk::split ("|", enumValuesStr, std::back_inserter (token_list));//cannot convert const char* to const std::string
		std::string s;
		for (auto it = token_list.begin (); it != token_list.end (); ++it)
		{
			s.assign (it->first, it->second);
			auto constant = type->enum_constant_by_name (s.c_str ());
			if (constant)
			{
				mask |= U (constant->value ());
			}
		}
		return mask;
	}

} // namespace looreflect
#define GET_REAL_TYPE(type)                                                    \
  (type->is_class()                                                            \
       ? static_cast<const looreflect::LooClass *>(type)                       \
       : (type->is_enum() ? static_cast<const looreflect::LooEnum *>(type)     \
                          : type))


#endif

