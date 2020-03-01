/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::Object> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<loo::Object> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<loo::Object> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<loo::Object> { static constexpr bool value = false; };
template<> struct HasCustomDump<loo::Object> { static constexpr bool value = false; };
namespace detail
{
template<>
inline LooClass const *
LooGetClassImpl(LooClassTag<loo::Object>) noexcept
{
static detail::LooClassBuilder<loo::Object, 1, 1> reflected([](auto self) {

/* LooField 1 */
self->fields[0].m_type = LooGetType<char>();
self->fields[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized | LooField::kFlagsCString;
self->fields[0].m_serializedWidth = sizeof(char) * 8;
self->fields[0].m_offset = offsetof(loo::Object, m_Name);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
self->fields[0].m_name = "m_Name";

/* LooFunction 1*/
static LooFunctionReturn functionRet0;
functionRet0.m_type = LooGetType<char>();
functionRet0.m_flags = 0/*TODO*/;
functionRet0.m_serializedWidth = sizeof(char) * 8;
functionRet0.m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
static LooFunctionParameter functionParameters0[1];
self->functions[0].m_returnType = &functionRet0;
self->functions[0].m_parameters = &functionParameters0[0];
self->functions[0].m_parametersEnd = &functionParameters0[0];
self->functions[0].m_flags = LooFunction::kFlagsNull | LooFunction::kFlagsMember;
self->functions[0].m_name = "name";
});
static LooClass cache(
sizeof(loo::Object),
Hash("loo::Object"),
nullptr,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"loo::Object",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::Object>) noexcept
{
return LooGetClass<loo::Object>();
}
} /* namespace detail */
} /* namespace looreflect */

// utils functions for class instance
inline const looreflect::LooType *loo::Object::GetType() const { return looreflect::LooGetClass<loo::Object>();}

