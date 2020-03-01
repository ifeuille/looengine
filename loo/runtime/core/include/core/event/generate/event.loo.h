/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::Event> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<loo::core::Event> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<loo::core::Event> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<loo::core::Event> { static constexpr bool value = false; };
template<> struct HasCustomDump<loo::core::Event> { static constexpr bool value = false; };
namespace detail
{
template<>
inline LooClass const *
LooGetClassImpl(LooClassTag<loo::core::Event>) noexcept
{
static detail::LooClassBuilder<loo::core::Event, 4, 0> reflected([](auto self) {

/* LooField 1 */
self->fields[0].m_type = LooGetType<int>();
self->fields[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[0].m_serializedWidth = sizeof(int) * 8;
self->fields[0].m_offset = offsetof(loo::core::Event, typeID);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[0].m_name = "typeID";

/* LooField 2 */
self->fields[1].m_type = LooGetType<int>();
self->fields[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[1].m_serializedWidth = sizeof(int) * 8;
self->fields[1].m_offset = offsetof(loo::core::Event, flags);
self->fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[1].m_name = "flags";

/* LooField 3 */
self->fields[2].m_type = LooGetType<bool>();
self->fields[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[2].m_serializedWidth = sizeof(bool) * 8;
self->fields[2].m_offset = offsetof(loo::core::Event, canceled);
self->fields[2].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[2].m_name = "canceled";

/* LooField 4 */
self->fields[3].m_type = LooGetType<loo::Object>();
self->fields[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[3].m_serializedWidth = sizeof(loo::Object) * 8;
self->fields[3].m_offset = offsetof(loo::core::Event, sender);
self->fields[3].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
self->fields[3].m_name = "sender";
});
static LooClass cache(
sizeof(loo::core::Event),
Hash("loo::core::Event"),
const_cast<LooClass*>(LooGetClass<loo::Object>()),
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"loo::core::Event",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::Event>) noexcept
{
return LooGetClass<loo::core::Event>();
}
} /* namespace detail */
} /* namespace looreflect */

// utils functions for class instance
inline const looreflect::LooType *loo::core::Event::GetType() const { return looreflect::LooGetClass<loo::core::Event>();}

/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::EventListener> { static constexpr bool value = false; };
template<> struct HasBeforeSerialize<loo::core::EventListener> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<loo::core::EventListener> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<loo::core::EventListener> { static constexpr bool value = false; };
template<> struct HasCustomDump<loo::core::EventListener> { static constexpr bool value = false; };
namespace detail
{
template<>
inline LooClass const *
LooGetClassImpl(LooClassTag<loo::core::EventListener>) noexcept
{
static detail::LooClassBuilder<loo::core::EventListener, 0, 3> reflected([](auto self) {

/* LooFunction 1*/
static LooFunctionReturn functionRet0;
functionRet0.m_type = LooGetType<void>();
functionRet0.m_flags = 0/*TODO*/;
functionRet0.m_serializedWidth = 0 * 8;
functionRet0.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static LooFunctionParameter functionParameters0[1];
functionParameters0[0].m_type = LooGetType<int>();
functionParameters0[0].m_flags = 0/*TODO*/;
functionParameters0[0].m_serializedWidth = sizeof(int) * 8;
functionParameters0[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
functionParameters0[0].m_name = "eventType";
self->functions[0].m_returnType = &functionRet0;
self->functions[0].m_parameters = &functionParameters0[0];
self->functions[0].m_parametersEnd = &functionParameters0[1];
self->functions[0].m_flags = LooFunction::kFlagsNull | LooFunction::kFlagsMember;
self->functions[0].m_name = "listen";

/* LooFunction 2*/
static LooFunctionReturn functionRet1;
functionRet1.m_type = LooGetType<void>();
functionRet1.m_flags = 0/*TODO*/;
functionRet1.m_serializedWidth = 0 * 8;
functionRet1.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static LooFunctionParameter functionParameters1[1];
functionParameters1[0].m_type = LooGetType<int>();
functionParameters1[0].m_flags = 0/*TODO*/;
functionParameters1[0].m_serializedWidth = sizeof(int) * 8;
functionParameters1[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
functionParameters1[0].m_name = "eventType";
self->functions[1].m_returnType = &functionRet1;
self->functions[1].m_parameters = &functionParameters1[0];
self->functions[1].m_parametersEnd = &functionParameters1[1];
self->functions[1].m_flags = LooFunction::kFlagsNull | LooFunction::kFlagsMember;
self->functions[1].m_name = "unlisten";

/* LooFunction 3*/
static LooFunctionReturn functionRet2;
functionRet2.m_type = LooGetType<bool>();
functionRet2.m_flags = 0/*TODO*/;
functionRet2.m_serializedWidth = sizeof(bool) * 8;
functionRet2.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static LooFunctionParameter functionParameters2[1];
functionParameters2[0].m_type = LooGetType<loo::core::Event>();
functionParameters2[0].m_flags = 0/*TODO*/;
functionParameters2[0].m_serializedWidth = sizeof(loo::core::Event) * 8;
functionParameters2[0].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
functionParameters2[0].m_name = "";
self->functions[2].m_returnType = &functionRet2;
self->functions[2].m_parameters = &functionParameters2[0];
self->functions[2].m_parametersEnd = &functionParameters2[1];
self->functions[2].m_flags = LooFunction::kFlagsNull | LooFunction::kFlagsMember;
self->functions[2].m_name = "onEvent";
});
static LooClass cache(
sizeof(loo::core::EventListener),
Hash("loo::core::EventListener"),
nullptr,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"loo::core::EventListener",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::EventListener>) noexcept
{
return LooGetClass<loo::core::EventListener>();
}
} /* namespace detail */
} /* namespace looreflect */

// utils functions for class instance
inline const looreflect::LooType *loo::core::EventListener::GetType() const { return looreflect::LooGetClass<loo::core::EventListener>();}

/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::EventManager> { static constexpr bool value = false; };
template<> struct HasBeforeSerialize<loo::core::EventManager> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<loo::core::EventManager> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<loo::core::EventManager> { static constexpr bool value = false; };
template<> struct HasCustomDump<loo::core::EventManager> { static constexpr bool value = false; };
namespace detail
{
template<>
inline LooClass const *
LooGetClassImpl(LooClassTag<loo::core::EventManager>) noexcept
{
static detail::LooClassBuilder<loo::core::EventManager, 0, 4> reflected([](auto self) {

/* LooFunction 1*/
static LooFunctionReturn functionRet0;
functionRet0.m_type = LooGetType<bool>();
functionRet0.m_flags = 0/*TODO*/;
functionRet0.m_serializedWidth = sizeof(bool) * 8;
functionRet0.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static LooFunctionParameter functionParameters0[1];
functionParameters0[0].m_type = LooGetType<loo::core::Event>();
functionParameters0[0].m_flags = 0/*TODO*/;
functionParameters0[0].m_serializedWidth = sizeof(loo::core::Event) * 8;
functionParameters0[0].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
functionParameters0[0].m_name = "e";
self->functions[0].m_returnType = &functionRet0;
self->functions[0].m_parameters = &functionParameters0[0];
self->functions[0].m_parametersEnd = &functionParameters0[1];
self->functions[0].m_flags = LooFunction::kFlagsNull | LooFunction::kFlagsMember;
self->functions[0].m_name = "sendEvent";

/* LooFunction 2*/
static LooFunctionReturn functionRet1;
functionRet1.m_type = LooGetType<void>();
functionRet1.m_flags = 0/*TODO*/;
functionRet1.m_serializedWidth = 0 * 8;
functionRet1.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static LooFunctionParameter functionParameters1[1];
functionParameters1[0].m_type = LooGetType<loo::core::Event>();
functionParameters1[0].m_flags = 0/*TODO*/;
functionParameters1[0].m_serializedWidth = sizeof(loo::core::Event) * 8;
functionParameters1[0].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
functionParameters1[0].m_name = "e";
self->functions[1].m_returnType = &functionRet1;
self->functions[1].m_parameters = &functionParameters1[0];
self->functions[1].m_parametersEnd = &functionParameters1[1];
self->functions[1].m_flags = LooFunction::kFlagsNull | LooFunction::kFlagsMember;
self->functions[1].m_name = "postEvent";

/* LooFunction 3*/
static LooFunctionReturn functionRet2;
functionRet2.m_type = LooGetType<void>();
functionRet2.m_flags = 0/*TODO*/;
functionRet2.m_serializedWidth = 0 * 8;
functionRet2.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static LooFunctionParameter functionParameters2[2];
functionParameters2[0].m_type = LooGetType<int>();
functionParameters2[0].m_flags = 0/*TODO*/;
functionParameters2[0].m_serializedWidth = sizeof(int) * 8;
functionParameters2[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
functionParameters2[0].m_name = "eventid";
functionParameters2[1].m_type = LooGetType<loo::core::EventListener>();
functionParameters2[1].m_flags = 0/*TODO*/;
functionParameters2[1].m_serializedWidth = sizeof(loo::core::EventListener) * 8;
functionParameters2[1].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
functionParameters2[1].m_name = "listener";
self->functions[2].m_returnType = &functionRet2;
self->functions[2].m_parameters = &functionParameters2[0];
self->functions[2].m_parametersEnd = &functionParameters2[2];
self->functions[2].m_flags = LooFunction::kFlagsNull | LooFunction::kFlagsMember;
self->functions[2].m_name = "listen";

/* LooFunction 4*/
static LooFunctionReturn functionRet3;
functionRet3.m_type = LooGetType<void>();
functionRet3.m_flags = 0/*TODO*/;
functionRet3.m_serializedWidth = 0 * 8;
functionRet3.m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
static LooFunctionParameter functionParameters3[2];
functionParameters3[0].m_type = LooGetType<int>();
functionParameters3[0].m_flags = 0/*TODO*/;
functionParameters3[0].m_serializedWidth = sizeof(int) * 8;
functionParameters3[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
functionParameters3[0].m_name = "eventid";
functionParameters3[1].m_type = LooGetType<loo::core::EventListener>();
functionParameters3[1].m_flags = 0/*TODO*/;
functionParameters3[1].m_serializedWidth = sizeof(loo::core::EventListener) * 8;
functionParameters3[1].m_qualifier = Qualifier(0, 0, 0, 1, 0, 0);
functionParameters3[1].m_name = "listener";
self->functions[3].m_returnType = &functionRet3;
self->functions[3].m_parameters = &functionParameters3[0];
self->functions[3].m_parametersEnd = &functionParameters3[2];
self->functions[3].m_flags = LooFunction::kFlagsNull | LooFunction::kFlagsMember;
self->functions[3].m_name = "unlisten";
});
static LooClass cache(
sizeof(loo::core::EventManager),
Hash("loo::core::EventManager"),
const_cast<LooClass*>(LooGetClass<loo::Object>()),
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"loo::core::EventManager",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::EventManager>) noexcept
{
return LooGetClass<loo::core::EventManager>();
}
} /* namespace detail */
} /* namespace looreflect */

// utils functions for class instance
inline const looreflect::LooType *loo::core::EventManager::GetType() const { return looreflect::LooGetClass<loo::core::EventManager>();}

