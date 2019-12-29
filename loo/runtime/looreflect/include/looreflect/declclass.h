#ifndef LOOREFLECT_DECLCLASS_H
#define LOOREFLECT_DECLCLASS_H

#include "looreflect/looreflect.h"

namespace looreflect {
	//field
	class LooField {
		template<typename T, std::size_t, std::size_t, std::size_t>friend struct detail::LooClassBuilder;
		template<size_t N>friend struct detail::LooFunctionBuilder;
		friend class LooClass;

	public:
		static constexpr unsigned kFlagsNull = 0x0;
		static constexpr unsigned kFlagsSerialized = 0x1;
		static constexpr unsigned kFlagsCString = 0x2;
		
		LooField () noexcept = default;

		LooField (
			LooType const *type,
			unsigned flags,
			unsigned width,
			unsigned offset,
			Qualifier qualifier) noexcept
			: m_type (type)
			, m_flags (flags)
			, m_serializedWidth (width)
			, m_offset (offset)
			, m_qualifier (qualifier)
		{}
	public://
		looreflect::LooType const* type ()const noexcept { return m_type; }
        unsigned flags() const noexcept { return m_flags; }
		std::size_t serialize_width ()const noexcept { return m_serializedWidth; }
		std::size_t offset ()const noexcept { return m_offset; }
		looreflect::Qualifier qualifier ()const noexcept { return m_qualifier; }
		char const* name ()const noexcept { return m_name; }
	public:
		template<typename T>void set (void* instance, T const& value)const noexcept {
			/* assert(*TypeResolver<T>::Get() == *m_type && "type mismatch"); */
			memcpy (((char *)instance + m_offset), &value, sizeof (T));
		}
		template<typename T>T get (void const* instance)const noexcept {
			/* assert(*TypeResolver<T>::Get() == *m_type && "type mismatch"); */
			T ret;
			memcpy (&ret, ((char *)instance + m_offset), sizeof (T));
			return ret;
		}
		template<class T> T const * pointer (void const *instance) const noexcept{
			/* assert(*TypeResolver<T>::Get() == *m_type && "type mismatch"); */
			return static_cast<T const *>((char *)instance + m_offset);
		}
		template<class T> T * pointer (void *instance) const noexcept{
			/* assert(*TypeResolver<T>::Get() == *m_type && "type mismatch"); */
			return static_cast<T *>((char *)instance + m_offset);
		}

		void const * void_pointer (void const *instance) const noexcept{
			return static_cast<void const *>((char *)instance + m_offset);
		}
	public:
		looreflect::LooType const *m_type;
		unsigned m_flags;
		unsigned m_serializedWidth;
		unsigned m_offset;
		looreflect::Qualifier m_qualifier;
		char const *m_name;
	};
	
	class LooFunctionParameter : public LooField{
		template<class Type, size_t, size_t, size_t>friend struct detail::LooClassBuilder;
		template<size_t N>friend struct detail::LooFunctionBuilder;

	public:
		using LooField::LooField;
	};
	class LooFunctionReturn : public LooField{
		template<class Type, size_t, size_t, size_t>
		friend struct detail::LooClassBuilder;
		template<size_t N>
		friend struct detail::LooFunctionBuilder;

	public:
		using LooField::LooField;
	};

	class LooFunction{
		template<class Type, size_t, size_t, size_t>friend struct detail::LooClassBuilder;
		template<size_t N>friend struct detail::LooFunctionBuilder;

	public:
		static constexpr unsigned kFlagsNull = 0x0;
		static constexpr unsigned kFlagsMember = 0x1;
		static constexpr unsigned kFlagsReplicated = 0x2;

		LooFunction () noexcept = default;

		LooFunction (
			LooFunctionReturn *returnType,
			/* TODO(arvid): Replace with parameter of range. */
			LooFunctionParameter *parameters,
			LooFunctionParameter *parametersEnd,
			unsigned flags) noexcept
			: m_returnType (returnType)
			, m_parameters (parameters)
			, m_parametersEnd (parametersEnd)
			, m_flags (flags)
		{}

		LooFunctionReturn const * return_type () const noexcept{return m_returnType;}

		iterator_range<LooFunctionParameter> parameters () const noexcept{
			return iterator_range<LooFunctionParameter>(m_parameters, m_parametersEnd);
		}

		unsigned flags () const noexcept{return m_flags;}

		char const * name () const noexcept{return m_name;}
		
	public:
		LooFunctionReturn const *m_returnType;
		LooFunctionParameter const *m_parameters;
		LooFunctionParameter const *m_parametersEnd;
		unsigned m_flags;
		char const *m_name;
	};

	struct LooClassVisitor{
		virtual ~LooClassVisitor () {}
		virtual void class_begin (LooClass const *, int depth) = 0;

		virtual void class_end (LooClass const *, int depth) = 0;

		virtual void class_member (LooField const *, int depth) = 0;


		virtual void array_begin (LooType const *, int depth, int length) = 0;

		virtual void array_end (LooType const *, int depth) = 0;

		virtual void array_element (LooType const *type, int depth, int elem) = 0;

		virtual void primitive (LooType const *t, void const *instance) = 0;
		virtual void string (LooType const *t, void const *instance) = 0;
	};

	class LooClass : public LooType{
		template<class T> friend LooClass const *LooGetClass () noexcept;
		template<class T> friend LooType const *LooGetType () noexcept;
		template<class T> friend LooClass const *LooGetClassImpl (LooClassTag<T>) noexcept;
		template<class T> friend LooType const *LooGetTypeImpl (LooTypeTag<T>) noexcept;

	public:
		static constexpr size_t kFlagsNull = 0x0;
		static constexpr size_t kFlagsHasBeforeSerialize = 0x1;
		static constexpr size_t kFlagsHasAfterSerialize = 0x2;
		static constexpr size_t kFlagsHasCustomSerialize = 0x4;
		static constexpr size_t kFlagsHasCustomDump = 0x8;

	public:
		LooClass (
			int size,
			std::uint64_t hash,
			LooClass *baseClass,
			/* TODO(arvid): Replace with parameter of range. */
			LooField *fields,
			LooField *fieldsEnd,
			/* TODO(arvid): Replace with parameter of range. */
			LooFunction *functions,
			LooFunction *functionsEnd,
			char const *name,
			std::size_t flags) noexcept
			: LooType (size, hash, name)
			, m_baseClass (baseClass)
			, m_fields (fields)
			, m_fieldsEnd (fieldsEnd)
			, m_functions (functions)
			, m_functionsEnd (functionsEnd)
			, m_name (name)
			, m_flags (flags)
		{
			/* Any nullptr type is refering to ourself. */
			for (LooField *field = fields; field != fieldsEnd; ++field)
				if (field->m_type == nullptr)
					field->m_type = this;
		}

		/* --------------------------------------------------------------------- */
		/* Identifier                                                            */
		/* --------------------------------------------------------------------- */
		virtual bool is_class () const noexcept override { return true; };

		/* --------------------------------------------------------------------- */
		/* Identifier                                                            */
		/* --------------------------------------------------------------------- */
		void visit_field (
				void const *ptr,
				LooField const *field,
				LooClassVisitor *visitor,
				std::size_t filter,
				int depth,
				int arrayElem = -1) const noexcept
		{
			/* If the field isn't passing the filter, skip it. */
			if (!(field->flags () & filter))
				return;

			LooType const *t = field->type ();
			auto qualifier = field->qualifier ();

			if (qualifier.isArray)
				visitor->array_element (t, depth, arrayElem);
			else
				visitor->class_member (field, depth);

			/* Recurse deeper if the field is a class. */
			if (t->is_class ()) {
				LooClass const *c = (LooClass const *)t;

				/* Resolve pointers directly. */
				if (field->qualifier ().isPointer) {
					void const *p = *(void const **)ptr;
					c->visit (p, visitor, filter, depth);
				}
				else {
					c->visit (ptr, visitor, filter, depth);
				}
			}

			/* Just visit the field if it's a primitive. */
			else {
				if ((field->flags () & LooField::kFlagsCString))
					visitor->string (field->type (), ptr);
				else
					visitor->primitive (field->type (), ptr);
			}
		}

		void visit_array (
				void const *ptr,
				LooField const *field,
				LooClassVisitor *visitor,
				std::size_t filter,
				unsigned depth) const noexcept{
			/* If the field isn't passing the filter, skip it. */
			if (!(field->flags () & filter))
				return;

			const looreflect::Qualifier qualifier = field->qualifier ();
			visitor->class_member (field, depth);
			visitor->array_begin (field->type (), depth, qualifier.arrayLength);

			char const *p = (char const *)ptr;
			for (int i = 0, n = qualifier.arrayLength; i < n; ++i) {
				visit_field (p, field, visitor, depth + 1, i);
				p += field->type ()->size ();
			}

			visitor->array_end (field->type (), depth);
		}

		virtual void visit (
				void const *instance,
				LooClassVisitor *visitor,
				std::size_t filter = LooField::kFlagsSerialized,
				unsigned depth = 0) const noexcept{
			if (instance == nullptr) {
				visitor->primitive (this, nullptr);
				return;
			}

			visitor->class_begin (this, depth);
			for (auto &field : fields ()) {
				void const *ptr = field.void_pointer (instance);
				auto qualifier = field.qualifier ();

				if (qualifier.isArray) {
					visit_array (ptr, &field, visitor, filter, depth + 1);
				}
				else {
					visit_field (ptr, &field, visitor, filter, depth + 1);
				}
			}
			visitor->class_end (this, depth);
		}


		LooClass const * base_class () const noexcept{
			return m_baseClass;
		}

		/* TODO(arvid): Replace with 'a::Range' */
		iterator_range<LooField> fields () const noexcept{
			return iterator_range<LooField>{m_fields, m_fieldsEnd};
		}

		iterator_range<LooFunction> functions () const noexcept{
			return iterator_range<LooFunction>{m_functions, m_functionsEnd};
		}

		char const * name () const noexcept	{
			return m_name;
		}

		std::size_t flags () const noexcept{
			return m_flags;
		}

		LooField const * field_by_name (char const *name) const noexcept{
			for (auto &field : fields ()) {
				if (strcmp (name, field.name ()) == 0)
					return &field;
			}

			return nullptr;
		}

		LooFunction const * function_by_name (char const *name) const noexcept{
			for (auto &func : functions ()) {
				if (strcmp (name, func.name ()) == 0)
					return &func;
			}

			return nullptr;
		}

	public:
		LooClass *m_baseClass;
		LooField *m_fields;
		LooField *m_fieldsEnd;
		LooFunction *m_functions;
		LooFunction *m_functionsEnd;
		char const *m_name;
		std::size_t m_flags;
	};

	struct LooTemplateArgument
	{
		enum class Tag {
			Type,
			Number,
		};

		Tag tag;
		union {
			LooType const *type;
			std::uint64_t number;
		};
	};

	class LooClassTemplate : public LooClass
	{
	public:
		LooClassTemplate (
			int size,
			std::uint64_t hash,
			LooClass *baseClass,
			LooField *fields,
			LooField *fieldsEnd,
			LooFunction *functions,
			LooFunction *functionsEnd,
			char const *name,
			size_t flags,
			LooTemplateArgument *templateArgs,
			LooTemplateArgument *templateArgsEnd) noexcept
			: LooClass (
				size,
				hash,
				baseClass,
				fields,
				fieldsEnd,
				functions,
				functionsEnd,
				name,
				flags)
			, m_templateArgs (templateArgs)
			, m_templateArgsEnd (templateArgsEnd)
		{}

	public:
		LooTemplateArgument *m_templateArgs;
		LooTemplateArgument *m_templateArgsEnd;
	};

	namespace detail {
		template<class Type, size_t NFields, size_t NFunctions, size_t NTemplateArgs = 0>
		struct LooClassBuilder {
			template<class Lambda>	LooClassBuilder (Lambda &&ctor) noexcept
			{
				ctor (this);
			}

			std::size_t const numFields = NFields;
			std::size_t const numFunctions = NFunctions;
			std::size_t const numTemplateArgs = NTemplateArgs;
			/* Arrays of size 0 are UB. */
			LooField fields[NFields + 1];
			LooFunction functions[NFunctions + 1];
			LooTemplateArgument templateArgs[NTemplateArgs + 1];
		};
}

}

#endif