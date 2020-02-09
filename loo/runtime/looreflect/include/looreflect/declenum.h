#ifndef LOOREFLECT_DECLENUM_H
#define LOOREFLECT_DECLENUM_H
#include "looreflect/looreflect.h"

namespace looreflect {
	//enum value
	class LooEnumConstant {
	public:
		LooEnumConstant () noexcept = default;

		LooEnumConstant (
			LooType const *type,
			unsigned flags,
			const char* name,
			const char* tagName,
			uint64_t value,
			int index)noexcept
			:m_type (type)
			, m_flags (flags)
			, m_name (name)
			, m_tagName(tagName)
			, m_value (value)
			, m_index (index) {
		}

		uint64_t value ()const noexcept {
			return m_value;
		}

		uint64_t index ()const noexcept {
			return m_index;
		}
		std::size_t flags () const noexcept {
			return m_flags;
		}
		const char* name ()const noexcept {
			return m_name;
		}
		const char* tag_name ()const noexcept {
			return m_tagName;
		}
		template<typename T> T get () const noexcept {
			return static_cast<T>(m_value);
		}
		looreflect::LooType const * type () const noexcept {
			return m_type;
		}
	public:
		int m_index;
		uint64_t m_value;
		
		const char* m_name;//not full name
		const char* m_tagName;
		std::size_t m_flags;
		looreflect::LooType const *m_type;
	};

	//Enum visitor
	class LooEnumVisitor {
	public:
		virtual ~LooEnumVisitor () {}

		virtual void begin (LooEnum const*) = 0;
		virtual void end (LooEnum const*) = 0;
		virtual void value (LooEnumConstant const*) = 0;


		virtual void primitive (LooType const *t, void const *instance) = 0;
		virtual void string (LooType const *t, void const *instance) = 0;

	};

	class LooEnum : public LooType
	{
	public:
		template<class T>
		friend LooEnum const *LooGetEnum () noexcept;
		template<class T>
		friend LooType const *LooGetType () noexcept;
		template<class T>
		friend LooEnum const *LooGetEnumImpl (LooEnumTag<T>) noexcept;
		template<class T>
        friend LooType const *LooGetTypeImpl(LooTypeTag<T>) noexcept;

	public:
		LooEnum (
			int size,
			std::uint64_t hash,
			LooEnumConstant* enumValues,
            LooEnumConstant *enumValuesEnd,
			char const* name,
			std::size_t flags)noexcept
			:LooType (size, hash, name)
			, m_enumvalues (enumValues)
			, m_enumvaluesEnd (enumValuesEnd)
			, m_flags (flags) {
		}

		virtual bool is_enum () const noexcept override{ return true; }

		void visit_enum_constant (
			LooEnumConstant const* enumValue,
			LooEnumVisitor* visitor,
			std::size_t filter)const noexcept {
			if (!(enumValue->flags () & filter)) {
				return;
			}
			//LooType const* type = enumValue->type ();
			visitor->value (enumValue);
		}

		virtual void visit (
			void const *instance,
			LooEnumVisitor *visitor,
			std::size_t filter = LooField::kFlagsSerialized) const noexcept
		{
			if (instance == nullptr) {
				visitor->primitive (this, nullptr);
				return;
			}

			visitor->begin (this);
			for (auto &enumValue : values ()) {
				visit_enum_constant (&enumValue, visitor, filter);
			}
			visitor->end (this);
		}

		iterator_range<LooEnumConstant> values ()const noexcept {
            return iterator_range<LooEnumConstant>(m_enumvalues, m_enumvaluesEnd);
		}

		std::size_t flags () const noexcept
		{
			return m_flags;
		}

		LooEnumConstant const* enum_constant_by_name (char const* name)const noexcept {
			for (auto& enumvalue : values ()) {
				if (strcmp (name, enumvalue.name ()) == 0) {
					return &enumvalue;
				}
			}
			return nullptr;
		}

		LooEnumConstant const* enum_constant_by_value (uint64_t value)const noexcept {
			for (auto& enumvalue : values ()) {
				if (value == enumvalue.value ()) {
					return &enumvalue;
				}
			}
			return nullptr;
		}

		LooEnumConstant const* enum_constant_by_index (int index)const noexcept {
			for (auto& enumvalue : values ()) {
				if (index == enumvalue.index ()) {
					return &enumvalue;
				}
			}
			return nullptr;
		}

	public:
		char const* m_name;
		LooEnumConstant* m_enumvalues;
		LooEnumConstant* m_enumvaluesEnd;
		std::size_t m_flags;
	};

	namespace detail {
		template<class Type, size_t NValues>
		struct LooEnumBuilder {
          template <class Lambda> LooEnumBuilder(Lambda &&ctor) { ctor(this);
			}

			size_t const numValues = NValues;
			LooEnumConstant enumValues[NValues + 1];

		};
	}

}



#endif