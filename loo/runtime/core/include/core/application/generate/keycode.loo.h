/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::TouchPoint> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<loo::core::TouchPoint> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<loo::core::TouchPoint> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<loo::core::TouchPoint> { static constexpr bool value = false; };
template<> struct HasCustomDump<loo::core::TouchPoint> { static constexpr bool value = false; };
namespace detail
{
template<>
inline LooClass const *
LooGetClassImpl(LooClassTag<loo::core::TouchPoint>) noexcept
{
static detail::LooClassBuilder<loo::core::TouchPoint, 1, 0> reflected([](auto self) {

/* LooField 1 */
self->fields[0].m_type = LooGetType<int>();
self->fields[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[0].m_serializedWidth = sizeof(int) * 8;
self->fields[0].m_offset = offsetof(loo::core::TouchPoint, id);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[0].m_name = "id";
});
static LooClass cache(
sizeof(loo::core::TouchPoint),
Hash("loo::core::TouchPoint"),
nullptr,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"loo::core::TouchPoint",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::TouchPoint>) noexcept
{
return LooGetClass<loo::core::TouchPoint>();
}
} /* namespace detail */
} /* namespace looreflect */

// utils functions for class instance
inline const looreflect::LooType *loo::core::TouchPoint::GetType() const { return looreflect::LooGetClass<loo::core::TouchPoint>();}

/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::SAppTouchPoint> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<loo::core::SAppTouchPoint> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<loo::core::SAppTouchPoint> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<loo::core::SAppTouchPoint> { static constexpr bool value = false; };
template<> struct HasCustomDump<loo::core::SAppTouchPoint> { static constexpr bool value = false; };
namespace detail
{
template<>
inline LooClass const *
LooGetClassImpl(LooClassTag<loo::core::SAppTouchPoint>) noexcept
{
static detail::LooClassBuilder<loo::core::SAppTouchPoint, 4, 0> reflected([](auto self) {

/* LooField 1 */
self->fields[0].m_type = LooGetType<unsigned long long>();
self->fields[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[0].m_serializedWidth = sizeof(unsigned long long) * 8;
self->fields[0].m_offset = offsetof(loo::core::SAppTouchPoint, identifier);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[0].m_name = "identifier";

/* LooField 2 */
self->fields[1].m_type = LooGetType<float>();
self->fields[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[1].m_serializedWidth = sizeof(float) * 8;
self->fields[1].m_offset = offsetof(loo::core::SAppTouchPoint, x);
self->fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[1].m_name = "x";

/* LooField 3 */
self->fields[2].m_type = LooGetType<float>();
self->fields[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[2].m_serializedWidth = sizeof(float) * 8;
self->fields[2].m_offset = offsetof(loo::core::SAppTouchPoint, y);
self->fields[2].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[2].m_name = "y";

/* LooField 4 */
self->fields[3].m_type = LooGetType<bool>();
self->fields[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[3].m_serializedWidth = sizeof(bool) * 8;
self->fields[3].m_offset = offsetof(loo::core::SAppTouchPoint, changed);
self->fields[3].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[3].m_name = "changed";
});
static LooClass cache(
sizeof(loo::core::SAppTouchPoint),
Hash("loo::core::SAppTouchPoint"),
nullptr,
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"loo::core::SAppTouchPoint",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::SAppTouchPoint>) noexcept
{
return LooGetClass<loo::core::SAppTouchPoint>();
}
} /* namespace detail */
} /* namespace looreflect */

// utils functions for class instance
inline const looreflect::LooType *loo::core::SAppTouchPoint::GetType() const { return looreflect::LooGetClass<loo::core::SAppTouchPoint>();}

/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::SAppEvent> { static constexpr bool value = true; };
template<> struct HasBeforeSerialize<loo::core::SAppEvent> { static constexpr bool value = false; };
template<> struct HasAfterSerialize<loo::core::SAppEvent> { static constexpr bool value = false; };
template<> struct HasCustomSerialize<loo::core::SAppEvent> { static constexpr bool value = false; };
template<> struct HasCustomDump<loo::core::SAppEvent> { static constexpr bool value = false; };
namespace detail
{
template<>
inline LooClass const *
LooGetClassImpl(LooClassTag<loo::core::SAppEvent>) noexcept
{
static detail::LooClassBuilder<loo::core::SAppEvent, 14, 0> reflected([](auto self) {

/* LooField 1 */
self->fields[0].m_type = LooGetType<unsigned long long>();
self->fields[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[0].m_serializedWidth = sizeof(unsigned long long) * 8;
self->fields[0].m_offset = offsetof(loo::core::SAppEvent, frameCount);
self->fields[0].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[0].m_name = "frameCount";

/* LooField 2 */
self->fields[1].m_type = LooGetType<loo::core::SAppEventType>();
self->fields[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[1].m_serializedWidth = sizeof(loo::core::SAppEventType) * 8;
self->fields[1].m_offset = offsetof(loo::core::SAppEvent, type);
self->fields[1].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[1].m_name = "type";

/* LooField 3 */
self->fields[2].m_type = LooGetType<loo::core::KeyCode>();
self->fields[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[2].m_serializedWidth = sizeof(loo::core::KeyCode) * 8;
self->fields[2].m_offset = offsetof(loo::core::SAppEvent, keyCode);
self->fields[2].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[2].m_name = "keyCode";

/* LooField 4 */
self->fields[3].m_type = LooGetType<unsigned int>();
self->fields[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[3].m_serializedWidth = sizeof(unsigned int) * 8;
self->fields[3].m_offset = offsetof(loo::core::SAppEvent, charCode);
self->fields[3].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[3].m_name = "charCode";

/* LooField 5 */
self->fields[4].m_type = LooGetType<bool>();
self->fields[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[4].m_serializedWidth = sizeof(bool) * 8;
self->fields[4].m_offset = offsetof(loo::core::SAppEvent, keyRepeat);
self->fields[4].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[4].m_name = "keyRepeat";

/* LooField 6 */
self->fields[5].m_type = LooGetType<unsigned int>();
self->fields[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[5].m_serializedWidth = sizeof(unsigned int) * 8;
self->fields[5].m_offset = offsetof(loo::core::SAppEvent, modifiers);
self->fields[5].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[5].m_name = "modifiers";

/* LooField 7 */
self->fields[6].m_type = LooGetType<int>();
self->fields[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[6].m_serializedWidth = sizeof(int) * 8;
self->fields[6].m_offset = offsetof(loo::core::SAppEvent, mouseX);
self->fields[6].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[6].m_name = "mouseX";

/* LooField 8 */
self->fields[7].m_type = LooGetType<int>();
self->fields[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[7].m_serializedWidth = sizeof(int) * 8;
self->fields[7].m_offset = offsetof(loo::core::SAppEvent, mouseY);
self->fields[7].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[7].m_name = "mouseY";

/* LooField 9 */
self->fields[8].m_type = LooGetType<float>();
self->fields[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[8].m_serializedWidth = sizeof(float) * 8;
self->fields[8].m_offset = offsetof(loo::core::SAppEvent, scrollX);
self->fields[8].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[8].m_name = "scrollX";

/* LooField 10 */
self->fields[9].m_type = LooGetType<float>();
self->fields[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[9].m_serializedWidth = sizeof(float) * 8;
self->fields[9].m_offset = offsetof(loo::core::SAppEvent, scrollY);
self->fields[9].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[9].m_name = "scrollY";

/* LooField 11 */
self->fields[10].m_type = LooGetType<int>();
self->fields[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[10].m_serializedWidth = sizeof(int) * 8;
self->fields[10].m_offset = offsetof(loo::core::SAppEvent, windowWidth);
self->fields[10].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[10].m_name = "windowWidth";

/* LooField 12 */
self->fields[11].m_type = LooGetType<int>();
self->fields[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[11].m_serializedWidth = sizeof(int) * 8;
self->fields[11].m_offset = offsetof(loo::core::SAppEvent, windowHeight);
self->fields[11].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[11].m_name = "windowHeight";

/* LooField 13 */
self->fields[12].m_type = LooGetType<int>();
self->fields[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[12].m_serializedWidth = sizeof(int) * 8;
self->fields[12].m_offset = offsetof(loo::core::SAppEvent, framebufferWidth);
self->fields[12].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[12].m_name = "framebufferWidth";

/* LooField 14 */
self->fields[13].m_type = LooGetType<int>();
self->fields[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->fields[13].m_serializedWidth = sizeof(int) * 8;
self->fields[13].m_offset = offsetof(loo::core::SAppEvent, framebufferHeight);
self->fields[13].m_qualifier = Qualifier(0, 0, 0, 0, 0, 0);
self->fields[13].m_name = "framebufferHeight";
});
static LooClass cache(
sizeof(loo::core::SAppEvent),
Hash("loo::core::SAppEvent"),
const_cast<LooClass*>(LooGetClass<loo::core::Event>()),
reflected.fields,
reflected.fields + reflected.numFields,
reflected.functions,
reflected.functions + reflected.numFunctions,
"loo::core::SAppEvent",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::SAppEvent>) noexcept
{
return LooGetClass<loo::core::SAppEvent>();
}
} /* namespace detail */
} /* namespace looreflect */

// utils functions for class instance
inline const looreflect::LooType *loo::core::SAppEvent::GetType() const { return looreflect::LooGetClass<loo::core::SAppEvent>();}

/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::TouchType> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::core::TouchType>) noexcept
{
static detail::LooEnumBuilder<loo::core::TouchType, 7> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "Move";
self->enumValues[0].m_tagName = "Move";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "Down";
self->enumValues[1].m_tagName = "Down";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 8;
self->enumValues[2].m_name = "Inrange";
self->enumValues[2].m_tagName = "Inrange";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 16;
self->enumValues[3].m_name = "Primary";
self->enumValues[3].m_tagName = "Primary";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 32;
self->enumValues[4].m_name = "Nocoalesce";
self->enumValues[4].m_tagName = "Nocoalesce";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 64;
self->enumValues[5].m_name = "Pen";
self->enumValues[5].m_tagName = "Pen";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 128;
self->enumValues[6].m_name = "Palm";
self->enumValues[6].m_tagName = "Palm";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::core::TouchType),
Hash("loo::core::TouchType"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::core::TouchType",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::TouchType>) noexcept
{
return LooGetEnum<loo::core::TouchType>();
}
} /* namespace detail */
} /* namespace looreflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::TouchPointState> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::core::TouchPointState>) noexcept
{
static detail::LooEnumBuilder<loo::core::TouchPointState, 4> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "TouchPointPressed";
self->enumValues[0].m_tagName = "TouchPointPressed";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "TouchPointMoved";
self->enumValues[1].m_tagName = "TouchPointMoved";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4;
self->enumValues[2].m_name = "TouchPointStationary";
self->enumValues[2].m_tagName = "TouchPointStationary";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 8;
self->enumValues[3].m_name = "TouchPointReleased";
self->enumValues[3].m_tagName = "TouchPointReleased";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::core::TouchPointState),
Hash("loo::core::TouchPointState"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::core::TouchPointState",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::TouchPointState>) noexcept
{
return LooGetEnum<loo::core::TouchPointState>();
}
} /* namespace detail */
} /* namespace looreflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::KeyCode> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::core::KeyCode>) noexcept
{
static detail::LooEnumBuilder<loo::core::KeyCode, 326> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "None";
self->enumValues[0].m_tagName = "None";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 8;
self->enumValues[1].m_name = "Backspace";
self->enumValues[1].m_tagName = "Backspace";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 9;
self->enumValues[2].m_name = "Tab";
self->enumValues[2].m_tagName = "Tab";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 12;
self->enumValues[3].m_name = "Clear";
self->enumValues[3].m_tagName = "Clear";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 13;
self->enumValues[4].m_name = "Return";
self->enumValues[4].m_tagName = "Return";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 19;
self->enumValues[5].m_name = "Pause";
self->enumValues[5].m_tagName = "Pause";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 27;
self->enumValues[6].m_name = "Escape";
self->enumValues[6].m_tagName = "Escape";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 32;
self->enumValues[7].m_name = "Space";
self->enumValues[7].m_tagName = "Space";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 33;
self->enumValues[8].m_name = "Exclaim";
self->enumValues[8].m_tagName = "Exclaim";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 34;
self->enumValues[9].m_name = "DoubleQuote";
self->enumValues[9].m_tagName = "DoubleQuote";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 35;
self->enumValues[10].m_name = "Hash";
self->enumValues[10].m_tagName = "Hash";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 36;
self->enumValues[11].m_name = "Dollar";
self->enumValues[11].m_tagName = "Dollar";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 37;
self->enumValues[12].m_name = "Percent";
self->enumValues[12].m_tagName = "Percent";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 38;
self->enumValues[13].m_name = "Ampersand";
self->enumValues[13].m_tagName = "Ampersand";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 39;
self->enumValues[14].m_name = "Quote";
self->enumValues[14].m_tagName = "Quote";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 40;
self->enumValues[15].m_name = "LeftParen";
self->enumValues[15].m_tagName = "LeftParen";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;

/* EnumConstant 17 */
self->enumValues[16].m_index = 16;
self->enumValues[16].m_value = 41;
self->enumValues[16].m_name = "RightParen";
self->enumValues[16].m_tagName = "RightParen";
self->enumValues[16].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[16].m_type = nullptr;

/* EnumConstant 18 */
self->enumValues[17].m_index = 17;
self->enumValues[17].m_value = 42;
self->enumValues[17].m_name = "Asterisk";
self->enumValues[17].m_tagName = "Asterisk";
self->enumValues[17].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[17].m_type = nullptr;

/* EnumConstant 19 */
self->enumValues[18].m_index = 18;
self->enumValues[18].m_value = 43;
self->enumValues[18].m_name = "Plus";
self->enumValues[18].m_tagName = "Plus";
self->enumValues[18].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[18].m_type = nullptr;

/* EnumConstant 20 */
self->enumValues[19].m_index = 19;
self->enumValues[19].m_value = 44;
self->enumValues[19].m_name = "Comma";
self->enumValues[19].m_tagName = "Comma";
self->enumValues[19].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[19].m_type = nullptr;

/* EnumConstant 21 */
self->enumValues[20].m_index = 20;
self->enumValues[20].m_value = 45;
self->enumValues[20].m_name = "Minus";
self->enumValues[20].m_tagName = "Minus";
self->enumValues[20].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[20].m_type = nullptr;

/* EnumConstant 22 */
self->enumValues[21].m_index = 21;
self->enumValues[21].m_value = 46;
self->enumValues[21].m_name = "Period";
self->enumValues[21].m_tagName = "Period";
self->enumValues[21].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[21].m_type = nullptr;

/* EnumConstant 23 */
self->enumValues[22].m_index = 22;
self->enumValues[22].m_value = 47;
self->enumValues[22].m_name = "Slash";
self->enumValues[22].m_tagName = "Slash";
self->enumValues[22].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[22].m_type = nullptr;

/* EnumConstant 24 */
self->enumValues[23].m_index = 23;
self->enumValues[23].m_value = 48;
self->enumValues[23].m_name = "Alpha0";
self->enumValues[23].m_tagName = "Alpha0";
self->enumValues[23].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[23].m_type = nullptr;

/* EnumConstant 25 */
self->enumValues[24].m_index = 24;
self->enumValues[24].m_value = 49;
self->enumValues[24].m_name = "Alpha1";
self->enumValues[24].m_tagName = "Alpha1";
self->enumValues[24].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[24].m_type = nullptr;

/* EnumConstant 26 */
self->enumValues[25].m_index = 25;
self->enumValues[25].m_value = 50;
self->enumValues[25].m_name = "Alpha2";
self->enumValues[25].m_tagName = "Alpha2";
self->enumValues[25].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[25].m_type = nullptr;

/* EnumConstant 27 */
self->enumValues[26].m_index = 26;
self->enumValues[26].m_value = 51;
self->enumValues[26].m_name = "Alpha3";
self->enumValues[26].m_tagName = "Alpha3";
self->enumValues[26].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[26].m_type = nullptr;

/* EnumConstant 28 */
self->enumValues[27].m_index = 27;
self->enumValues[27].m_value = 52;
self->enumValues[27].m_name = "Alpha4";
self->enumValues[27].m_tagName = "Alpha4";
self->enumValues[27].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[27].m_type = nullptr;

/* EnumConstant 29 */
self->enumValues[28].m_index = 28;
self->enumValues[28].m_value = 53;
self->enumValues[28].m_name = "Alpha5";
self->enumValues[28].m_tagName = "Alpha5";
self->enumValues[28].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[28].m_type = nullptr;

/* EnumConstant 30 */
self->enumValues[29].m_index = 29;
self->enumValues[29].m_value = 54;
self->enumValues[29].m_name = "Alpha6";
self->enumValues[29].m_tagName = "Alpha6";
self->enumValues[29].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[29].m_type = nullptr;

/* EnumConstant 31 */
self->enumValues[30].m_index = 30;
self->enumValues[30].m_value = 55;
self->enumValues[30].m_name = "Alpha7";
self->enumValues[30].m_tagName = "Alpha7";
self->enumValues[30].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[30].m_type = nullptr;

/* EnumConstant 32 */
self->enumValues[31].m_index = 31;
self->enumValues[31].m_value = 56;
self->enumValues[31].m_name = "Alpha8";
self->enumValues[31].m_tagName = "Alpha8";
self->enumValues[31].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[31].m_type = nullptr;

/* EnumConstant 33 */
self->enumValues[32].m_index = 32;
self->enumValues[32].m_value = 57;
self->enumValues[32].m_name = "Alpha9";
self->enumValues[32].m_tagName = "Alpha9";
self->enumValues[32].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[32].m_type = nullptr;

/* EnumConstant 34 */
self->enumValues[33].m_index = 33;
self->enumValues[33].m_value = 58;
self->enumValues[33].m_name = "Colon";
self->enumValues[33].m_tagName = "Colon";
self->enumValues[33].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[33].m_type = nullptr;

/* EnumConstant 35 */
self->enumValues[34].m_index = 34;
self->enumValues[34].m_value = 59;
self->enumValues[34].m_name = "Semicolon";
self->enumValues[34].m_tagName = "Semicolon";
self->enumValues[34].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[34].m_type = nullptr;

/* EnumConstant 36 */
self->enumValues[35].m_index = 35;
self->enumValues[35].m_value = 60;
self->enumValues[35].m_name = "Less";
self->enumValues[35].m_tagName = "Less";
self->enumValues[35].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[35].m_type = nullptr;

/* EnumConstant 37 */
self->enumValues[36].m_index = 36;
self->enumValues[36].m_value = 61;
self->enumValues[36].m_name = "Equals";
self->enumValues[36].m_tagName = "Equals";
self->enumValues[36].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[36].m_type = nullptr;

/* EnumConstant 38 */
self->enumValues[37].m_index = 37;
self->enumValues[37].m_value = 62;
self->enumValues[37].m_name = "Greater";
self->enumValues[37].m_tagName = "Greater";
self->enumValues[37].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[37].m_type = nullptr;

/* EnumConstant 39 */
self->enumValues[38].m_index = 38;
self->enumValues[38].m_value = 63;
self->enumValues[38].m_name = "Question";
self->enumValues[38].m_tagName = "Question";
self->enumValues[38].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[38].m_type = nullptr;

/* EnumConstant 40 */
self->enumValues[39].m_index = 39;
self->enumValues[39].m_value = 64;
self->enumValues[39].m_name = "At";
self->enumValues[39].m_tagName = "At";
self->enumValues[39].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[39].m_type = nullptr;

/* EnumConstant 41 */
self->enumValues[40].m_index = 40;
self->enumValues[40].m_value = 91;
self->enumValues[40].m_name = "LeftBracket";
self->enumValues[40].m_tagName = "LeftBracket";
self->enumValues[40].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[40].m_type = nullptr;

/* EnumConstant 42 */
self->enumValues[41].m_index = 41;
self->enumValues[41].m_value = 92;
self->enumValues[41].m_name = "Backslash";
self->enumValues[41].m_tagName = "Backslash";
self->enumValues[41].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[41].m_type = nullptr;

/* EnumConstant 43 */
self->enumValues[42].m_index = 42;
self->enumValues[42].m_value = 93;
self->enumValues[42].m_name = "RightBracket";
self->enumValues[42].m_tagName = "RightBracket";
self->enumValues[42].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[42].m_type = nullptr;

/* EnumConstant 44 */
self->enumValues[43].m_index = 43;
self->enumValues[43].m_value = 94;
self->enumValues[43].m_name = "Caret";
self->enumValues[43].m_tagName = "Caret";
self->enumValues[43].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[43].m_type = nullptr;

/* EnumConstant 45 */
self->enumValues[44].m_index = 44;
self->enumValues[44].m_value = 95;
self->enumValues[44].m_name = "Underscore";
self->enumValues[44].m_tagName = "Underscore";
self->enumValues[44].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[44].m_type = nullptr;

/* EnumConstant 46 */
self->enumValues[45].m_index = 45;
self->enumValues[45].m_value = 96;
self->enumValues[45].m_name = "BackQuote";
self->enumValues[45].m_tagName = "BackQuote";
self->enumValues[45].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[45].m_type = nullptr;

/* EnumConstant 47 */
self->enumValues[46].m_index = 46;
self->enumValues[46].m_value = 97;
self->enumValues[46].m_name = "A";
self->enumValues[46].m_tagName = "A";
self->enumValues[46].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[46].m_type = nullptr;

/* EnumConstant 48 */
self->enumValues[47].m_index = 47;
self->enumValues[47].m_value = 98;
self->enumValues[47].m_name = "B";
self->enumValues[47].m_tagName = "B";
self->enumValues[47].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[47].m_type = nullptr;

/* EnumConstant 49 */
self->enumValues[48].m_index = 48;
self->enumValues[48].m_value = 99;
self->enumValues[48].m_name = "C";
self->enumValues[48].m_tagName = "C";
self->enumValues[48].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[48].m_type = nullptr;

/* EnumConstant 50 */
self->enumValues[49].m_index = 49;
self->enumValues[49].m_value = 100;
self->enumValues[49].m_name = "D";
self->enumValues[49].m_tagName = "D";
self->enumValues[49].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[49].m_type = nullptr;

/* EnumConstant 51 */
self->enumValues[50].m_index = 50;
self->enumValues[50].m_value = 101;
self->enumValues[50].m_name = "E";
self->enumValues[50].m_tagName = "E";
self->enumValues[50].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[50].m_type = nullptr;

/* EnumConstant 52 */
self->enumValues[51].m_index = 51;
self->enumValues[51].m_value = 102;
self->enumValues[51].m_name = "F";
self->enumValues[51].m_tagName = "F";
self->enumValues[51].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[51].m_type = nullptr;

/* EnumConstant 53 */
self->enumValues[52].m_index = 52;
self->enumValues[52].m_value = 103;
self->enumValues[52].m_name = "G";
self->enumValues[52].m_tagName = "G";
self->enumValues[52].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[52].m_type = nullptr;

/* EnumConstant 54 */
self->enumValues[53].m_index = 53;
self->enumValues[53].m_value = 104;
self->enumValues[53].m_name = "H";
self->enumValues[53].m_tagName = "H";
self->enumValues[53].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[53].m_type = nullptr;

/* EnumConstant 55 */
self->enumValues[54].m_index = 54;
self->enumValues[54].m_value = 105;
self->enumValues[54].m_name = "I";
self->enumValues[54].m_tagName = "I";
self->enumValues[54].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[54].m_type = nullptr;

/* EnumConstant 56 */
self->enumValues[55].m_index = 55;
self->enumValues[55].m_value = 106;
self->enumValues[55].m_name = "J";
self->enumValues[55].m_tagName = "J";
self->enumValues[55].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[55].m_type = nullptr;

/* EnumConstant 57 */
self->enumValues[56].m_index = 56;
self->enumValues[56].m_value = 107;
self->enumValues[56].m_name = "K";
self->enumValues[56].m_tagName = "K";
self->enumValues[56].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[56].m_type = nullptr;

/* EnumConstant 58 */
self->enumValues[57].m_index = 57;
self->enumValues[57].m_value = 108;
self->enumValues[57].m_name = "L";
self->enumValues[57].m_tagName = "L";
self->enumValues[57].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[57].m_type = nullptr;

/* EnumConstant 59 */
self->enumValues[58].m_index = 58;
self->enumValues[58].m_value = 109;
self->enumValues[58].m_name = "M";
self->enumValues[58].m_tagName = "M";
self->enumValues[58].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[58].m_type = nullptr;

/* EnumConstant 60 */
self->enumValues[59].m_index = 59;
self->enumValues[59].m_value = 110;
self->enumValues[59].m_name = "N";
self->enumValues[59].m_tagName = "N";
self->enumValues[59].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[59].m_type = nullptr;

/* EnumConstant 61 */
self->enumValues[60].m_index = 60;
self->enumValues[60].m_value = 111;
self->enumValues[60].m_name = "O";
self->enumValues[60].m_tagName = "O";
self->enumValues[60].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[60].m_type = nullptr;

/* EnumConstant 62 */
self->enumValues[61].m_index = 61;
self->enumValues[61].m_value = 112;
self->enumValues[61].m_name = "P";
self->enumValues[61].m_tagName = "P";
self->enumValues[61].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[61].m_type = nullptr;

/* EnumConstant 63 */
self->enumValues[62].m_index = 62;
self->enumValues[62].m_value = 113;
self->enumValues[62].m_name = "Q";
self->enumValues[62].m_tagName = "Q";
self->enumValues[62].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[62].m_type = nullptr;

/* EnumConstant 64 */
self->enumValues[63].m_index = 63;
self->enumValues[63].m_value = 114;
self->enumValues[63].m_name = "R";
self->enumValues[63].m_tagName = "R";
self->enumValues[63].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[63].m_type = nullptr;

/* EnumConstant 65 */
self->enumValues[64].m_index = 64;
self->enumValues[64].m_value = 115;
self->enumValues[64].m_name = "S";
self->enumValues[64].m_tagName = "S";
self->enumValues[64].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[64].m_type = nullptr;

/* EnumConstant 66 */
self->enumValues[65].m_index = 65;
self->enumValues[65].m_value = 116;
self->enumValues[65].m_name = "T";
self->enumValues[65].m_tagName = "T";
self->enumValues[65].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[65].m_type = nullptr;

/* EnumConstant 67 */
self->enumValues[66].m_index = 66;
self->enumValues[66].m_value = 117;
self->enumValues[66].m_name = "U";
self->enumValues[66].m_tagName = "U";
self->enumValues[66].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[66].m_type = nullptr;

/* EnumConstant 68 */
self->enumValues[67].m_index = 67;
self->enumValues[67].m_value = 118;
self->enumValues[67].m_name = "V";
self->enumValues[67].m_tagName = "V";
self->enumValues[67].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[67].m_type = nullptr;

/* EnumConstant 69 */
self->enumValues[68].m_index = 68;
self->enumValues[68].m_value = 119;
self->enumValues[68].m_name = "W";
self->enumValues[68].m_tagName = "W";
self->enumValues[68].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[68].m_type = nullptr;

/* EnumConstant 70 */
self->enumValues[69].m_index = 69;
self->enumValues[69].m_value = 120;
self->enumValues[69].m_name = "X";
self->enumValues[69].m_tagName = "X";
self->enumValues[69].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[69].m_type = nullptr;

/* EnumConstant 71 */
self->enumValues[70].m_index = 70;
self->enumValues[70].m_value = 121;
self->enumValues[70].m_name = "Y";
self->enumValues[70].m_tagName = "Y";
self->enumValues[70].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[70].m_type = nullptr;

/* EnumConstant 72 */
self->enumValues[71].m_index = 71;
self->enumValues[71].m_value = 122;
self->enumValues[71].m_name = "Z";
self->enumValues[71].m_tagName = "Z";
self->enumValues[71].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[71].m_type = nullptr;

/* EnumConstant 73 */
self->enumValues[72].m_index = 72;
self->enumValues[72].m_value = 123;
self->enumValues[72].m_name = "LeftCurlyBracket";
self->enumValues[72].m_tagName = "LeftCurlyBracket";
self->enumValues[72].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[72].m_type = nullptr;

/* EnumConstant 74 */
self->enumValues[73].m_index = 73;
self->enumValues[73].m_value = 124;
self->enumValues[73].m_name = "Pipe";
self->enumValues[73].m_tagName = "Pipe";
self->enumValues[73].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[73].m_type = nullptr;

/* EnumConstant 75 */
self->enumValues[74].m_index = 74;
self->enumValues[74].m_value = 125;
self->enumValues[74].m_name = "RightCurlyBracket";
self->enumValues[74].m_tagName = "RightCurlyBracket";
self->enumValues[74].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[74].m_type = nullptr;

/* EnumConstant 76 */
self->enumValues[75].m_index = 75;
self->enumValues[75].m_value = 126;
self->enumValues[75].m_name = "Tilde";
self->enumValues[75].m_tagName = "Tilde";
self->enumValues[75].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[75].m_type = nullptr;

/* EnumConstant 77 */
self->enumValues[76].m_index = 76;
self->enumValues[76].m_value = 127;
self->enumValues[76].m_name = "Delete";
self->enumValues[76].m_tagName = "Delete";
self->enumValues[76].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[76].m_type = nullptr;

/* EnumConstant 78 */
self->enumValues[77].m_index = 77;
self->enumValues[77].m_value = 256;
self->enumValues[77].m_name = "Keypad0";
self->enumValues[77].m_tagName = "Keypad0";
self->enumValues[77].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[77].m_type = nullptr;

/* EnumConstant 79 */
self->enumValues[78].m_index = 78;
self->enumValues[78].m_value = 257;
self->enumValues[78].m_name = "Keypad1";
self->enumValues[78].m_tagName = "Keypad1";
self->enumValues[78].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[78].m_type = nullptr;

/* EnumConstant 80 */
self->enumValues[79].m_index = 79;
self->enumValues[79].m_value = 258;
self->enumValues[79].m_name = "Keypad2";
self->enumValues[79].m_tagName = "Keypad2";
self->enumValues[79].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[79].m_type = nullptr;

/* EnumConstant 81 */
self->enumValues[80].m_index = 80;
self->enumValues[80].m_value = 259;
self->enumValues[80].m_name = "Keypad3";
self->enumValues[80].m_tagName = "Keypad3";
self->enumValues[80].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[80].m_type = nullptr;

/* EnumConstant 82 */
self->enumValues[81].m_index = 81;
self->enumValues[81].m_value = 260;
self->enumValues[81].m_name = "Keypad4";
self->enumValues[81].m_tagName = "Keypad4";
self->enumValues[81].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[81].m_type = nullptr;

/* EnumConstant 83 */
self->enumValues[82].m_index = 82;
self->enumValues[82].m_value = 261;
self->enumValues[82].m_name = "Keypad5";
self->enumValues[82].m_tagName = "Keypad5";
self->enumValues[82].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[82].m_type = nullptr;

/* EnumConstant 84 */
self->enumValues[83].m_index = 83;
self->enumValues[83].m_value = 262;
self->enumValues[83].m_name = "Keypad6";
self->enumValues[83].m_tagName = "Keypad6";
self->enumValues[83].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[83].m_type = nullptr;

/* EnumConstant 85 */
self->enumValues[84].m_index = 84;
self->enumValues[84].m_value = 263;
self->enumValues[84].m_name = "Keypad7";
self->enumValues[84].m_tagName = "Keypad7";
self->enumValues[84].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[84].m_type = nullptr;

/* EnumConstant 86 */
self->enumValues[85].m_index = 85;
self->enumValues[85].m_value = 264;
self->enumValues[85].m_name = "Keypad8";
self->enumValues[85].m_tagName = "Keypad8";
self->enumValues[85].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[85].m_type = nullptr;

/* EnumConstant 87 */
self->enumValues[86].m_index = 86;
self->enumValues[86].m_value = 265;
self->enumValues[86].m_name = "Keypad9";
self->enumValues[86].m_tagName = "Keypad9";
self->enumValues[86].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[86].m_type = nullptr;

/* EnumConstant 88 */
self->enumValues[87].m_index = 87;
self->enumValues[87].m_value = 266;
self->enumValues[87].m_name = "KeypadPeriod";
self->enumValues[87].m_tagName = "KeypadPeriod";
self->enumValues[87].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[87].m_type = nullptr;

/* EnumConstant 89 */
self->enumValues[88].m_index = 88;
self->enumValues[88].m_value = 267;
self->enumValues[88].m_name = "KeypadDivide";
self->enumValues[88].m_tagName = "KeypadDivide";
self->enumValues[88].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[88].m_type = nullptr;

/* EnumConstant 90 */
self->enumValues[89].m_index = 89;
self->enumValues[89].m_value = 268;
self->enumValues[89].m_name = "KeypadMultiply";
self->enumValues[89].m_tagName = "KeypadMultiply";
self->enumValues[89].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[89].m_type = nullptr;

/* EnumConstant 91 */
self->enumValues[90].m_index = 90;
self->enumValues[90].m_value = 269;
self->enumValues[90].m_name = "KeypadMinus";
self->enumValues[90].m_tagName = "KeypadMinus";
self->enumValues[90].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[90].m_type = nullptr;

/* EnumConstant 92 */
self->enumValues[91].m_index = 91;
self->enumValues[91].m_value = 270;
self->enumValues[91].m_name = "KeypadPlus";
self->enumValues[91].m_tagName = "KeypadPlus";
self->enumValues[91].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[91].m_type = nullptr;

/* EnumConstant 93 */
self->enumValues[92].m_index = 92;
self->enumValues[92].m_value = 271;
self->enumValues[92].m_name = "KeypadEnter";
self->enumValues[92].m_tagName = "KeypadEnter";
self->enumValues[92].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[92].m_type = nullptr;

/* EnumConstant 94 */
self->enumValues[93].m_index = 93;
self->enumValues[93].m_value = 272;
self->enumValues[93].m_name = "KeypadEquals";
self->enumValues[93].m_tagName = "KeypadEquals";
self->enumValues[93].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[93].m_type = nullptr;

/* EnumConstant 95 */
self->enumValues[94].m_index = 94;
self->enumValues[94].m_value = 273;
self->enumValues[94].m_name = "UpArrow";
self->enumValues[94].m_tagName = "UpArrow";
self->enumValues[94].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[94].m_type = nullptr;

/* EnumConstant 96 */
self->enumValues[95].m_index = 95;
self->enumValues[95].m_value = 274;
self->enumValues[95].m_name = "DownArrow";
self->enumValues[95].m_tagName = "DownArrow";
self->enumValues[95].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[95].m_type = nullptr;

/* EnumConstant 97 */
self->enumValues[96].m_index = 96;
self->enumValues[96].m_value = 275;
self->enumValues[96].m_name = "RightArrow";
self->enumValues[96].m_tagName = "RightArrow";
self->enumValues[96].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[96].m_type = nullptr;

/* EnumConstant 98 */
self->enumValues[97].m_index = 97;
self->enumValues[97].m_value = 276;
self->enumValues[97].m_name = "LeftArrow";
self->enumValues[97].m_tagName = "LeftArrow";
self->enumValues[97].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[97].m_type = nullptr;

/* EnumConstant 99 */
self->enumValues[98].m_index = 98;
self->enumValues[98].m_value = 277;
self->enumValues[98].m_name = "Insert";
self->enumValues[98].m_tagName = "Insert";
self->enumValues[98].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[98].m_type = nullptr;

/* EnumConstant 100 */
self->enumValues[99].m_index = 99;
self->enumValues[99].m_value = 278;
self->enumValues[99].m_name = "Home";
self->enumValues[99].m_tagName = "Home";
self->enumValues[99].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[99].m_type = nullptr;

/* EnumConstant 101 */
self->enumValues[100].m_index = 100;
self->enumValues[100].m_value = 279;
self->enumValues[100].m_name = "End";
self->enumValues[100].m_tagName = "End";
self->enumValues[100].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[100].m_type = nullptr;

/* EnumConstant 102 */
self->enumValues[101].m_index = 101;
self->enumValues[101].m_value = 280;
self->enumValues[101].m_name = "PageUp";
self->enumValues[101].m_tagName = "PageUp";
self->enumValues[101].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[101].m_type = nullptr;

/* EnumConstant 103 */
self->enumValues[102].m_index = 102;
self->enumValues[102].m_value = 281;
self->enumValues[102].m_name = "PageDown";
self->enumValues[102].m_tagName = "PageDown";
self->enumValues[102].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[102].m_type = nullptr;

/* EnumConstant 104 */
self->enumValues[103].m_index = 103;
self->enumValues[103].m_value = 282;
self->enumValues[103].m_name = "F1";
self->enumValues[103].m_tagName = "F1";
self->enumValues[103].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[103].m_type = nullptr;

/* EnumConstant 105 */
self->enumValues[104].m_index = 104;
self->enumValues[104].m_value = 283;
self->enumValues[104].m_name = "F2";
self->enumValues[104].m_tagName = "F2";
self->enumValues[104].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[104].m_type = nullptr;

/* EnumConstant 106 */
self->enumValues[105].m_index = 105;
self->enumValues[105].m_value = 284;
self->enumValues[105].m_name = "F3";
self->enumValues[105].m_tagName = "F3";
self->enumValues[105].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[105].m_type = nullptr;

/* EnumConstant 107 */
self->enumValues[106].m_index = 106;
self->enumValues[106].m_value = 285;
self->enumValues[106].m_name = "F4";
self->enumValues[106].m_tagName = "F4";
self->enumValues[106].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[106].m_type = nullptr;

/* EnumConstant 108 */
self->enumValues[107].m_index = 107;
self->enumValues[107].m_value = 286;
self->enumValues[107].m_name = "F5";
self->enumValues[107].m_tagName = "F5";
self->enumValues[107].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[107].m_type = nullptr;

/* EnumConstant 109 */
self->enumValues[108].m_index = 108;
self->enumValues[108].m_value = 287;
self->enumValues[108].m_name = "F6";
self->enumValues[108].m_tagName = "F6";
self->enumValues[108].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[108].m_type = nullptr;

/* EnumConstant 110 */
self->enumValues[109].m_index = 109;
self->enumValues[109].m_value = 288;
self->enumValues[109].m_name = "F7";
self->enumValues[109].m_tagName = "F7";
self->enumValues[109].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[109].m_type = nullptr;

/* EnumConstant 111 */
self->enumValues[110].m_index = 110;
self->enumValues[110].m_value = 289;
self->enumValues[110].m_name = "F8";
self->enumValues[110].m_tagName = "F8";
self->enumValues[110].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[110].m_type = nullptr;

/* EnumConstant 112 */
self->enumValues[111].m_index = 111;
self->enumValues[111].m_value = 290;
self->enumValues[111].m_name = "F9";
self->enumValues[111].m_tagName = "F9";
self->enumValues[111].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[111].m_type = nullptr;

/* EnumConstant 113 */
self->enumValues[112].m_index = 112;
self->enumValues[112].m_value = 291;
self->enumValues[112].m_name = "F10";
self->enumValues[112].m_tagName = "F10";
self->enumValues[112].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[112].m_type = nullptr;

/* EnumConstant 114 */
self->enumValues[113].m_index = 113;
self->enumValues[113].m_value = 292;
self->enumValues[113].m_name = "F11";
self->enumValues[113].m_tagName = "F11";
self->enumValues[113].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[113].m_type = nullptr;

/* EnumConstant 115 */
self->enumValues[114].m_index = 114;
self->enumValues[114].m_value = 293;
self->enumValues[114].m_name = "F12";
self->enumValues[114].m_tagName = "F12";
self->enumValues[114].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[114].m_type = nullptr;

/* EnumConstant 116 */
self->enumValues[115].m_index = 115;
self->enumValues[115].m_value = 294;
self->enumValues[115].m_name = "F13";
self->enumValues[115].m_tagName = "F13";
self->enumValues[115].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[115].m_type = nullptr;

/* EnumConstant 117 */
self->enumValues[116].m_index = 116;
self->enumValues[116].m_value = 295;
self->enumValues[116].m_name = "F14";
self->enumValues[116].m_tagName = "F14";
self->enumValues[116].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[116].m_type = nullptr;

/* EnumConstant 118 */
self->enumValues[117].m_index = 117;
self->enumValues[117].m_value = 296;
self->enumValues[117].m_name = "F15";
self->enumValues[117].m_tagName = "F15";
self->enumValues[117].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[117].m_type = nullptr;

/* EnumConstant 119 */
self->enumValues[118].m_index = 118;
self->enumValues[118].m_value = 300;
self->enumValues[118].m_name = "Numlock";
self->enumValues[118].m_tagName = "Numlock";
self->enumValues[118].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[118].m_type = nullptr;

/* EnumConstant 120 */
self->enumValues[119].m_index = 119;
self->enumValues[119].m_value = 301;
self->enumValues[119].m_name = "CapsLock";
self->enumValues[119].m_tagName = "CapsLock";
self->enumValues[119].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[119].m_type = nullptr;

/* EnumConstant 121 */
self->enumValues[120].m_index = 120;
self->enumValues[120].m_value = 302;
self->enumValues[120].m_name = "ScrollLock";
self->enumValues[120].m_tagName = "ScrollLock";
self->enumValues[120].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[120].m_type = nullptr;

/* EnumConstant 122 */
self->enumValues[121].m_index = 121;
self->enumValues[121].m_value = 303;
self->enumValues[121].m_name = "RightShift";
self->enumValues[121].m_tagName = "RightShift";
self->enumValues[121].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[121].m_type = nullptr;

/* EnumConstant 123 */
self->enumValues[122].m_index = 122;
self->enumValues[122].m_value = 304;
self->enumValues[122].m_name = "LeftShift";
self->enumValues[122].m_tagName = "LeftShift";
self->enumValues[122].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[122].m_type = nullptr;

/* EnumConstant 124 */
self->enumValues[123].m_index = 123;
self->enumValues[123].m_value = 305;
self->enumValues[123].m_name = "RightControl";
self->enumValues[123].m_tagName = "RightControl";
self->enumValues[123].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[123].m_type = nullptr;

/* EnumConstant 125 */
self->enumValues[124].m_index = 124;
self->enumValues[124].m_value = 306;
self->enumValues[124].m_name = "LeftControl";
self->enumValues[124].m_tagName = "LeftControl";
self->enumValues[124].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[124].m_type = nullptr;

/* EnumConstant 126 */
self->enumValues[125].m_index = 125;
self->enumValues[125].m_value = 307;
self->enumValues[125].m_name = "RightAlt";
self->enumValues[125].m_tagName = "RightAlt";
self->enumValues[125].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[125].m_type = nullptr;

/* EnumConstant 127 */
self->enumValues[126].m_index = 126;
self->enumValues[126].m_value = 308;
self->enumValues[126].m_name = "LeftAlt";
self->enumValues[126].m_tagName = "LeftAlt";
self->enumValues[126].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[126].m_type = nullptr;

/* EnumConstant 128 */
self->enumValues[127].m_index = 127;
self->enumValues[127].m_value = 309;
self->enumValues[127].m_name = "RightCommand";
self->enumValues[127].m_tagName = "RightCommand";
self->enumValues[127].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[127].m_type = nullptr;

/* EnumConstant 129 */
self->enumValues[128].m_index = 128;
self->enumValues[128].m_value = 309;
self->enumValues[128].m_name = "RightApple";
self->enumValues[128].m_tagName = "RightApple";
self->enumValues[128].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[128].m_type = nullptr;

/* EnumConstant 130 */
self->enumValues[129].m_index = 129;
self->enumValues[129].m_value = 310;
self->enumValues[129].m_name = "LeftCommand";
self->enumValues[129].m_tagName = "LeftCommand";
self->enumValues[129].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[129].m_type = nullptr;

/* EnumConstant 131 */
self->enumValues[130].m_index = 130;
self->enumValues[130].m_value = 310;
self->enumValues[130].m_name = "LeftApple";
self->enumValues[130].m_tagName = "LeftApple";
self->enumValues[130].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[130].m_type = nullptr;

/* EnumConstant 132 */
self->enumValues[131].m_index = 131;
self->enumValues[131].m_value = 311;
self->enumValues[131].m_name = "LeftWindows";
self->enumValues[131].m_tagName = "LeftWindows";
self->enumValues[131].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[131].m_type = nullptr;

/* EnumConstant 133 */
self->enumValues[132].m_index = 132;
self->enumValues[132].m_value = 312;
self->enumValues[132].m_name = "RightWindows";
self->enumValues[132].m_tagName = "RightWindows";
self->enumValues[132].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[132].m_type = nullptr;

/* EnumConstant 134 */
self->enumValues[133].m_index = 133;
self->enumValues[133].m_value = 313;
self->enumValues[133].m_name = "AltGr";
self->enumValues[133].m_tagName = "AltGr";
self->enumValues[133].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[133].m_type = nullptr;

/* EnumConstant 135 */
self->enumValues[134].m_index = 134;
self->enumValues[134].m_value = 315;
self->enumValues[134].m_name = "Help";
self->enumValues[134].m_tagName = "Help";
self->enumValues[134].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[134].m_type = nullptr;

/* EnumConstant 136 */
self->enumValues[135].m_index = 135;
self->enumValues[135].m_value = 316;
self->enumValues[135].m_name = "Print";
self->enumValues[135].m_tagName = "Print";
self->enumValues[135].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[135].m_type = nullptr;

/* EnumConstant 137 */
self->enumValues[136].m_index = 136;
self->enumValues[136].m_value = 317;
self->enumValues[136].m_name = "SysReq";
self->enumValues[136].m_tagName = "SysReq";
self->enumValues[136].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[136].m_type = nullptr;

/* EnumConstant 138 */
self->enumValues[137].m_index = 137;
self->enumValues[137].m_value = 318;
self->enumValues[137].m_name = "Break";
self->enumValues[137].m_tagName = "Break";
self->enumValues[137].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[137].m_type = nullptr;

/* EnumConstant 139 */
self->enumValues[138].m_index = 138;
self->enumValues[138].m_value = 319;
self->enumValues[138].m_name = "Menu";
self->enumValues[138].m_tagName = "Menu";
self->enumValues[138].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[138].m_type = nullptr;

/* EnumConstant 140 */
self->enumValues[139].m_index = 139;
self->enumValues[139].m_value = 323;
self->enumValues[139].m_name = "Mouse0";
self->enumValues[139].m_tagName = "Mouse0";
self->enumValues[139].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[139].m_type = nullptr;

/* EnumConstant 141 */
self->enumValues[140].m_index = 140;
self->enumValues[140].m_value = 324;
self->enumValues[140].m_name = "Mouse1";
self->enumValues[140].m_tagName = "Mouse1";
self->enumValues[140].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[140].m_type = nullptr;

/* EnumConstant 142 */
self->enumValues[141].m_index = 141;
self->enumValues[141].m_value = 325;
self->enumValues[141].m_name = "Mouse2";
self->enumValues[141].m_tagName = "Mouse2";
self->enumValues[141].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[141].m_type = nullptr;

/* EnumConstant 143 */
self->enumValues[142].m_index = 142;
self->enumValues[142].m_value = 326;
self->enumValues[142].m_name = "Mouse3";
self->enumValues[142].m_tagName = "Mouse3";
self->enumValues[142].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[142].m_type = nullptr;

/* EnumConstant 144 */
self->enumValues[143].m_index = 143;
self->enumValues[143].m_value = 327;
self->enumValues[143].m_name = "Mouse4";
self->enumValues[143].m_tagName = "Mouse4";
self->enumValues[143].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[143].m_type = nullptr;

/* EnumConstant 145 */
self->enumValues[144].m_index = 144;
self->enumValues[144].m_value = 328;
self->enumValues[144].m_name = "Mouse5";
self->enumValues[144].m_tagName = "Mouse5";
self->enumValues[144].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[144].m_type = nullptr;

/* EnumConstant 146 */
self->enumValues[145].m_index = 145;
self->enumValues[145].m_value = 329;
self->enumValues[145].m_name = "Mouse6";
self->enumValues[145].m_tagName = "Mouse6";
self->enumValues[145].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[145].m_type = nullptr;

/* EnumConstant 147 */
self->enumValues[146].m_index = 146;
self->enumValues[146].m_value = 330;
self->enumValues[146].m_name = "JoystickButton0";
self->enumValues[146].m_tagName = "JoystickButton0";
self->enumValues[146].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[146].m_type = nullptr;

/* EnumConstant 148 */
self->enumValues[147].m_index = 147;
self->enumValues[147].m_value = 331;
self->enumValues[147].m_name = "JoystickButton1";
self->enumValues[147].m_tagName = "JoystickButton1";
self->enumValues[147].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[147].m_type = nullptr;

/* EnumConstant 149 */
self->enumValues[148].m_index = 148;
self->enumValues[148].m_value = 332;
self->enumValues[148].m_name = "JoystickButton2";
self->enumValues[148].m_tagName = "JoystickButton2";
self->enumValues[148].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[148].m_type = nullptr;

/* EnumConstant 150 */
self->enumValues[149].m_index = 149;
self->enumValues[149].m_value = 333;
self->enumValues[149].m_name = "JoystickButton3";
self->enumValues[149].m_tagName = "JoystickButton3";
self->enumValues[149].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[149].m_type = nullptr;

/* EnumConstant 151 */
self->enumValues[150].m_index = 150;
self->enumValues[150].m_value = 334;
self->enumValues[150].m_name = "JoystickButton4";
self->enumValues[150].m_tagName = "JoystickButton4";
self->enumValues[150].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[150].m_type = nullptr;

/* EnumConstant 152 */
self->enumValues[151].m_index = 151;
self->enumValues[151].m_value = 335;
self->enumValues[151].m_name = "JoystickButton5";
self->enumValues[151].m_tagName = "JoystickButton5";
self->enumValues[151].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[151].m_type = nullptr;

/* EnumConstant 153 */
self->enumValues[152].m_index = 152;
self->enumValues[152].m_value = 336;
self->enumValues[152].m_name = "JoystickButton6";
self->enumValues[152].m_tagName = "JoystickButton6";
self->enumValues[152].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[152].m_type = nullptr;

/* EnumConstant 154 */
self->enumValues[153].m_index = 153;
self->enumValues[153].m_value = 337;
self->enumValues[153].m_name = "JoystickButton7";
self->enumValues[153].m_tagName = "JoystickButton7";
self->enumValues[153].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[153].m_type = nullptr;

/* EnumConstant 155 */
self->enumValues[154].m_index = 154;
self->enumValues[154].m_value = 338;
self->enumValues[154].m_name = "JoystickButton8";
self->enumValues[154].m_tagName = "JoystickButton8";
self->enumValues[154].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[154].m_type = nullptr;

/* EnumConstant 156 */
self->enumValues[155].m_index = 155;
self->enumValues[155].m_value = 339;
self->enumValues[155].m_name = "JoystickButton9";
self->enumValues[155].m_tagName = "JoystickButton9";
self->enumValues[155].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[155].m_type = nullptr;

/* EnumConstant 157 */
self->enumValues[156].m_index = 156;
self->enumValues[156].m_value = 340;
self->enumValues[156].m_name = "JoystickButton10";
self->enumValues[156].m_tagName = "JoystickButton10";
self->enumValues[156].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[156].m_type = nullptr;

/* EnumConstant 158 */
self->enumValues[157].m_index = 157;
self->enumValues[157].m_value = 341;
self->enumValues[157].m_name = "JoystickButton11";
self->enumValues[157].m_tagName = "JoystickButton11";
self->enumValues[157].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[157].m_type = nullptr;

/* EnumConstant 159 */
self->enumValues[158].m_index = 158;
self->enumValues[158].m_value = 342;
self->enumValues[158].m_name = "JoystickButton12";
self->enumValues[158].m_tagName = "JoystickButton12";
self->enumValues[158].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[158].m_type = nullptr;

/* EnumConstant 160 */
self->enumValues[159].m_index = 159;
self->enumValues[159].m_value = 343;
self->enumValues[159].m_name = "JoystickButton13";
self->enumValues[159].m_tagName = "JoystickButton13";
self->enumValues[159].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[159].m_type = nullptr;

/* EnumConstant 161 */
self->enumValues[160].m_index = 160;
self->enumValues[160].m_value = 344;
self->enumValues[160].m_name = "JoystickButton14";
self->enumValues[160].m_tagName = "JoystickButton14";
self->enumValues[160].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[160].m_type = nullptr;

/* EnumConstant 162 */
self->enumValues[161].m_index = 161;
self->enumValues[161].m_value = 345;
self->enumValues[161].m_name = "JoystickButton15";
self->enumValues[161].m_tagName = "JoystickButton15";
self->enumValues[161].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[161].m_type = nullptr;

/* EnumConstant 163 */
self->enumValues[162].m_index = 162;
self->enumValues[162].m_value = 346;
self->enumValues[162].m_name = "JoystickButton16";
self->enumValues[162].m_tagName = "JoystickButton16";
self->enumValues[162].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[162].m_type = nullptr;

/* EnumConstant 164 */
self->enumValues[163].m_index = 163;
self->enumValues[163].m_value = 347;
self->enumValues[163].m_name = "JoystickButton17";
self->enumValues[163].m_tagName = "JoystickButton17";
self->enumValues[163].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[163].m_type = nullptr;

/* EnumConstant 165 */
self->enumValues[164].m_index = 164;
self->enumValues[164].m_value = 348;
self->enumValues[164].m_name = "JoystickButton18";
self->enumValues[164].m_tagName = "JoystickButton18";
self->enumValues[164].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[164].m_type = nullptr;

/* EnumConstant 166 */
self->enumValues[165].m_index = 165;
self->enumValues[165].m_value = 349;
self->enumValues[165].m_name = "JoystickButton19";
self->enumValues[165].m_tagName = "JoystickButton19";
self->enumValues[165].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[165].m_type = nullptr;

/* EnumConstant 167 */
self->enumValues[166].m_index = 166;
self->enumValues[166].m_value = 350;
self->enumValues[166].m_name = "Joystick1Button0";
self->enumValues[166].m_tagName = "Joystick1Button0";
self->enumValues[166].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[166].m_type = nullptr;

/* EnumConstant 168 */
self->enumValues[167].m_index = 167;
self->enumValues[167].m_value = 351;
self->enumValues[167].m_name = "Joystick1Button1";
self->enumValues[167].m_tagName = "Joystick1Button1";
self->enumValues[167].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[167].m_type = nullptr;

/* EnumConstant 169 */
self->enumValues[168].m_index = 168;
self->enumValues[168].m_value = 352;
self->enumValues[168].m_name = "Joystick1Button2";
self->enumValues[168].m_tagName = "Joystick1Button2";
self->enumValues[168].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[168].m_type = nullptr;

/* EnumConstant 170 */
self->enumValues[169].m_index = 169;
self->enumValues[169].m_value = 353;
self->enumValues[169].m_name = "Joystick1Button3";
self->enumValues[169].m_tagName = "Joystick1Button3";
self->enumValues[169].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[169].m_type = nullptr;

/* EnumConstant 171 */
self->enumValues[170].m_index = 170;
self->enumValues[170].m_value = 354;
self->enumValues[170].m_name = "Joystick1Button4";
self->enumValues[170].m_tagName = "Joystick1Button4";
self->enumValues[170].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[170].m_type = nullptr;

/* EnumConstant 172 */
self->enumValues[171].m_index = 171;
self->enumValues[171].m_value = 355;
self->enumValues[171].m_name = "Joystick1Button5";
self->enumValues[171].m_tagName = "Joystick1Button5";
self->enumValues[171].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[171].m_type = nullptr;

/* EnumConstant 173 */
self->enumValues[172].m_index = 172;
self->enumValues[172].m_value = 356;
self->enumValues[172].m_name = "Joystick1Button6";
self->enumValues[172].m_tagName = "Joystick1Button6";
self->enumValues[172].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[172].m_type = nullptr;

/* EnumConstant 174 */
self->enumValues[173].m_index = 173;
self->enumValues[173].m_value = 357;
self->enumValues[173].m_name = "Joystick1Button7";
self->enumValues[173].m_tagName = "Joystick1Button7";
self->enumValues[173].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[173].m_type = nullptr;

/* EnumConstant 175 */
self->enumValues[174].m_index = 174;
self->enumValues[174].m_value = 358;
self->enumValues[174].m_name = "Joystick1Button8";
self->enumValues[174].m_tagName = "Joystick1Button8";
self->enumValues[174].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[174].m_type = nullptr;

/* EnumConstant 176 */
self->enumValues[175].m_index = 175;
self->enumValues[175].m_value = 359;
self->enumValues[175].m_name = "Joystick1Button9";
self->enumValues[175].m_tagName = "Joystick1Button9";
self->enumValues[175].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[175].m_type = nullptr;

/* EnumConstant 177 */
self->enumValues[176].m_index = 176;
self->enumValues[176].m_value = 360;
self->enumValues[176].m_name = "Joystick1Button10";
self->enumValues[176].m_tagName = "Joystick1Button10";
self->enumValues[176].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[176].m_type = nullptr;

/* EnumConstant 178 */
self->enumValues[177].m_index = 177;
self->enumValues[177].m_value = 361;
self->enumValues[177].m_name = "Joystick1Button11";
self->enumValues[177].m_tagName = "Joystick1Button11";
self->enumValues[177].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[177].m_type = nullptr;

/* EnumConstant 179 */
self->enumValues[178].m_index = 178;
self->enumValues[178].m_value = 362;
self->enumValues[178].m_name = "Joystick1Button12";
self->enumValues[178].m_tagName = "Joystick1Button12";
self->enumValues[178].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[178].m_type = nullptr;

/* EnumConstant 180 */
self->enumValues[179].m_index = 179;
self->enumValues[179].m_value = 363;
self->enumValues[179].m_name = "Joystick1Button13";
self->enumValues[179].m_tagName = "Joystick1Button13";
self->enumValues[179].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[179].m_type = nullptr;

/* EnumConstant 181 */
self->enumValues[180].m_index = 180;
self->enumValues[180].m_value = 364;
self->enumValues[180].m_name = "Joystick1Button14";
self->enumValues[180].m_tagName = "Joystick1Button14";
self->enumValues[180].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[180].m_type = nullptr;

/* EnumConstant 182 */
self->enumValues[181].m_index = 181;
self->enumValues[181].m_value = 365;
self->enumValues[181].m_name = "Joystick1Button15";
self->enumValues[181].m_tagName = "Joystick1Button15";
self->enumValues[181].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[181].m_type = nullptr;

/* EnumConstant 183 */
self->enumValues[182].m_index = 182;
self->enumValues[182].m_value = 366;
self->enumValues[182].m_name = "Joystick1Button16";
self->enumValues[182].m_tagName = "Joystick1Button16";
self->enumValues[182].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[182].m_type = nullptr;

/* EnumConstant 184 */
self->enumValues[183].m_index = 183;
self->enumValues[183].m_value = 367;
self->enumValues[183].m_name = "Joystick1Button17";
self->enumValues[183].m_tagName = "Joystick1Button17";
self->enumValues[183].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[183].m_type = nullptr;

/* EnumConstant 185 */
self->enumValues[184].m_index = 184;
self->enumValues[184].m_value = 368;
self->enumValues[184].m_name = "Joystick1Button18";
self->enumValues[184].m_tagName = "Joystick1Button18";
self->enumValues[184].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[184].m_type = nullptr;

/* EnumConstant 186 */
self->enumValues[185].m_index = 185;
self->enumValues[185].m_value = 369;
self->enumValues[185].m_name = "Joystick1Button19";
self->enumValues[185].m_tagName = "Joystick1Button19";
self->enumValues[185].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[185].m_type = nullptr;

/* EnumConstant 187 */
self->enumValues[186].m_index = 186;
self->enumValues[186].m_value = 370;
self->enumValues[186].m_name = "Joystick2Button0";
self->enumValues[186].m_tagName = "Joystick2Button0";
self->enumValues[186].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[186].m_type = nullptr;

/* EnumConstant 188 */
self->enumValues[187].m_index = 187;
self->enumValues[187].m_value = 371;
self->enumValues[187].m_name = "Joystick2Button1";
self->enumValues[187].m_tagName = "Joystick2Button1";
self->enumValues[187].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[187].m_type = nullptr;

/* EnumConstant 189 */
self->enumValues[188].m_index = 188;
self->enumValues[188].m_value = 372;
self->enumValues[188].m_name = "Joystick2Button2";
self->enumValues[188].m_tagName = "Joystick2Button2";
self->enumValues[188].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[188].m_type = nullptr;

/* EnumConstant 190 */
self->enumValues[189].m_index = 189;
self->enumValues[189].m_value = 373;
self->enumValues[189].m_name = "Joystick2Button3";
self->enumValues[189].m_tagName = "Joystick2Button3";
self->enumValues[189].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[189].m_type = nullptr;

/* EnumConstant 191 */
self->enumValues[190].m_index = 190;
self->enumValues[190].m_value = 374;
self->enumValues[190].m_name = "Joystick2Button4";
self->enumValues[190].m_tagName = "Joystick2Button4";
self->enumValues[190].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[190].m_type = nullptr;

/* EnumConstant 192 */
self->enumValues[191].m_index = 191;
self->enumValues[191].m_value = 375;
self->enumValues[191].m_name = "Joystick2Button5";
self->enumValues[191].m_tagName = "Joystick2Button5";
self->enumValues[191].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[191].m_type = nullptr;

/* EnumConstant 193 */
self->enumValues[192].m_index = 192;
self->enumValues[192].m_value = 376;
self->enumValues[192].m_name = "Joystick2Button6";
self->enumValues[192].m_tagName = "Joystick2Button6";
self->enumValues[192].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[192].m_type = nullptr;

/* EnumConstant 194 */
self->enumValues[193].m_index = 193;
self->enumValues[193].m_value = 377;
self->enumValues[193].m_name = "Joystick2Button7";
self->enumValues[193].m_tagName = "Joystick2Button7";
self->enumValues[193].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[193].m_type = nullptr;

/* EnumConstant 195 */
self->enumValues[194].m_index = 194;
self->enumValues[194].m_value = 378;
self->enumValues[194].m_name = "Joystick2Button8";
self->enumValues[194].m_tagName = "Joystick2Button8";
self->enumValues[194].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[194].m_type = nullptr;

/* EnumConstant 196 */
self->enumValues[195].m_index = 195;
self->enumValues[195].m_value = 379;
self->enumValues[195].m_name = "Joystick2Button9";
self->enumValues[195].m_tagName = "Joystick2Button9";
self->enumValues[195].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[195].m_type = nullptr;

/* EnumConstant 197 */
self->enumValues[196].m_index = 196;
self->enumValues[196].m_value = 380;
self->enumValues[196].m_name = "Joystick2Button10";
self->enumValues[196].m_tagName = "Joystick2Button10";
self->enumValues[196].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[196].m_type = nullptr;

/* EnumConstant 198 */
self->enumValues[197].m_index = 197;
self->enumValues[197].m_value = 381;
self->enumValues[197].m_name = "Joystick2Button11";
self->enumValues[197].m_tagName = "Joystick2Button11";
self->enumValues[197].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[197].m_type = nullptr;

/* EnumConstant 199 */
self->enumValues[198].m_index = 198;
self->enumValues[198].m_value = 382;
self->enumValues[198].m_name = "Joystick2Button12";
self->enumValues[198].m_tagName = "Joystick2Button12";
self->enumValues[198].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[198].m_type = nullptr;

/* EnumConstant 200 */
self->enumValues[199].m_index = 199;
self->enumValues[199].m_value = 383;
self->enumValues[199].m_name = "Joystick2Button13";
self->enumValues[199].m_tagName = "Joystick2Button13";
self->enumValues[199].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[199].m_type = nullptr;

/* EnumConstant 201 */
self->enumValues[200].m_index = 200;
self->enumValues[200].m_value = 384;
self->enumValues[200].m_name = "Joystick2Button14";
self->enumValues[200].m_tagName = "Joystick2Button14";
self->enumValues[200].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[200].m_type = nullptr;

/* EnumConstant 202 */
self->enumValues[201].m_index = 201;
self->enumValues[201].m_value = 385;
self->enumValues[201].m_name = "Joystick2Button15";
self->enumValues[201].m_tagName = "Joystick2Button15";
self->enumValues[201].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[201].m_type = nullptr;

/* EnumConstant 203 */
self->enumValues[202].m_index = 202;
self->enumValues[202].m_value = 386;
self->enumValues[202].m_name = "Joystick2Button16";
self->enumValues[202].m_tagName = "Joystick2Button16";
self->enumValues[202].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[202].m_type = nullptr;

/* EnumConstant 204 */
self->enumValues[203].m_index = 203;
self->enumValues[203].m_value = 387;
self->enumValues[203].m_name = "Joystick2Button17";
self->enumValues[203].m_tagName = "Joystick2Button17";
self->enumValues[203].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[203].m_type = nullptr;

/* EnumConstant 205 */
self->enumValues[204].m_index = 204;
self->enumValues[204].m_value = 388;
self->enumValues[204].m_name = "Joystick2Button18";
self->enumValues[204].m_tagName = "Joystick2Button18";
self->enumValues[204].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[204].m_type = nullptr;

/* EnumConstant 206 */
self->enumValues[205].m_index = 205;
self->enumValues[205].m_value = 389;
self->enumValues[205].m_name = "Joystick2Button19";
self->enumValues[205].m_tagName = "Joystick2Button19";
self->enumValues[205].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[205].m_type = nullptr;

/* EnumConstant 207 */
self->enumValues[206].m_index = 206;
self->enumValues[206].m_value = 390;
self->enumValues[206].m_name = "Joystick3Button0";
self->enumValues[206].m_tagName = "Joystick3Button0";
self->enumValues[206].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[206].m_type = nullptr;

/* EnumConstant 208 */
self->enumValues[207].m_index = 207;
self->enumValues[207].m_value = 391;
self->enumValues[207].m_name = "Joystick3Button1";
self->enumValues[207].m_tagName = "Joystick3Button1";
self->enumValues[207].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[207].m_type = nullptr;

/* EnumConstant 209 */
self->enumValues[208].m_index = 208;
self->enumValues[208].m_value = 392;
self->enumValues[208].m_name = "Joystick3Button2";
self->enumValues[208].m_tagName = "Joystick3Button2";
self->enumValues[208].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[208].m_type = nullptr;

/* EnumConstant 210 */
self->enumValues[209].m_index = 209;
self->enumValues[209].m_value = 393;
self->enumValues[209].m_name = "Joystick3Button3";
self->enumValues[209].m_tagName = "Joystick3Button3";
self->enumValues[209].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[209].m_type = nullptr;

/* EnumConstant 211 */
self->enumValues[210].m_index = 210;
self->enumValues[210].m_value = 394;
self->enumValues[210].m_name = "Joystick3Button4";
self->enumValues[210].m_tagName = "Joystick3Button4";
self->enumValues[210].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[210].m_type = nullptr;

/* EnumConstant 212 */
self->enumValues[211].m_index = 211;
self->enumValues[211].m_value = 395;
self->enumValues[211].m_name = "Joystick3Button5";
self->enumValues[211].m_tagName = "Joystick3Button5";
self->enumValues[211].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[211].m_type = nullptr;

/* EnumConstant 213 */
self->enumValues[212].m_index = 212;
self->enumValues[212].m_value = 396;
self->enumValues[212].m_name = "Joystick3Button6";
self->enumValues[212].m_tagName = "Joystick3Button6";
self->enumValues[212].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[212].m_type = nullptr;

/* EnumConstant 214 */
self->enumValues[213].m_index = 213;
self->enumValues[213].m_value = 397;
self->enumValues[213].m_name = "Joystick3Button7";
self->enumValues[213].m_tagName = "Joystick3Button7";
self->enumValues[213].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[213].m_type = nullptr;

/* EnumConstant 215 */
self->enumValues[214].m_index = 214;
self->enumValues[214].m_value = 398;
self->enumValues[214].m_name = "Joystick3Button8";
self->enumValues[214].m_tagName = "Joystick3Button8";
self->enumValues[214].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[214].m_type = nullptr;

/* EnumConstant 216 */
self->enumValues[215].m_index = 215;
self->enumValues[215].m_value = 399;
self->enumValues[215].m_name = "Joystick3Button9";
self->enumValues[215].m_tagName = "Joystick3Button9";
self->enumValues[215].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[215].m_type = nullptr;

/* EnumConstant 217 */
self->enumValues[216].m_index = 216;
self->enumValues[216].m_value = 400;
self->enumValues[216].m_name = "Joystick3Button10";
self->enumValues[216].m_tagName = "Joystick3Button10";
self->enumValues[216].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[216].m_type = nullptr;

/* EnumConstant 218 */
self->enumValues[217].m_index = 217;
self->enumValues[217].m_value = 401;
self->enumValues[217].m_name = "Joystick3Button11";
self->enumValues[217].m_tagName = "Joystick3Button11";
self->enumValues[217].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[217].m_type = nullptr;

/* EnumConstant 219 */
self->enumValues[218].m_index = 218;
self->enumValues[218].m_value = 402;
self->enumValues[218].m_name = "Joystick3Button12";
self->enumValues[218].m_tagName = "Joystick3Button12";
self->enumValues[218].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[218].m_type = nullptr;

/* EnumConstant 220 */
self->enumValues[219].m_index = 219;
self->enumValues[219].m_value = 403;
self->enumValues[219].m_name = "Joystick3Button13";
self->enumValues[219].m_tagName = "Joystick3Button13";
self->enumValues[219].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[219].m_type = nullptr;

/* EnumConstant 221 */
self->enumValues[220].m_index = 220;
self->enumValues[220].m_value = 404;
self->enumValues[220].m_name = "Joystick3Button14";
self->enumValues[220].m_tagName = "Joystick3Button14";
self->enumValues[220].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[220].m_type = nullptr;

/* EnumConstant 222 */
self->enumValues[221].m_index = 221;
self->enumValues[221].m_value = 405;
self->enumValues[221].m_name = "Joystick3Button15";
self->enumValues[221].m_tagName = "Joystick3Button15";
self->enumValues[221].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[221].m_type = nullptr;

/* EnumConstant 223 */
self->enumValues[222].m_index = 222;
self->enumValues[222].m_value = 406;
self->enumValues[222].m_name = "Joystick3Button16";
self->enumValues[222].m_tagName = "Joystick3Button16";
self->enumValues[222].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[222].m_type = nullptr;

/* EnumConstant 224 */
self->enumValues[223].m_index = 223;
self->enumValues[223].m_value = 407;
self->enumValues[223].m_name = "Joystick3Button17";
self->enumValues[223].m_tagName = "Joystick3Button17";
self->enumValues[223].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[223].m_type = nullptr;

/* EnumConstant 225 */
self->enumValues[224].m_index = 224;
self->enumValues[224].m_value = 408;
self->enumValues[224].m_name = "Joystick3Button18";
self->enumValues[224].m_tagName = "Joystick3Button18";
self->enumValues[224].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[224].m_type = nullptr;

/* EnumConstant 226 */
self->enumValues[225].m_index = 225;
self->enumValues[225].m_value = 409;
self->enumValues[225].m_name = "Joystick3Button19";
self->enumValues[225].m_tagName = "Joystick3Button19";
self->enumValues[225].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[225].m_type = nullptr;

/* EnumConstant 227 */
self->enumValues[226].m_index = 226;
self->enumValues[226].m_value = 410;
self->enumValues[226].m_name = "Joystick4Button0";
self->enumValues[226].m_tagName = "Joystick4Button0";
self->enumValues[226].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[226].m_type = nullptr;

/* EnumConstant 228 */
self->enumValues[227].m_index = 227;
self->enumValues[227].m_value = 411;
self->enumValues[227].m_name = "Joystick4Button1";
self->enumValues[227].m_tagName = "Joystick4Button1";
self->enumValues[227].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[227].m_type = nullptr;

/* EnumConstant 229 */
self->enumValues[228].m_index = 228;
self->enumValues[228].m_value = 412;
self->enumValues[228].m_name = "Joystick4Button2";
self->enumValues[228].m_tagName = "Joystick4Button2";
self->enumValues[228].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[228].m_type = nullptr;

/* EnumConstant 230 */
self->enumValues[229].m_index = 229;
self->enumValues[229].m_value = 413;
self->enumValues[229].m_name = "Joystick4Button3";
self->enumValues[229].m_tagName = "Joystick4Button3";
self->enumValues[229].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[229].m_type = nullptr;

/* EnumConstant 231 */
self->enumValues[230].m_index = 230;
self->enumValues[230].m_value = 414;
self->enumValues[230].m_name = "Joystick4Button4";
self->enumValues[230].m_tagName = "Joystick4Button4";
self->enumValues[230].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[230].m_type = nullptr;

/* EnumConstant 232 */
self->enumValues[231].m_index = 231;
self->enumValues[231].m_value = 415;
self->enumValues[231].m_name = "Joystick4Button5";
self->enumValues[231].m_tagName = "Joystick4Button5";
self->enumValues[231].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[231].m_type = nullptr;

/* EnumConstant 233 */
self->enumValues[232].m_index = 232;
self->enumValues[232].m_value = 416;
self->enumValues[232].m_name = "Joystick4Button6";
self->enumValues[232].m_tagName = "Joystick4Button6";
self->enumValues[232].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[232].m_type = nullptr;

/* EnumConstant 234 */
self->enumValues[233].m_index = 233;
self->enumValues[233].m_value = 417;
self->enumValues[233].m_name = "Joystick4Button7";
self->enumValues[233].m_tagName = "Joystick4Button7";
self->enumValues[233].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[233].m_type = nullptr;

/* EnumConstant 235 */
self->enumValues[234].m_index = 234;
self->enumValues[234].m_value = 418;
self->enumValues[234].m_name = "Joystick4Button8";
self->enumValues[234].m_tagName = "Joystick4Button8";
self->enumValues[234].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[234].m_type = nullptr;

/* EnumConstant 236 */
self->enumValues[235].m_index = 235;
self->enumValues[235].m_value = 419;
self->enumValues[235].m_name = "Joystick4Button9";
self->enumValues[235].m_tagName = "Joystick4Button9";
self->enumValues[235].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[235].m_type = nullptr;

/* EnumConstant 237 */
self->enumValues[236].m_index = 236;
self->enumValues[236].m_value = 420;
self->enumValues[236].m_name = "Joystick4Button10";
self->enumValues[236].m_tagName = "Joystick4Button10";
self->enumValues[236].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[236].m_type = nullptr;

/* EnumConstant 238 */
self->enumValues[237].m_index = 237;
self->enumValues[237].m_value = 421;
self->enumValues[237].m_name = "Joystick4Button11";
self->enumValues[237].m_tagName = "Joystick4Button11";
self->enumValues[237].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[237].m_type = nullptr;

/* EnumConstant 239 */
self->enumValues[238].m_index = 238;
self->enumValues[238].m_value = 422;
self->enumValues[238].m_name = "Joystick4Button12";
self->enumValues[238].m_tagName = "Joystick4Button12";
self->enumValues[238].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[238].m_type = nullptr;

/* EnumConstant 240 */
self->enumValues[239].m_index = 239;
self->enumValues[239].m_value = 423;
self->enumValues[239].m_name = "Joystick4Button13";
self->enumValues[239].m_tagName = "Joystick4Button13";
self->enumValues[239].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[239].m_type = nullptr;

/* EnumConstant 241 */
self->enumValues[240].m_index = 240;
self->enumValues[240].m_value = 424;
self->enumValues[240].m_name = "Joystick4Button14";
self->enumValues[240].m_tagName = "Joystick4Button14";
self->enumValues[240].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[240].m_type = nullptr;

/* EnumConstant 242 */
self->enumValues[241].m_index = 241;
self->enumValues[241].m_value = 425;
self->enumValues[241].m_name = "Joystick4Button15";
self->enumValues[241].m_tagName = "Joystick4Button15";
self->enumValues[241].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[241].m_type = nullptr;

/* EnumConstant 243 */
self->enumValues[242].m_index = 242;
self->enumValues[242].m_value = 426;
self->enumValues[242].m_name = "Joystick4Button16";
self->enumValues[242].m_tagName = "Joystick4Button16";
self->enumValues[242].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[242].m_type = nullptr;

/* EnumConstant 244 */
self->enumValues[243].m_index = 243;
self->enumValues[243].m_value = 427;
self->enumValues[243].m_name = "Joystick4Button17";
self->enumValues[243].m_tagName = "Joystick4Button17";
self->enumValues[243].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[243].m_type = nullptr;

/* EnumConstant 245 */
self->enumValues[244].m_index = 244;
self->enumValues[244].m_value = 428;
self->enumValues[244].m_name = "Joystick4Button18";
self->enumValues[244].m_tagName = "Joystick4Button18";
self->enumValues[244].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[244].m_type = nullptr;

/* EnumConstant 246 */
self->enumValues[245].m_index = 245;
self->enumValues[245].m_value = 429;
self->enumValues[245].m_name = "Joystick4Button19";
self->enumValues[245].m_tagName = "Joystick4Button19";
self->enumValues[245].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[245].m_type = nullptr;

/* EnumConstant 247 */
self->enumValues[246].m_index = 246;
self->enumValues[246].m_value = 430;
self->enumValues[246].m_name = "Joystick5Button0";
self->enumValues[246].m_tagName = "Joystick5Button0";
self->enumValues[246].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[246].m_type = nullptr;

/* EnumConstant 248 */
self->enumValues[247].m_index = 247;
self->enumValues[247].m_value = 431;
self->enumValues[247].m_name = "Joystick5Button1";
self->enumValues[247].m_tagName = "Joystick5Button1";
self->enumValues[247].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[247].m_type = nullptr;

/* EnumConstant 249 */
self->enumValues[248].m_index = 248;
self->enumValues[248].m_value = 432;
self->enumValues[248].m_name = "Joystick5Button2";
self->enumValues[248].m_tagName = "Joystick5Button2";
self->enumValues[248].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[248].m_type = nullptr;

/* EnumConstant 250 */
self->enumValues[249].m_index = 249;
self->enumValues[249].m_value = 433;
self->enumValues[249].m_name = "Joystick5Button3";
self->enumValues[249].m_tagName = "Joystick5Button3";
self->enumValues[249].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[249].m_type = nullptr;

/* EnumConstant 251 */
self->enumValues[250].m_index = 250;
self->enumValues[250].m_value = 434;
self->enumValues[250].m_name = "Joystick5Button4";
self->enumValues[250].m_tagName = "Joystick5Button4";
self->enumValues[250].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[250].m_type = nullptr;

/* EnumConstant 252 */
self->enumValues[251].m_index = 251;
self->enumValues[251].m_value = 435;
self->enumValues[251].m_name = "Joystick5Button5";
self->enumValues[251].m_tagName = "Joystick5Button5";
self->enumValues[251].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[251].m_type = nullptr;

/* EnumConstant 253 */
self->enumValues[252].m_index = 252;
self->enumValues[252].m_value = 436;
self->enumValues[252].m_name = "Joystick5Button6";
self->enumValues[252].m_tagName = "Joystick5Button6";
self->enumValues[252].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[252].m_type = nullptr;

/* EnumConstant 254 */
self->enumValues[253].m_index = 253;
self->enumValues[253].m_value = 437;
self->enumValues[253].m_name = "Joystick5Button7";
self->enumValues[253].m_tagName = "Joystick5Button7";
self->enumValues[253].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[253].m_type = nullptr;

/* EnumConstant 255 */
self->enumValues[254].m_index = 254;
self->enumValues[254].m_value = 438;
self->enumValues[254].m_name = "Joystick5Button8";
self->enumValues[254].m_tagName = "Joystick5Button8";
self->enumValues[254].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[254].m_type = nullptr;

/* EnumConstant 256 */
self->enumValues[255].m_index = 255;
self->enumValues[255].m_value = 439;
self->enumValues[255].m_name = "Joystick5Button9";
self->enumValues[255].m_tagName = "Joystick5Button9";
self->enumValues[255].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[255].m_type = nullptr;

/* EnumConstant 257 */
self->enumValues[256].m_index = 256;
self->enumValues[256].m_value = 440;
self->enumValues[256].m_name = "Joystick5Button10";
self->enumValues[256].m_tagName = "Joystick5Button10";
self->enumValues[256].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[256].m_type = nullptr;

/* EnumConstant 258 */
self->enumValues[257].m_index = 257;
self->enumValues[257].m_value = 441;
self->enumValues[257].m_name = "Joystick5Button11";
self->enumValues[257].m_tagName = "Joystick5Button11";
self->enumValues[257].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[257].m_type = nullptr;

/* EnumConstant 259 */
self->enumValues[258].m_index = 258;
self->enumValues[258].m_value = 442;
self->enumValues[258].m_name = "Joystick5Button12";
self->enumValues[258].m_tagName = "Joystick5Button12";
self->enumValues[258].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[258].m_type = nullptr;

/* EnumConstant 260 */
self->enumValues[259].m_index = 259;
self->enumValues[259].m_value = 443;
self->enumValues[259].m_name = "Joystick5Button13";
self->enumValues[259].m_tagName = "Joystick5Button13";
self->enumValues[259].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[259].m_type = nullptr;

/* EnumConstant 261 */
self->enumValues[260].m_index = 260;
self->enumValues[260].m_value = 444;
self->enumValues[260].m_name = "Joystick5Button14";
self->enumValues[260].m_tagName = "Joystick5Button14";
self->enumValues[260].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[260].m_type = nullptr;

/* EnumConstant 262 */
self->enumValues[261].m_index = 261;
self->enumValues[261].m_value = 445;
self->enumValues[261].m_name = "Joystick5Button15";
self->enumValues[261].m_tagName = "Joystick5Button15";
self->enumValues[261].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[261].m_type = nullptr;

/* EnumConstant 263 */
self->enumValues[262].m_index = 262;
self->enumValues[262].m_value = 446;
self->enumValues[262].m_name = "Joystick5Button16";
self->enumValues[262].m_tagName = "Joystick5Button16";
self->enumValues[262].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[262].m_type = nullptr;

/* EnumConstant 264 */
self->enumValues[263].m_index = 263;
self->enumValues[263].m_value = 447;
self->enumValues[263].m_name = "Joystick5Button17";
self->enumValues[263].m_tagName = "Joystick5Button17";
self->enumValues[263].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[263].m_type = nullptr;

/* EnumConstant 265 */
self->enumValues[264].m_index = 264;
self->enumValues[264].m_value = 448;
self->enumValues[264].m_name = "Joystick5Button18";
self->enumValues[264].m_tagName = "Joystick5Button18";
self->enumValues[264].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[264].m_type = nullptr;

/* EnumConstant 266 */
self->enumValues[265].m_index = 265;
self->enumValues[265].m_value = 449;
self->enumValues[265].m_name = "Joystick5Button19";
self->enumValues[265].m_tagName = "Joystick5Button19";
self->enumValues[265].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[265].m_type = nullptr;

/* EnumConstant 267 */
self->enumValues[266].m_index = 266;
self->enumValues[266].m_value = 450;
self->enumValues[266].m_name = "Joystick6Button0";
self->enumValues[266].m_tagName = "Joystick6Button0";
self->enumValues[266].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[266].m_type = nullptr;

/* EnumConstant 268 */
self->enumValues[267].m_index = 267;
self->enumValues[267].m_value = 451;
self->enumValues[267].m_name = "Joystick6Button1";
self->enumValues[267].m_tagName = "Joystick6Button1";
self->enumValues[267].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[267].m_type = nullptr;

/* EnumConstant 269 */
self->enumValues[268].m_index = 268;
self->enumValues[268].m_value = 452;
self->enumValues[268].m_name = "Joystick6Button2";
self->enumValues[268].m_tagName = "Joystick6Button2";
self->enumValues[268].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[268].m_type = nullptr;

/* EnumConstant 270 */
self->enumValues[269].m_index = 269;
self->enumValues[269].m_value = 453;
self->enumValues[269].m_name = "Joystick6Button3";
self->enumValues[269].m_tagName = "Joystick6Button3";
self->enumValues[269].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[269].m_type = nullptr;

/* EnumConstant 271 */
self->enumValues[270].m_index = 270;
self->enumValues[270].m_value = 454;
self->enumValues[270].m_name = "Joystick6Button4";
self->enumValues[270].m_tagName = "Joystick6Button4";
self->enumValues[270].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[270].m_type = nullptr;

/* EnumConstant 272 */
self->enumValues[271].m_index = 271;
self->enumValues[271].m_value = 455;
self->enumValues[271].m_name = "Joystick6Button5";
self->enumValues[271].m_tagName = "Joystick6Button5";
self->enumValues[271].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[271].m_type = nullptr;

/* EnumConstant 273 */
self->enumValues[272].m_index = 272;
self->enumValues[272].m_value = 456;
self->enumValues[272].m_name = "Joystick6Button6";
self->enumValues[272].m_tagName = "Joystick6Button6";
self->enumValues[272].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[272].m_type = nullptr;

/* EnumConstant 274 */
self->enumValues[273].m_index = 273;
self->enumValues[273].m_value = 457;
self->enumValues[273].m_name = "Joystick6Button7";
self->enumValues[273].m_tagName = "Joystick6Button7";
self->enumValues[273].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[273].m_type = nullptr;

/* EnumConstant 275 */
self->enumValues[274].m_index = 274;
self->enumValues[274].m_value = 458;
self->enumValues[274].m_name = "Joystick6Button8";
self->enumValues[274].m_tagName = "Joystick6Button8";
self->enumValues[274].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[274].m_type = nullptr;

/* EnumConstant 276 */
self->enumValues[275].m_index = 275;
self->enumValues[275].m_value = 459;
self->enumValues[275].m_name = "Joystick6Button9";
self->enumValues[275].m_tagName = "Joystick6Button9";
self->enumValues[275].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[275].m_type = nullptr;

/* EnumConstant 277 */
self->enumValues[276].m_index = 276;
self->enumValues[276].m_value = 460;
self->enumValues[276].m_name = "Joystick6Button10";
self->enumValues[276].m_tagName = "Joystick6Button10";
self->enumValues[276].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[276].m_type = nullptr;

/* EnumConstant 278 */
self->enumValues[277].m_index = 277;
self->enumValues[277].m_value = 461;
self->enumValues[277].m_name = "Joystick6Button11";
self->enumValues[277].m_tagName = "Joystick6Button11";
self->enumValues[277].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[277].m_type = nullptr;

/* EnumConstant 279 */
self->enumValues[278].m_index = 278;
self->enumValues[278].m_value = 462;
self->enumValues[278].m_name = "Joystick6Button12";
self->enumValues[278].m_tagName = "Joystick6Button12";
self->enumValues[278].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[278].m_type = nullptr;

/* EnumConstant 280 */
self->enumValues[279].m_index = 279;
self->enumValues[279].m_value = 463;
self->enumValues[279].m_name = "Joystick6Button13";
self->enumValues[279].m_tagName = "Joystick6Button13";
self->enumValues[279].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[279].m_type = nullptr;

/* EnumConstant 281 */
self->enumValues[280].m_index = 280;
self->enumValues[280].m_value = 464;
self->enumValues[280].m_name = "Joystick6Button14";
self->enumValues[280].m_tagName = "Joystick6Button14";
self->enumValues[280].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[280].m_type = nullptr;

/* EnumConstant 282 */
self->enumValues[281].m_index = 281;
self->enumValues[281].m_value = 465;
self->enumValues[281].m_name = "Joystick6Button15";
self->enumValues[281].m_tagName = "Joystick6Button15";
self->enumValues[281].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[281].m_type = nullptr;

/* EnumConstant 283 */
self->enumValues[282].m_index = 282;
self->enumValues[282].m_value = 466;
self->enumValues[282].m_name = "Joystick6Button16";
self->enumValues[282].m_tagName = "Joystick6Button16";
self->enumValues[282].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[282].m_type = nullptr;

/* EnumConstant 284 */
self->enumValues[283].m_index = 283;
self->enumValues[283].m_value = 467;
self->enumValues[283].m_name = "Joystick6Button17";
self->enumValues[283].m_tagName = "Joystick6Button17";
self->enumValues[283].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[283].m_type = nullptr;

/* EnumConstant 285 */
self->enumValues[284].m_index = 284;
self->enumValues[284].m_value = 468;
self->enumValues[284].m_name = "Joystick6Button18";
self->enumValues[284].m_tagName = "Joystick6Button18";
self->enumValues[284].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[284].m_type = nullptr;

/* EnumConstant 286 */
self->enumValues[285].m_index = 285;
self->enumValues[285].m_value = 469;
self->enumValues[285].m_name = "Joystick6Button19";
self->enumValues[285].m_tagName = "Joystick6Button19";
self->enumValues[285].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[285].m_type = nullptr;

/* EnumConstant 287 */
self->enumValues[286].m_index = 286;
self->enumValues[286].m_value = 470;
self->enumValues[286].m_name = "Joystick7Button0";
self->enumValues[286].m_tagName = "Joystick7Button0";
self->enumValues[286].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[286].m_type = nullptr;

/* EnumConstant 288 */
self->enumValues[287].m_index = 287;
self->enumValues[287].m_value = 471;
self->enumValues[287].m_name = "Joystick7Button1";
self->enumValues[287].m_tagName = "Joystick7Button1";
self->enumValues[287].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[287].m_type = nullptr;

/* EnumConstant 289 */
self->enumValues[288].m_index = 288;
self->enumValues[288].m_value = 472;
self->enumValues[288].m_name = "Joystick7Button2";
self->enumValues[288].m_tagName = "Joystick7Button2";
self->enumValues[288].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[288].m_type = nullptr;

/* EnumConstant 290 */
self->enumValues[289].m_index = 289;
self->enumValues[289].m_value = 473;
self->enumValues[289].m_name = "Joystick7Button3";
self->enumValues[289].m_tagName = "Joystick7Button3";
self->enumValues[289].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[289].m_type = nullptr;

/* EnumConstant 291 */
self->enumValues[290].m_index = 290;
self->enumValues[290].m_value = 474;
self->enumValues[290].m_name = "Joystick7Button4";
self->enumValues[290].m_tagName = "Joystick7Button4";
self->enumValues[290].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[290].m_type = nullptr;

/* EnumConstant 292 */
self->enumValues[291].m_index = 291;
self->enumValues[291].m_value = 475;
self->enumValues[291].m_name = "Joystick7Button5";
self->enumValues[291].m_tagName = "Joystick7Button5";
self->enumValues[291].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[291].m_type = nullptr;

/* EnumConstant 293 */
self->enumValues[292].m_index = 292;
self->enumValues[292].m_value = 476;
self->enumValues[292].m_name = "Joystick7Button6";
self->enumValues[292].m_tagName = "Joystick7Button6";
self->enumValues[292].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[292].m_type = nullptr;

/* EnumConstant 294 */
self->enumValues[293].m_index = 293;
self->enumValues[293].m_value = 477;
self->enumValues[293].m_name = "Joystick7Button7";
self->enumValues[293].m_tagName = "Joystick7Button7";
self->enumValues[293].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[293].m_type = nullptr;

/* EnumConstant 295 */
self->enumValues[294].m_index = 294;
self->enumValues[294].m_value = 478;
self->enumValues[294].m_name = "Joystick7Button8";
self->enumValues[294].m_tagName = "Joystick7Button8";
self->enumValues[294].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[294].m_type = nullptr;

/* EnumConstant 296 */
self->enumValues[295].m_index = 295;
self->enumValues[295].m_value = 479;
self->enumValues[295].m_name = "Joystick7Button9";
self->enumValues[295].m_tagName = "Joystick7Button9";
self->enumValues[295].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[295].m_type = nullptr;

/* EnumConstant 297 */
self->enumValues[296].m_index = 296;
self->enumValues[296].m_value = 480;
self->enumValues[296].m_name = "Joystick7Button10";
self->enumValues[296].m_tagName = "Joystick7Button10";
self->enumValues[296].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[296].m_type = nullptr;

/* EnumConstant 298 */
self->enumValues[297].m_index = 297;
self->enumValues[297].m_value = 481;
self->enumValues[297].m_name = "Joystick7Button11";
self->enumValues[297].m_tagName = "Joystick7Button11";
self->enumValues[297].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[297].m_type = nullptr;

/* EnumConstant 299 */
self->enumValues[298].m_index = 298;
self->enumValues[298].m_value = 482;
self->enumValues[298].m_name = "Joystick7Button12";
self->enumValues[298].m_tagName = "Joystick7Button12";
self->enumValues[298].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[298].m_type = nullptr;

/* EnumConstant 300 */
self->enumValues[299].m_index = 299;
self->enumValues[299].m_value = 483;
self->enumValues[299].m_name = "Joystick7Button13";
self->enumValues[299].m_tagName = "Joystick7Button13";
self->enumValues[299].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[299].m_type = nullptr;

/* EnumConstant 301 */
self->enumValues[300].m_index = 300;
self->enumValues[300].m_value = 484;
self->enumValues[300].m_name = "Joystick7Button14";
self->enumValues[300].m_tagName = "Joystick7Button14";
self->enumValues[300].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[300].m_type = nullptr;

/* EnumConstant 302 */
self->enumValues[301].m_index = 301;
self->enumValues[301].m_value = 485;
self->enumValues[301].m_name = "Joystick7Button15";
self->enumValues[301].m_tagName = "Joystick7Button15";
self->enumValues[301].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[301].m_type = nullptr;

/* EnumConstant 303 */
self->enumValues[302].m_index = 302;
self->enumValues[302].m_value = 486;
self->enumValues[302].m_name = "Joystick7Button16";
self->enumValues[302].m_tagName = "Joystick7Button16";
self->enumValues[302].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[302].m_type = nullptr;

/* EnumConstant 304 */
self->enumValues[303].m_index = 303;
self->enumValues[303].m_value = 487;
self->enumValues[303].m_name = "Joystick7Button17";
self->enumValues[303].m_tagName = "Joystick7Button17";
self->enumValues[303].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[303].m_type = nullptr;

/* EnumConstant 305 */
self->enumValues[304].m_index = 304;
self->enumValues[304].m_value = 488;
self->enumValues[304].m_name = "Joystick7Button18";
self->enumValues[304].m_tagName = "Joystick7Button18";
self->enumValues[304].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[304].m_type = nullptr;

/* EnumConstant 306 */
self->enumValues[305].m_index = 305;
self->enumValues[305].m_value = 489;
self->enumValues[305].m_name = "Joystick7Button19";
self->enumValues[305].m_tagName = "Joystick7Button19";
self->enumValues[305].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[305].m_type = nullptr;

/* EnumConstant 307 */
self->enumValues[306].m_index = 306;
self->enumValues[306].m_value = 490;
self->enumValues[306].m_name = "Joystick8Button0";
self->enumValues[306].m_tagName = "Joystick8Button0";
self->enumValues[306].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[306].m_type = nullptr;

/* EnumConstant 308 */
self->enumValues[307].m_index = 307;
self->enumValues[307].m_value = 491;
self->enumValues[307].m_name = "Joystick8Button1";
self->enumValues[307].m_tagName = "Joystick8Button1";
self->enumValues[307].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[307].m_type = nullptr;

/* EnumConstant 309 */
self->enumValues[308].m_index = 308;
self->enumValues[308].m_value = 492;
self->enumValues[308].m_name = "Joystick8Button2";
self->enumValues[308].m_tagName = "Joystick8Button2";
self->enumValues[308].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[308].m_type = nullptr;

/* EnumConstant 310 */
self->enumValues[309].m_index = 309;
self->enumValues[309].m_value = 493;
self->enumValues[309].m_name = "Joystick8Button3";
self->enumValues[309].m_tagName = "Joystick8Button3";
self->enumValues[309].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[309].m_type = nullptr;

/* EnumConstant 311 */
self->enumValues[310].m_index = 310;
self->enumValues[310].m_value = 494;
self->enumValues[310].m_name = "Joystick8Button4";
self->enumValues[310].m_tagName = "Joystick8Button4";
self->enumValues[310].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[310].m_type = nullptr;

/* EnumConstant 312 */
self->enumValues[311].m_index = 311;
self->enumValues[311].m_value = 495;
self->enumValues[311].m_name = "Joystick8Button5";
self->enumValues[311].m_tagName = "Joystick8Button5";
self->enumValues[311].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[311].m_type = nullptr;

/* EnumConstant 313 */
self->enumValues[312].m_index = 312;
self->enumValues[312].m_value = 496;
self->enumValues[312].m_name = "Joystick8Button6";
self->enumValues[312].m_tagName = "Joystick8Button6";
self->enumValues[312].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[312].m_type = nullptr;

/* EnumConstant 314 */
self->enumValues[313].m_index = 313;
self->enumValues[313].m_value = 497;
self->enumValues[313].m_name = "Joystick8Button7";
self->enumValues[313].m_tagName = "Joystick8Button7";
self->enumValues[313].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[313].m_type = nullptr;

/* EnumConstant 315 */
self->enumValues[314].m_index = 314;
self->enumValues[314].m_value = 498;
self->enumValues[314].m_name = "Joystick8Button8";
self->enumValues[314].m_tagName = "Joystick8Button8";
self->enumValues[314].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[314].m_type = nullptr;

/* EnumConstant 316 */
self->enumValues[315].m_index = 315;
self->enumValues[315].m_value = 499;
self->enumValues[315].m_name = "Joystick8Button9";
self->enumValues[315].m_tagName = "Joystick8Button9";
self->enumValues[315].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[315].m_type = nullptr;

/* EnumConstant 317 */
self->enumValues[316].m_index = 316;
self->enumValues[316].m_value = 500;
self->enumValues[316].m_name = "Joystick8Button10";
self->enumValues[316].m_tagName = "Joystick8Button10";
self->enumValues[316].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[316].m_type = nullptr;

/* EnumConstant 318 */
self->enumValues[317].m_index = 317;
self->enumValues[317].m_value = 501;
self->enumValues[317].m_name = "Joystick8Button11";
self->enumValues[317].m_tagName = "Joystick8Button11";
self->enumValues[317].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[317].m_type = nullptr;

/* EnumConstant 319 */
self->enumValues[318].m_index = 318;
self->enumValues[318].m_value = 502;
self->enumValues[318].m_name = "Joystick8Button12";
self->enumValues[318].m_tagName = "Joystick8Button12";
self->enumValues[318].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[318].m_type = nullptr;

/* EnumConstant 320 */
self->enumValues[319].m_index = 319;
self->enumValues[319].m_value = 503;
self->enumValues[319].m_name = "Joystick8Button13";
self->enumValues[319].m_tagName = "Joystick8Button13";
self->enumValues[319].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[319].m_type = nullptr;

/* EnumConstant 321 */
self->enumValues[320].m_index = 320;
self->enumValues[320].m_value = 504;
self->enumValues[320].m_name = "Joystick8Button14";
self->enumValues[320].m_tagName = "Joystick8Button14";
self->enumValues[320].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[320].m_type = nullptr;

/* EnumConstant 322 */
self->enumValues[321].m_index = 321;
self->enumValues[321].m_value = 505;
self->enumValues[321].m_name = "Joystick8Button15";
self->enumValues[321].m_tagName = "Joystick8Button15";
self->enumValues[321].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[321].m_type = nullptr;

/* EnumConstant 323 */
self->enumValues[322].m_index = 322;
self->enumValues[322].m_value = 506;
self->enumValues[322].m_name = "Joystick8Button16";
self->enumValues[322].m_tagName = "Joystick8Button16";
self->enumValues[322].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[322].m_type = nullptr;

/* EnumConstant 324 */
self->enumValues[323].m_index = 323;
self->enumValues[323].m_value = 507;
self->enumValues[323].m_name = "Joystick8Button17";
self->enumValues[323].m_tagName = "Joystick8Button17";
self->enumValues[323].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[323].m_type = nullptr;

/* EnumConstant 325 */
self->enumValues[324].m_index = 324;
self->enumValues[324].m_value = 508;
self->enumValues[324].m_name = "Joystick8Button18";
self->enumValues[324].m_tagName = "Joystick8Button18";
self->enumValues[324].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[324].m_type = nullptr;

/* EnumConstant 326 */
self->enumValues[325].m_index = 325;
self->enumValues[325].m_value = 509;
self->enumValues[325].m_name = "Joystick8Button19";
self->enumValues[325].m_tagName = "Joystick8Button19";
self->enumValues[325].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[325].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::core::KeyCode),
Hash("loo::core::KeyCode"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::core::KeyCode",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::KeyCode>) noexcept
{
return LooGetEnum<loo::core::KeyCode>();
}
} /* namespace detail */
} /* namespace looreflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::SAppEventType> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::core::SAppEventType>) noexcept
{
static detail::LooEnumBuilder<loo::core::SAppEventType, 25> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "SAPP_EVENTTYPE_INVALID";
self->enumValues[0].m_tagName = "SAPP_EVENTTYPE_INVALID";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "SAPP_EVENTTYPE_KEY_DOWN";
self->enumValues[1].m_tagName = "SAPP_EVENTTYPE_KEY_DOWN";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "SAPP_EVENTTYPE_KEY_UP";
self->enumValues[2].m_tagName = "SAPP_EVENTTYPE_KEY_UP";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "SAPP_EVENTTYPE_CHAR";
self->enumValues[3].m_tagName = "SAPP_EVENTTYPE_CHAR";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "SAPP_EVENTTYPE_MOUSE_DOWN";
self->enumValues[4].m_tagName = "SAPP_EVENTTYPE_MOUSE_DOWN";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "SAPP_EVENTTYPE_MOUSE_UP";
self->enumValues[5].m_tagName = "SAPP_EVENTTYPE_MOUSE_UP";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "SAPP_EVENTTYPE_MOUSE_SCROLL";
self->enumValues[6].m_tagName = "SAPP_EVENTTYPE_MOUSE_SCROLL";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "SAPP_EVENTTYPE_MOUSE_MOVE";
self->enumValues[7].m_tagName = "SAPP_EVENTTYPE_MOUSE_MOVE";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 8;
self->enumValues[8].m_name = "SAPP_EVENTTYPE_MOUSE_ENTER";
self->enumValues[8].m_tagName = "SAPP_EVENTTYPE_MOUSE_ENTER";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 9;
self->enumValues[9].m_name = "SAPP_EVENTTYPE_MOUSE_LEAVE";
self->enumValues[9].m_tagName = "SAPP_EVENTTYPE_MOUSE_LEAVE";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 10;
self->enumValues[10].m_name = "SAPP_EVENTTYPE_TOUCHES";
self->enumValues[10].m_tagName = "SAPP_EVENTTYPE_TOUCHES";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 11;
self->enumValues[11].m_name = "SAPP_EVENTTYPE_TOUCHES_BEGAN";
self->enumValues[11].m_tagName = "SAPP_EVENTTYPE_TOUCHES_BEGAN";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 12;
self->enumValues[12].m_name = "SAPP_EVENTTYPE_TOUCHES_MOVED";
self->enumValues[12].m_tagName = "SAPP_EVENTTYPE_TOUCHES_MOVED";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 13;
self->enumValues[13].m_name = "SAPP_EVENTTYPE_TOUCHES_ENDED";
self->enumValues[13].m_tagName = "SAPP_EVENTTYPE_TOUCHES_ENDED";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 14;
self->enumValues[14].m_name = "SAPP_EVENTTYPE_TOUCHES_CANCELLED";
self->enumValues[14].m_tagName = "SAPP_EVENTTYPE_TOUCHES_CANCELLED";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 15;
self->enumValues[15].m_name = "SAPP_EVENTTYPE_RESIZED";
self->enumValues[15].m_tagName = "SAPP_EVENTTYPE_RESIZED";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;

/* EnumConstant 17 */
self->enumValues[16].m_index = 16;
self->enumValues[16].m_value = 16;
self->enumValues[16].m_name = "SAPP_EVENTTYPE_ICONIFIED";
self->enumValues[16].m_tagName = "SAPP_EVENTTYPE_ICONIFIED";
self->enumValues[16].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[16].m_type = nullptr;

/* EnumConstant 18 */
self->enumValues[17].m_index = 17;
self->enumValues[17].m_value = 17;
self->enumValues[17].m_name = "SAPP_EVENTTYPE_RESTORED";
self->enumValues[17].m_tagName = "SAPP_EVENTTYPE_RESTORED";
self->enumValues[17].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[17].m_type = nullptr;

/* EnumConstant 19 */
self->enumValues[18].m_index = 18;
self->enumValues[18].m_value = 18;
self->enumValues[18].m_name = "SAPP_EVENTTYPE_SUSPENDED";
self->enumValues[18].m_tagName = "SAPP_EVENTTYPE_SUSPENDED";
self->enumValues[18].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[18].m_type = nullptr;

/* EnumConstant 20 */
self->enumValues[19].m_index = 19;
self->enumValues[19].m_value = 19;
self->enumValues[19].m_name = "SAPP_EVENTTYPE_RESUMED";
self->enumValues[19].m_tagName = "SAPP_EVENTTYPE_RESUMED";
self->enumValues[19].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[19].m_type = nullptr;

/* EnumConstant 21 */
self->enumValues[20].m_index = 20;
self->enumValues[20].m_value = 20;
self->enumValues[20].m_name = "SAPP_EVENTTYPE_UPDATE_CURSOR";
self->enumValues[20].m_tagName = "SAPP_EVENTTYPE_UPDATE_CURSOR";
self->enumValues[20].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[20].m_type = nullptr;

/* EnumConstant 22 */
self->enumValues[21].m_index = 21;
self->enumValues[21].m_value = 21;
self->enumValues[21].m_name = "SAPP_EVENTTYPE_QUIT_REQUESTED";
self->enumValues[21].m_tagName = "SAPP_EVENTTYPE_QUIT_REQUESTED";
self->enumValues[21].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[21].m_type = nullptr;

/* EnumConstant 23 */
self->enumValues[22].m_index = 22;
self->enumValues[22].m_value = 22;
self->enumValues[22].m_name = "SAPP_EVENTTYPE_CLIPBOARD_PASTED";
self->enumValues[22].m_tagName = "SAPP_EVENTTYPE_CLIPBOARD_PASTED";
self->enumValues[22].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[22].m_type = nullptr;

/* EnumConstant 24 */
self->enumValues[23].m_index = 23;
self->enumValues[23].m_value = 23;
self->enumValues[23].m_name = "_SAPP_EVENTTYPE_NUM";
self->enumValues[23].m_tagName = "_SAPP_EVENTTYPE_NUM";
self->enumValues[23].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[23].m_type = nullptr;

/* EnumConstant 25 */
self->enumValues[24].m_index = 24;
self->enumValues[24].m_value = 2147483647;
self->enumValues[24].m_name = "_SAPP_EVENTTYPE_FORCE_U32";
self->enumValues[24].m_tagName = "_SAPP_EVENTTYPE_FORCE_U32";
self->enumValues[24].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[24].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::core::SAppEventType),
Hash("loo::core::SAppEventType"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::core::SAppEventType",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::SAppEventType>) noexcept
{
return LooGetEnum<loo::core::SAppEventType>();
}
} /* namespace detail */
} /* namespace looreflect */

/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::core::SAppModifierType> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::core::SAppModifierType>) noexcept
{
static detail::LooEnumBuilder<loo::core::SAppModifierType, 11> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "SAPP_MODIFIER_LSHIFT";
self->enumValues[0].m_tagName = "SAPP_MODIFIER_LSHIFT";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "SAPP_MODIFIER_RSHIFT";
self->enumValues[1].m_tagName = "SAPP_MODIFIER_RSHIFT";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4;
self->enumValues[2].m_name = "SAPP_MODIFIER_LCTRL";
self->enumValues[2].m_tagName = "SAPP_MODIFIER_LCTRL";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 8;
self->enumValues[3].m_name = "SAPP_MODIFIER_RCTRL";
self->enumValues[3].m_tagName = "SAPP_MODIFIER_RCTRL";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 16;
self->enumValues[4].m_name = "SAPP_MODIFIER_LALT";
self->enumValues[4].m_tagName = "SAPP_MODIFIER_LALT";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 32;
self->enumValues[5].m_name = "SAPP_MODIFIER_RALT";
self->enumValues[5].m_tagName = "SAPP_MODIFIER_RALT";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 64;
self->enumValues[6].m_name = "SAPP_MODIFIER_LMETA";
self->enumValues[6].m_tagName = "SAPP_MODIFIER_LMETA";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 128;
self->enumValues[7].m_name = "SAPP_MODIFIER_RMETA";
self->enumValues[7].m_tagName = "SAPP_MODIFIER_RMETA";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 256;
self->enumValues[8].m_name = "SAPP_MODIFIER_CAPSLOCK";
self->enumValues[8].m_tagName = "SAPP_MODIFIER_CAPSLOCK";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 512;
self->enumValues[9].m_name = "SAPP_MODIFIER_NUMLOCK";
self->enumValues[9].m_tagName = "SAPP_MODIFIER_NUMLOCK";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 1024;
self->enumValues[10].m_name = "SAPP_MODIFIER_SCROLLLOCK";
self->enumValues[10].m_tagName = "SAPP_MODIFIER_SCROLLLOCK";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::core::SAppModifierType),
Hash("loo::core::SAppModifierType"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::core::SAppModifierType",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::core::SAppModifierType>) noexcept
{
return LooGetEnum<loo::core::SAppModifierType>();
}
} /* namespace detail */
} /* namespace looreflect */

