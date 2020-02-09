/* this file is auto-generated. do not edit! */
#pragma once
#include "looreflect/looreflect.h"
#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#endif
namespace looreflect
{

template<> struct IsSerializable<loo::vkfg::ESwapchainImage> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::ESwapchainImage>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::ESwapchainImage, 3> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Primary";
self->enumValues[0].m_tagName = "Primary";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "LeftEye";
self->enumValues[1].m_tagName = "LeftEye";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "RightEye";
self->enumValues[2].m_tagName = "RightEye";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::ESwapchainImage),
Hash("loo::vkfg::ESwapchainImage"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::ESwapchainImage",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::ESwapchainImage>) noexcept
{
return LooGetEnum<loo::vkfg::ESwapchainImage>();
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

template<> struct IsSerializable<loo::vkfg::EDebugFlags> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EDebugFlags>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EDebugFlags, 11> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "LogTasks";
self->enumValues[0].m_tagName = "LogTasks";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "LogBarriers";
self->enumValues[1].m_tagName = "LogBarriers";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4;
self->enumValues[2].m_name = "LogResourceUsage";
self->enumValues[2].m_tagName = "LogResourceUsage";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 1024;
self->enumValues[3].m_name = "VisTasks";
self->enumValues[3].m_tagName = "VisTasks";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 2048;
self->enumValues[4].m_name = "VisDrawTasks";
self->enumValues[4].m_tagName = "VisDrawTasks";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 4096;
self->enumValues[5].m_name = "VisResources";
self->enumValues[5].m_tagName = "VisResources";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 8192;
self->enumValues[6].m_name = "VisBarriers";
self->enumValues[6].m_tagName = "VisBarriers";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 16384;
self->enumValues[7].m_name = "VisBarrierLabels";
self->enumValues[7].m_tagName = "VisBarrierLabels";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 32768;
self->enumValues[8].m_name = "VisTaskDependencies";
self->enumValues[8].m_tagName = "VisTaskDependencies";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 0;
self->enumValues[9].m_name = "Unknown";
self->enumValues[9].m_tagName = "Unknown";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 15367;
self->enumValues[10].m_name = "Default";
self->enumValues[10].m_tagName = "Default";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EDebugFlags),
Hash("loo::vkfg::EDebugFlags"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EDebugFlags",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EDebugFlags>) noexcept
{
return LooGetEnum<loo::vkfg::EDebugFlags>();
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

template<> struct IsSerializable<loo::vkfg::EQueueType> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EQueueType>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EQueueType, 3> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Graphics";
self->enumValues[0].m_tagName = "Graphics";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "AsyncCompute";
self->enumValues[1].m_tagName = "AsyncCompute";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "AsyncTransfer";
self->enumValues[2].m_tagName = "AsyncTransfer";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EQueueType),
Hash("loo::vkfg::EQueueType"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EQueueType",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EQueueType>) noexcept
{
return LooGetEnum<loo::vkfg::EQueueType>();
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

template<> struct IsSerializable<loo::vkfg::EQueueUsage> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EQueueUsage>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EQueueUsage, 4> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Unknown";
self->enumValues[0].m_tagName = "Unknown";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Graphics";
self->enumValues[1].m_tagName = "Graphics";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "AsyncCompute";
self->enumValues[2].m_tagName = "AsyncCompute";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 4;
self->enumValues[3].m_name = "AsyncTransfer";
self->enumValues[3].m_tagName = "AsyncTransfer";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EQueueUsage),
Hash("loo::vkfg::EQueueUsage"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EQueueUsage",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EQueueUsage>) noexcept
{
return LooGetEnum<loo::vkfg::EQueueUsage>();
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

template<> struct IsSerializable<loo::vkfg::EMemoryType> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EMemoryType>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EMemoryType, 6> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Default";
self->enumValues[0].m_tagName = "Default";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "HostRead";
self->enumValues[1].m_tagName = "HostRead";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "HostWrite";
self->enumValues[2].m_tagName = "HostWrite";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 4;
self->enumValues[3].m_name = "Dedicated";
self->enumValues[3].m_tagName = "Dedicated";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 8;
self->enumValues[4].m_name = "AllowAliasing";
self->enumValues[4].m_tagName = "AllowAliasing";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 16;
self->enumValues[5].m_name = "Sparse";
self->enumValues[5].m_tagName = "Sparse";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EMemoryType),
Hash("loo::vkfg::EMemoryType"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EMemoryType",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EMemoryType>) noexcept
{
return LooGetEnum<loo::vkfg::EMemoryType>();
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

template<> struct IsSerializable<loo::vkfg::EBufferUsage> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EBufferUsage>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EBufferUsage, 10> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "TransferSrc";
self->enumValues[0].m_tagName = "TransferSrc";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "TransferDst";
self->enumValues[1].m_tagName = "TransferDst";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4;
self->enumValues[2].m_name = "UniformTexel";
self->enumValues[2].m_tagName = "UniformTexel";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 8;
self->enumValues[3].m_name = "StorageTexel";
self->enumValues[3].m_tagName = "StorageTexel";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 16;
self->enumValues[4].m_name = "Uniform";
self->enumValues[4].m_tagName = "Uniform";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 32;
self->enumValues[5].m_name = "Storage";
self->enumValues[5].m_tagName = "Storage";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 64;
self->enumValues[6].m_name = "Index";
self->enumValues[6].m_tagName = "Index";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 128;
self->enumValues[7].m_name = "Vertex";
self->enumValues[7].m_tagName = "Vertex";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 256;
self->enumValues[8].m_name = "Indirect";
self->enumValues[8].m_tagName = "Indirect";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 512;
self->enumValues[9].m_name = "RayTracing";
self->enumValues[9].m_tagName = "RayTracing";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EBufferUsage),
Hash("loo::vkfg::EBufferUsage"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EBufferUsage",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EBufferUsage>) noexcept
{
return LooGetEnum<loo::vkfg::EBufferUsage>();
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

template<> struct IsSerializable<loo::vkfg::EImage> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EImage>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EImage, 11> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Tex1D";
self->enumValues[0].m_tagName = "Tex1D";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Tex1DArray";
self->enumValues[1].m_tagName = "Tex1DArray";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Tex2D";
self->enumValues[2].m_tagName = "Tex2D";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "Tex2DArray";
self->enumValues[3].m_tagName = "Tex2DArray";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "Tex2DMS";
self->enumValues[4].m_tagName = "Tex2DMS";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "Tex2DMSArray";
self->enumValues[5].m_tagName = "Tex2DMSArray";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "TexCube";
self->enumValues[6].m_tagName = "TexCube";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "TexCubeArray";
self->enumValues[7].m_tagName = "TexCubeArray";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 8;
self->enumValues[8].m_name = "Tex3D";
self->enumValues[8].m_tagName = "Tex3D";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 9;
self->enumValues[9].m_name = "Buffer";
self->enumValues[9].m_tagName = "Buffer";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 4294967295;
self->enumValues[10].m_name = "Unknown";
self->enumValues[10].m_tagName = "Unknown";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EImage),
Hash("loo::vkfg::EImage"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EImage",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EImage>) noexcept
{
return LooGetEnum<loo::vkfg::EImage>();
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

template<> struct IsSerializable<loo::vkfg::EImageUsage> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EImageUsage>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EImageUsage, 10> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "TransferSrc";
self->enumValues[0].m_tagName = "TransferSrc";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "TransferDst";
self->enumValues[1].m_tagName = "TransferDst";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4;
self->enumValues[2].m_name = "Sampled";
self->enumValues[2].m_tagName = "Sampled";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 8;
self->enumValues[3].m_name = "Storage";
self->enumValues[3].m_tagName = "Storage";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 16;
self->enumValues[4].m_name = "ColorAttachment";
self->enumValues[4].m_tagName = "ColorAttachment";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 32;
self->enumValues[5].m_name = "DepthStencilAttachment";
self->enumValues[5].m_tagName = "DepthStencilAttachment";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 64;
self->enumValues[6].m_name = "TransientAttachment";
self->enumValues[6].m_tagName = "TransientAttachment";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 128;
self->enumValues[7].m_name = "InputAttachment";
self->enumValues[7].m_tagName = "InputAttachment";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 256;
self->enumValues[8].m_name = "ShadingRate";
self->enumValues[8].m_tagName = "ShadingRate";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 3;
self->enumValues[9].m_name = "Transfer";
self->enumValues[9].m_tagName = "Transfer";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EImageUsage),
Hash("loo::vkfg::EImageUsage"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EImageUsage",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EImageUsage>) noexcept
{
return LooGetEnum<loo::vkfg::EImageUsage>();
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

template<> struct IsSerializable<loo::vkfg::EImageAspect> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EImageAspect>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EImageAspect, 7> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "Color";
self->enumValues[0].m_tagName = "Color";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "Depth";
self->enumValues[1].m_tagName = "Depth";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4;
self->enumValues[2].m_name = "Stencil";
self->enumValues[2].m_tagName = "Stencil";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 8;
self->enumValues[3].m_name = "Metadata";
self->enumValues[3].m_tagName = "Metadata";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 6;
self->enumValues[4].m_name = "DepthStencil";
self->enumValues[4].m_tagName = "DepthStencil";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 4294967295;
self->enumValues[5].m_name = "Auto";
self->enumValues[5].m_tagName = "Auto";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 0;
self->enumValues[6].m_name = "Unknown";
self->enumValues[6].m_tagName = "Unknown";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EImageAspect),
Hash("loo::vkfg::EImageAspect"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EImageAspect",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EImageAspect>) noexcept
{
return LooGetEnum<loo::vkfg::EImageAspect>();
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

template<> struct IsSerializable<loo::vkfg::EAttachmentLoadOp> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EAttachmentLoadOp>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EAttachmentLoadOp, 4> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Invalidate";
self->enumValues[0].m_tagName = "Invalidate";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Load";
self->enumValues[1].m_tagName = "Load";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Clear";
self->enumValues[2].m_tagName = "Clear";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 4294967295;
self->enumValues[3].m_name = "Unknown";
self->enumValues[3].m_tagName = "Unknown";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EAttachmentLoadOp),
Hash("loo::vkfg::EAttachmentLoadOp"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EAttachmentLoadOp",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EAttachmentLoadOp>) noexcept
{
return LooGetEnum<loo::vkfg::EAttachmentLoadOp>();
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

template<> struct IsSerializable<loo::vkfg::EAttachmentStoreOp> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EAttachmentStoreOp>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EAttachmentStoreOp, 3> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Invalidate";
self->enumValues[0].m_tagName = "Invalidate";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Store";
self->enumValues[1].m_tagName = "Store";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4294967295;
self->enumValues[2].m_name = "Unknown";
self->enumValues[2].m_tagName = "Unknown";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EAttachmentStoreOp),
Hash("loo::vkfg::EAttachmentStoreOp"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EAttachmentStoreOp",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EAttachmentStoreOp>) noexcept
{
return LooGetEnum<loo::vkfg::EAttachmentStoreOp>();
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

template<> struct IsSerializable<loo::vkfg::EShadingRatePalette> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EShadingRatePalette>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EShadingRatePalette, 12> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "NoInvocations";
self->enumValues[0].m_tagName = "NoInvocations";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Block_1x1_16";
self->enumValues[1].m_tagName = "Block_1x1_16";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Block_1x1_8";
self->enumValues[2].m_tagName = "Block_1x1_8";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "Block_1x1_4";
self->enumValues[3].m_tagName = "Block_1x1_4";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "Block_1x1_2";
self->enumValues[4].m_tagName = "Block_1x1_2";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "Block_1x1_1";
self->enumValues[5].m_tagName = "Block_1x1_1";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "Block_2x1_1";
self->enumValues[6].m_tagName = "Block_2x1_1";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "Block_1x2_1";
self->enumValues[7].m_tagName = "Block_1x2_1";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 8;
self->enumValues[8].m_name = "Block_2x2_1";
self->enumValues[8].m_tagName = "Block_2x2_1";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 9;
self->enumValues[9].m_name = "Block_4x2_1";
self->enumValues[9].m_tagName = "Block_4x2_1";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 10;
self->enumValues[10].m_name = "Block_2x4_1";
self->enumValues[10].m_tagName = "Block_2x4_1";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 11;
self->enumValues[11].m_name = "Block_4x4_1";
self->enumValues[11].m_tagName = "Block_4x4_1";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EShadingRatePalette),
Hash("loo::vkfg::EShadingRatePalette"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EShadingRatePalette",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EShadingRatePalette>) noexcept
{
return LooGetEnum<loo::vkfg::EShadingRatePalette>();
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

template<> struct IsSerializable<loo::vkfg::EPixelFormat> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EPixelFormat>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EPixelFormat, 121> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "RGBA16_SNorm";
self->enumValues[0].m_tagName = "RGBA16_SNorm";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "RGBA8_SNorm";
self->enumValues[1].m_tagName = "RGBA8_SNorm";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "RGB16_SNorm";
self->enumValues[2].m_tagName = "RGB16_SNorm";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "RGB8_SNorm";
self->enumValues[3].m_tagName = "RGB8_SNorm";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "RG16_SNorm";
self->enumValues[4].m_tagName = "RG16_SNorm";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "RG8_SNorm";
self->enumValues[5].m_tagName = "RG8_SNorm";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "R16_SNorm";
self->enumValues[6].m_tagName = "R16_SNorm";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "R8_SNorm";
self->enumValues[7].m_tagName = "R8_SNorm";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 8;
self->enumValues[8].m_name = "RGBA16_UNorm";
self->enumValues[8].m_tagName = "RGBA16_UNorm";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 9;
self->enumValues[9].m_name = "RGBA8_UNorm";
self->enumValues[9].m_tagName = "RGBA8_UNorm";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 10;
self->enumValues[10].m_name = "RGB16_UNorm";
self->enumValues[10].m_tagName = "RGB16_UNorm";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 11;
self->enumValues[11].m_name = "RGB8_UNorm";
self->enumValues[11].m_tagName = "RGB8_UNorm";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 12;
self->enumValues[12].m_name = "RG16_UNorm";
self->enumValues[12].m_tagName = "RG16_UNorm";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 13;
self->enumValues[13].m_name = "RG8_UNorm";
self->enumValues[13].m_tagName = "RG8_UNorm";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 14;
self->enumValues[14].m_name = "R16_UNorm";
self->enumValues[14].m_tagName = "R16_UNorm";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 15;
self->enumValues[15].m_name = "R8_UNorm";
self->enumValues[15].m_tagName = "R8_UNorm";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;

/* EnumConstant 17 */
self->enumValues[16].m_index = 16;
self->enumValues[16].m_value = 16;
self->enumValues[16].m_name = "RGB10_A2_UNorm";
self->enumValues[16].m_tagName = "RGB10_A2_UNorm";
self->enumValues[16].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[16].m_type = nullptr;

/* EnumConstant 18 */
self->enumValues[17].m_index = 17;
self->enumValues[17].m_value = 17;
self->enumValues[17].m_name = "RGBA4_UNorm";
self->enumValues[17].m_tagName = "RGBA4_UNorm";
self->enumValues[17].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[17].m_type = nullptr;

/* EnumConstant 19 */
self->enumValues[18].m_index = 18;
self->enumValues[18].m_value = 18;
self->enumValues[18].m_name = "RGB5_A1_UNorm";
self->enumValues[18].m_tagName = "RGB5_A1_UNorm";
self->enumValues[18].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[18].m_type = nullptr;

/* EnumConstant 20 */
self->enumValues[19].m_index = 19;
self->enumValues[19].m_value = 19;
self->enumValues[19].m_name = "RGB_5_6_5_UNorm";
self->enumValues[19].m_tagName = "RGB_5_6_5_UNorm";
self->enumValues[19].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[19].m_type = nullptr;

/* EnumConstant 21 */
self->enumValues[20].m_index = 20;
self->enumValues[20].m_value = 20;
self->enumValues[20].m_name = "BGR8_UNorm";
self->enumValues[20].m_tagName = "BGR8_UNorm";
self->enumValues[20].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[20].m_type = nullptr;

/* EnumConstant 22 */
self->enumValues[21].m_index = 21;
self->enumValues[21].m_value = 21;
self->enumValues[21].m_name = "BGRA8_UNorm";
self->enumValues[21].m_tagName = "BGRA8_UNorm";
self->enumValues[21].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[21].m_type = nullptr;

/* EnumConstant 23 */
self->enumValues[22].m_index = 22;
self->enumValues[22].m_value = 22;
self->enumValues[22].m_name = "sRGB8";
self->enumValues[22].m_tagName = "sRGB8";
self->enumValues[22].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[22].m_type = nullptr;

/* EnumConstant 24 */
self->enumValues[23].m_index = 23;
self->enumValues[23].m_value = 23;
self->enumValues[23].m_name = "sRGB8_A8";
self->enumValues[23].m_tagName = "sRGB8_A8";
self->enumValues[23].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[23].m_type = nullptr;

/* EnumConstant 25 */
self->enumValues[24].m_index = 24;
self->enumValues[24].m_value = 24;
self->enumValues[24].m_name = "sBGR8";
self->enumValues[24].m_tagName = "sBGR8";
self->enumValues[24].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[24].m_type = nullptr;

/* EnumConstant 26 */
self->enumValues[25].m_index = 25;
self->enumValues[25].m_value = 25;
self->enumValues[25].m_name = "sBGR8_A8";
self->enumValues[25].m_tagName = "sBGR8_A8";
self->enumValues[25].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[25].m_type = nullptr;

/* EnumConstant 27 */
self->enumValues[26].m_index = 26;
self->enumValues[26].m_value = 26;
self->enumValues[26].m_name = "R8I";
self->enumValues[26].m_tagName = "R8I";
self->enumValues[26].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[26].m_type = nullptr;

/* EnumConstant 28 */
self->enumValues[27].m_index = 27;
self->enumValues[27].m_value = 27;
self->enumValues[27].m_name = "RG8I";
self->enumValues[27].m_tagName = "RG8I";
self->enumValues[27].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[27].m_type = nullptr;

/* EnumConstant 29 */
self->enumValues[28].m_index = 28;
self->enumValues[28].m_value = 28;
self->enumValues[28].m_name = "RGB8I";
self->enumValues[28].m_tagName = "RGB8I";
self->enumValues[28].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[28].m_type = nullptr;

/* EnumConstant 30 */
self->enumValues[29].m_index = 29;
self->enumValues[29].m_value = 29;
self->enumValues[29].m_name = "RGBA8I";
self->enumValues[29].m_tagName = "RGBA8I";
self->enumValues[29].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[29].m_type = nullptr;

/* EnumConstant 31 */
self->enumValues[30].m_index = 30;
self->enumValues[30].m_value = 30;
self->enumValues[30].m_name = "R16I";
self->enumValues[30].m_tagName = "R16I";
self->enumValues[30].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[30].m_type = nullptr;

/* EnumConstant 32 */
self->enumValues[31].m_index = 31;
self->enumValues[31].m_value = 31;
self->enumValues[31].m_name = "RG16I";
self->enumValues[31].m_tagName = "RG16I";
self->enumValues[31].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[31].m_type = nullptr;

/* EnumConstant 33 */
self->enumValues[32].m_index = 32;
self->enumValues[32].m_value = 32;
self->enumValues[32].m_name = "RGB16I";
self->enumValues[32].m_tagName = "RGB16I";
self->enumValues[32].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[32].m_type = nullptr;

/* EnumConstant 34 */
self->enumValues[33].m_index = 33;
self->enumValues[33].m_value = 33;
self->enumValues[33].m_name = "RGBA16I";
self->enumValues[33].m_tagName = "RGBA16I";
self->enumValues[33].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[33].m_type = nullptr;

/* EnumConstant 35 */
self->enumValues[34].m_index = 34;
self->enumValues[34].m_value = 34;
self->enumValues[34].m_name = "R32I";
self->enumValues[34].m_tagName = "R32I";
self->enumValues[34].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[34].m_type = nullptr;

/* EnumConstant 36 */
self->enumValues[35].m_index = 35;
self->enumValues[35].m_value = 35;
self->enumValues[35].m_name = "RG32I";
self->enumValues[35].m_tagName = "RG32I";
self->enumValues[35].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[35].m_type = nullptr;

/* EnumConstant 37 */
self->enumValues[36].m_index = 36;
self->enumValues[36].m_value = 36;
self->enumValues[36].m_name = "RGB32I";
self->enumValues[36].m_tagName = "RGB32I";
self->enumValues[36].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[36].m_type = nullptr;

/* EnumConstant 38 */
self->enumValues[37].m_index = 37;
self->enumValues[37].m_value = 37;
self->enumValues[37].m_name = "RGBA32I";
self->enumValues[37].m_tagName = "RGBA32I";
self->enumValues[37].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[37].m_type = nullptr;

/* EnumConstant 39 */
self->enumValues[38].m_index = 38;
self->enumValues[38].m_value = 38;
self->enumValues[38].m_name = "R8U";
self->enumValues[38].m_tagName = "R8U";
self->enumValues[38].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[38].m_type = nullptr;

/* EnumConstant 40 */
self->enumValues[39].m_index = 39;
self->enumValues[39].m_value = 39;
self->enumValues[39].m_name = "RG8U";
self->enumValues[39].m_tagName = "RG8U";
self->enumValues[39].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[39].m_type = nullptr;

/* EnumConstant 41 */
self->enumValues[40].m_index = 40;
self->enumValues[40].m_value = 40;
self->enumValues[40].m_name = "RGB8U";
self->enumValues[40].m_tagName = "RGB8U";
self->enumValues[40].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[40].m_type = nullptr;

/* EnumConstant 42 */
self->enumValues[41].m_index = 41;
self->enumValues[41].m_value = 41;
self->enumValues[41].m_name = "RGBA8U";
self->enumValues[41].m_tagName = "RGBA8U";
self->enumValues[41].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[41].m_type = nullptr;

/* EnumConstant 43 */
self->enumValues[42].m_index = 42;
self->enumValues[42].m_value = 42;
self->enumValues[42].m_name = "R16U";
self->enumValues[42].m_tagName = "R16U";
self->enumValues[42].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[42].m_type = nullptr;

/* EnumConstant 44 */
self->enumValues[43].m_index = 43;
self->enumValues[43].m_value = 43;
self->enumValues[43].m_name = "RG16U";
self->enumValues[43].m_tagName = "RG16U";
self->enumValues[43].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[43].m_type = nullptr;

/* EnumConstant 45 */
self->enumValues[44].m_index = 44;
self->enumValues[44].m_value = 44;
self->enumValues[44].m_name = "RGB16U";
self->enumValues[44].m_tagName = "RGB16U";
self->enumValues[44].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[44].m_type = nullptr;

/* EnumConstant 46 */
self->enumValues[45].m_index = 45;
self->enumValues[45].m_value = 45;
self->enumValues[45].m_name = "RGBA16U";
self->enumValues[45].m_tagName = "RGBA16U";
self->enumValues[45].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[45].m_type = nullptr;

/* EnumConstant 47 */
self->enumValues[46].m_index = 46;
self->enumValues[46].m_value = 46;
self->enumValues[46].m_name = "R32U";
self->enumValues[46].m_tagName = "R32U";
self->enumValues[46].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[46].m_type = nullptr;

/* EnumConstant 48 */
self->enumValues[47].m_index = 47;
self->enumValues[47].m_value = 47;
self->enumValues[47].m_name = "RG32U";
self->enumValues[47].m_tagName = "RG32U";
self->enumValues[47].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[47].m_type = nullptr;

/* EnumConstant 49 */
self->enumValues[48].m_index = 48;
self->enumValues[48].m_value = 48;
self->enumValues[48].m_name = "RGB32U";
self->enumValues[48].m_tagName = "RGB32U";
self->enumValues[48].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[48].m_type = nullptr;

/* EnumConstant 50 */
self->enumValues[49].m_index = 49;
self->enumValues[49].m_value = 49;
self->enumValues[49].m_name = "RGBA32U";
self->enumValues[49].m_tagName = "RGBA32U";
self->enumValues[49].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[49].m_type = nullptr;

/* EnumConstant 51 */
self->enumValues[50].m_index = 50;
self->enumValues[50].m_value = 50;
self->enumValues[50].m_name = "RGB10_A2U";
self->enumValues[50].m_tagName = "RGB10_A2U";
self->enumValues[50].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[50].m_type = nullptr;

/* EnumConstant 52 */
self->enumValues[51].m_index = 51;
self->enumValues[51].m_value = 51;
self->enumValues[51].m_name = "R16F";
self->enumValues[51].m_tagName = "R16F";
self->enumValues[51].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[51].m_type = nullptr;

/* EnumConstant 53 */
self->enumValues[52].m_index = 52;
self->enumValues[52].m_value = 52;
self->enumValues[52].m_name = "RG16F";
self->enumValues[52].m_tagName = "RG16F";
self->enumValues[52].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[52].m_type = nullptr;

/* EnumConstant 54 */
self->enumValues[53].m_index = 53;
self->enumValues[53].m_value = 53;
self->enumValues[53].m_name = "RGB16F";
self->enumValues[53].m_tagName = "RGB16F";
self->enumValues[53].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[53].m_type = nullptr;

/* EnumConstant 55 */
self->enumValues[54].m_index = 54;
self->enumValues[54].m_value = 54;
self->enumValues[54].m_name = "RGBA16F";
self->enumValues[54].m_tagName = "RGBA16F";
self->enumValues[54].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[54].m_type = nullptr;

/* EnumConstant 56 */
self->enumValues[55].m_index = 55;
self->enumValues[55].m_value = 55;
self->enumValues[55].m_name = "R32F";
self->enumValues[55].m_tagName = "R32F";
self->enumValues[55].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[55].m_type = nullptr;

/* EnumConstant 57 */
self->enumValues[56].m_index = 56;
self->enumValues[56].m_value = 56;
self->enumValues[56].m_name = "RG32F";
self->enumValues[56].m_tagName = "RG32F";
self->enumValues[56].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[56].m_type = nullptr;

/* EnumConstant 58 */
self->enumValues[57].m_index = 57;
self->enumValues[57].m_value = 57;
self->enumValues[57].m_name = "RGB32F";
self->enumValues[57].m_tagName = "RGB32F";
self->enumValues[57].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[57].m_type = nullptr;

/* EnumConstant 59 */
self->enumValues[58].m_index = 58;
self->enumValues[58].m_value = 58;
self->enumValues[58].m_name = "RGBA32F";
self->enumValues[58].m_tagName = "RGBA32F";
self->enumValues[58].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[58].m_type = nullptr;

/* EnumConstant 60 */
self->enumValues[59].m_index = 59;
self->enumValues[59].m_value = 59;
self->enumValues[59].m_name = "RGB_11_11_10F";
self->enumValues[59].m_tagName = "RGB_11_11_10F";
self->enumValues[59].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[59].m_type = nullptr;

/* EnumConstant 61 */
self->enumValues[60].m_index = 60;
self->enumValues[60].m_value = 60;
self->enumValues[60].m_name = "Depth16";
self->enumValues[60].m_tagName = "Depth16";
self->enumValues[60].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[60].m_type = nullptr;

/* EnumConstant 62 */
self->enumValues[61].m_index = 61;
self->enumValues[61].m_value = 61;
self->enumValues[61].m_name = "Depth24";
self->enumValues[61].m_tagName = "Depth24";
self->enumValues[61].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[61].m_type = nullptr;

/* EnumConstant 63 */
self->enumValues[62].m_index = 62;
self->enumValues[62].m_value = 62;
self->enumValues[62].m_name = "Depth32F";
self->enumValues[62].m_tagName = "Depth32F";
self->enumValues[62].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[62].m_type = nullptr;

/* EnumConstant 64 */
self->enumValues[63].m_index = 63;
self->enumValues[63].m_value = 63;
self->enumValues[63].m_name = "Depth16_Stencil8";
self->enumValues[63].m_tagName = "Depth16_Stencil8";
self->enumValues[63].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[63].m_type = nullptr;

/* EnumConstant 65 */
self->enumValues[64].m_index = 64;
self->enumValues[64].m_value = 64;
self->enumValues[64].m_name = "Depth24_Stencil8";
self->enumValues[64].m_tagName = "Depth24_Stencil8";
self->enumValues[64].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[64].m_type = nullptr;

/* EnumConstant 66 */
self->enumValues[65].m_index = 65;
self->enumValues[65].m_value = 65;
self->enumValues[65].m_name = "Depth32F_Stencil8";
self->enumValues[65].m_tagName = "Depth32F_Stencil8";
self->enumValues[65].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[65].m_type = nullptr;

/* EnumConstant 67 */
self->enumValues[66].m_index = 66;
self->enumValues[66].m_value = 66;
self->enumValues[66].m_name = "BC1_RGB8_UNorm";
self->enumValues[66].m_tagName = "BC1_RGB8_UNorm";
self->enumValues[66].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[66].m_type = nullptr;

/* EnumConstant 68 */
self->enumValues[67].m_index = 67;
self->enumValues[67].m_value = 67;
self->enumValues[67].m_name = "BC1_sRGB8_UNorm";
self->enumValues[67].m_tagName = "BC1_sRGB8_UNorm";
self->enumValues[67].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[67].m_type = nullptr;

/* EnumConstant 69 */
self->enumValues[68].m_index = 68;
self->enumValues[68].m_value = 68;
self->enumValues[68].m_name = "BC1_RGB8_A1_UNorm";
self->enumValues[68].m_tagName = "BC1_RGB8_A1_UNorm";
self->enumValues[68].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[68].m_type = nullptr;

/* EnumConstant 70 */
self->enumValues[69].m_index = 69;
self->enumValues[69].m_value = 69;
self->enumValues[69].m_name = "BC1_sRGB8_A1_UNorm";
self->enumValues[69].m_tagName = "BC1_sRGB8_A1_UNorm";
self->enumValues[69].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[69].m_type = nullptr;

/* EnumConstant 71 */
self->enumValues[70].m_index = 70;
self->enumValues[70].m_value = 70;
self->enumValues[70].m_name = "BC2_RGBA8_UNorm";
self->enumValues[70].m_tagName = "BC2_RGBA8_UNorm";
self->enumValues[70].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[70].m_type = nullptr;

/* EnumConstant 72 */
self->enumValues[71].m_index = 71;
self->enumValues[71].m_value = 71;
self->enumValues[71].m_name = "BC3_RGBA8_UNorm";
self->enumValues[71].m_tagName = "BC3_RGBA8_UNorm";
self->enumValues[71].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[71].m_type = nullptr;

/* EnumConstant 73 */
self->enumValues[72].m_index = 72;
self->enumValues[72].m_value = 72;
self->enumValues[72].m_name = "BC3_sRGB";
self->enumValues[72].m_tagName = "BC3_sRGB";
self->enumValues[72].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[72].m_type = nullptr;

/* EnumConstant 74 */
self->enumValues[73].m_index = 73;
self->enumValues[73].m_value = 73;
self->enumValues[73].m_name = "BC4_RED8_SNorm";
self->enumValues[73].m_tagName = "BC4_RED8_SNorm";
self->enumValues[73].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[73].m_type = nullptr;

/* EnumConstant 75 */
self->enumValues[74].m_index = 74;
self->enumValues[74].m_value = 74;
self->enumValues[74].m_name = "BC4_RED8_UNorm";
self->enumValues[74].m_tagName = "BC4_RED8_UNorm";
self->enumValues[74].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[74].m_type = nullptr;

/* EnumConstant 76 */
self->enumValues[75].m_index = 75;
self->enumValues[75].m_value = 75;
self->enumValues[75].m_name = "BC5_RG8_SNorm";
self->enumValues[75].m_tagName = "BC5_RG8_SNorm";
self->enumValues[75].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[75].m_type = nullptr;

/* EnumConstant 77 */
self->enumValues[76].m_index = 76;
self->enumValues[76].m_value = 76;
self->enumValues[76].m_name = "BC5_RG8_UNorm";
self->enumValues[76].m_tagName = "BC5_RG8_UNorm";
self->enumValues[76].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[76].m_type = nullptr;

/* EnumConstant 78 */
self->enumValues[77].m_index = 77;
self->enumValues[77].m_value = 77;
self->enumValues[77].m_name = "BC7_RGBA8_UNorm";
self->enumValues[77].m_tagName = "BC7_RGBA8_UNorm";
self->enumValues[77].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[77].m_type = nullptr;

/* EnumConstant 79 */
self->enumValues[78].m_index = 78;
self->enumValues[78].m_value = 78;
self->enumValues[78].m_name = "BC7_SRGB8_A8";
self->enumValues[78].m_tagName = "BC7_SRGB8_A8";
self->enumValues[78].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[78].m_type = nullptr;

/* EnumConstant 80 */
self->enumValues[79].m_index = 79;
self->enumValues[79].m_value = 79;
self->enumValues[79].m_name = "BC6H_RGB16F";
self->enumValues[79].m_tagName = "BC6H_RGB16F";
self->enumValues[79].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[79].m_type = nullptr;

/* EnumConstant 81 */
self->enumValues[80].m_index = 80;
self->enumValues[80].m_value = 80;
self->enumValues[80].m_name = "BC6H_RGB16UF";
self->enumValues[80].m_tagName = "BC6H_RGB16UF";
self->enumValues[80].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[80].m_type = nullptr;

/* EnumConstant 82 */
self->enumValues[81].m_index = 81;
self->enumValues[81].m_value = 81;
self->enumValues[81].m_name = "ETC2_RGB8_UNorm";
self->enumValues[81].m_tagName = "ETC2_RGB8_UNorm";
self->enumValues[81].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[81].m_type = nullptr;

/* EnumConstant 83 */
self->enumValues[82].m_index = 82;
self->enumValues[82].m_value = 82;
self->enumValues[82].m_name = "ECT2_SRGB8";
self->enumValues[82].m_tagName = "ECT2_SRGB8";
self->enumValues[82].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[82].m_type = nullptr;

/* EnumConstant 84 */
self->enumValues[83].m_index = 83;
self->enumValues[83].m_value = 83;
self->enumValues[83].m_name = "ETC2_RGB8_A1_UNorm";
self->enumValues[83].m_tagName = "ETC2_RGB8_A1_UNorm";
self->enumValues[83].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[83].m_type = nullptr;

/* EnumConstant 85 */
self->enumValues[84].m_index = 84;
self->enumValues[84].m_value = 84;
self->enumValues[84].m_name = "ETC2_SRGB8_A1";
self->enumValues[84].m_tagName = "ETC2_SRGB8_A1";
self->enumValues[84].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[84].m_type = nullptr;

/* EnumConstant 86 */
self->enumValues[85].m_index = 85;
self->enumValues[85].m_value = 85;
self->enumValues[85].m_name = "ETC2_RGBA8_UNorm";
self->enumValues[85].m_tagName = "ETC2_RGBA8_UNorm";
self->enumValues[85].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[85].m_type = nullptr;

/* EnumConstant 87 */
self->enumValues[86].m_index = 86;
self->enumValues[86].m_value = 86;
self->enumValues[86].m_name = "ETC2_SRGB8_A8";
self->enumValues[86].m_tagName = "ETC2_SRGB8_A8";
self->enumValues[86].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[86].m_type = nullptr;

/* EnumConstant 88 */
self->enumValues[87].m_index = 87;
self->enumValues[87].m_value = 87;
self->enumValues[87].m_name = "EAC_R11_SNorm";
self->enumValues[87].m_tagName = "EAC_R11_SNorm";
self->enumValues[87].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[87].m_type = nullptr;

/* EnumConstant 89 */
self->enumValues[88].m_index = 88;
self->enumValues[88].m_value = 88;
self->enumValues[88].m_name = "EAC_R11_UNorm";
self->enumValues[88].m_tagName = "EAC_R11_UNorm";
self->enumValues[88].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[88].m_type = nullptr;

/* EnumConstant 90 */
self->enumValues[89].m_index = 89;
self->enumValues[89].m_value = 89;
self->enumValues[89].m_name = "EAC_RG11_SNorm";
self->enumValues[89].m_tagName = "EAC_RG11_SNorm";
self->enumValues[89].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[89].m_type = nullptr;

/* EnumConstant 91 */
self->enumValues[90].m_index = 90;
self->enumValues[90].m_value = 90;
self->enumValues[90].m_name = "EAC_RG11_UNorm";
self->enumValues[90].m_tagName = "EAC_RG11_UNorm";
self->enumValues[90].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[90].m_type = nullptr;

/* EnumConstant 92 */
self->enumValues[91].m_index = 91;
self->enumValues[91].m_value = 91;
self->enumValues[91].m_name = "ASTC_RGBA_4x4";
self->enumValues[91].m_tagName = "ASTC_RGBA_4x4";
self->enumValues[91].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[91].m_type = nullptr;

/* EnumConstant 93 */
self->enumValues[92].m_index = 92;
self->enumValues[92].m_value = 92;
self->enumValues[92].m_name = "ASTC_RGBA_5x4";
self->enumValues[92].m_tagName = "ASTC_RGBA_5x4";
self->enumValues[92].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[92].m_type = nullptr;

/* EnumConstant 94 */
self->enumValues[93].m_index = 93;
self->enumValues[93].m_value = 93;
self->enumValues[93].m_name = "ASTC_RGBA_5x5";
self->enumValues[93].m_tagName = "ASTC_RGBA_5x5";
self->enumValues[93].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[93].m_type = nullptr;

/* EnumConstant 95 */
self->enumValues[94].m_index = 94;
self->enumValues[94].m_value = 94;
self->enumValues[94].m_name = "ASTC_RGBA_6x5";
self->enumValues[94].m_tagName = "ASTC_RGBA_6x5";
self->enumValues[94].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[94].m_type = nullptr;

/* EnumConstant 96 */
self->enumValues[95].m_index = 95;
self->enumValues[95].m_value = 95;
self->enumValues[95].m_name = "ASTC_RGBA_6x6";
self->enumValues[95].m_tagName = "ASTC_RGBA_6x6";
self->enumValues[95].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[95].m_type = nullptr;

/* EnumConstant 97 */
self->enumValues[96].m_index = 96;
self->enumValues[96].m_value = 96;
self->enumValues[96].m_name = "ASTC_RGBA_8x5";
self->enumValues[96].m_tagName = "ASTC_RGBA_8x5";
self->enumValues[96].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[96].m_type = nullptr;

/* EnumConstant 98 */
self->enumValues[97].m_index = 97;
self->enumValues[97].m_value = 97;
self->enumValues[97].m_name = "ASTC_RGBA_8x6";
self->enumValues[97].m_tagName = "ASTC_RGBA_8x6";
self->enumValues[97].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[97].m_type = nullptr;

/* EnumConstant 99 */
self->enumValues[98].m_index = 98;
self->enumValues[98].m_value = 98;
self->enumValues[98].m_name = "ASTC_RGBA_8x8";
self->enumValues[98].m_tagName = "ASTC_RGBA_8x8";
self->enumValues[98].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[98].m_type = nullptr;

/* EnumConstant 100 */
self->enumValues[99].m_index = 99;
self->enumValues[99].m_value = 99;
self->enumValues[99].m_name = "ASTC_RGBA_10x5";
self->enumValues[99].m_tagName = "ASTC_RGBA_10x5";
self->enumValues[99].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[99].m_type = nullptr;

/* EnumConstant 101 */
self->enumValues[100].m_index = 100;
self->enumValues[100].m_value = 100;
self->enumValues[100].m_name = "ASTC_RGBA_10x6";
self->enumValues[100].m_tagName = "ASTC_RGBA_10x6";
self->enumValues[100].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[100].m_type = nullptr;

/* EnumConstant 102 */
self->enumValues[101].m_index = 101;
self->enumValues[101].m_value = 101;
self->enumValues[101].m_name = "ASTC_RGBA_10x8";
self->enumValues[101].m_tagName = "ASTC_RGBA_10x8";
self->enumValues[101].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[101].m_type = nullptr;

/* EnumConstant 103 */
self->enumValues[102].m_index = 102;
self->enumValues[102].m_value = 102;
self->enumValues[102].m_name = "ASTC_RGBA_10x10";
self->enumValues[102].m_tagName = "ASTC_RGBA_10x10";
self->enumValues[102].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[102].m_type = nullptr;

/* EnumConstant 104 */
self->enumValues[103].m_index = 103;
self->enumValues[103].m_value = 103;
self->enumValues[103].m_name = "ASTC_RGBA_12x10";
self->enumValues[103].m_tagName = "ASTC_RGBA_12x10";
self->enumValues[103].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[103].m_type = nullptr;

/* EnumConstant 105 */
self->enumValues[104].m_index = 104;
self->enumValues[104].m_value = 104;
self->enumValues[104].m_name = "ASTC_RGBA_12x12";
self->enumValues[104].m_tagName = "ASTC_RGBA_12x12";
self->enumValues[104].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[104].m_type = nullptr;

/* EnumConstant 106 */
self->enumValues[105].m_index = 105;
self->enumValues[105].m_value = 105;
self->enumValues[105].m_name = "ASTC_SRGB8_A8_4x4";
self->enumValues[105].m_tagName = "ASTC_SRGB8_A8_4x4";
self->enumValues[105].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[105].m_type = nullptr;

/* EnumConstant 107 */
self->enumValues[106].m_index = 106;
self->enumValues[106].m_value = 106;
self->enumValues[106].m_name = "ASTC_SRGB8_A8_5x4";
self->enumValues[106].m_tagName = "ASTC_SRGB8_A8_5x4";
self->enumValues[106].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[106].m_type = nullptr;

/* EnumConstant 108 */
self->enumValues[107].m_index = 107;
self->enumValues[107].m_value = 107;
self->enumValues[107].m_name = "ASTC_SRGB8_A8_5x5";
self->enumValues[107].m_tagName = "ASTC_SRGB8_A8_5x5";
self->enumValues[107].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[107].m_type = nullptr;

/* EnumConstant 109 */
self->enumValues[108].m_index = 108;
self->enumValues[108].m_value = 108;
self->enumValues[108].m_name = "ASTC_SRGB8_A8_6x5";
self->enumValues[108].m_tagName = "ASTC_SRGB8_A8_6x5";
self->enumValues[108].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[108].m_type = nullptr;

/* EnumConstant 110 */
self->enumValues[109].m_index = 109;
self->enumValues[109].m_value = 109;
self->enumValues[109].m_name = "ASTC_SRGB8_A8_6x6";
self->enumValues[109].m_tagName = "ASTC_SRGB8_A8_6x6";
self->enumValues[109].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[109].m_type = nullptr;

/* EnumConstant 111 */
self->enumValues[110].m_index = 110;
self->enumValues[110].m_value = 110;
self->enumValues[110].m_name = "ASTC_SRGB8_A8_8x5";
self->enumValues[110].m_tagName = "ASTC_SRGB8_A8_8x5";
self->enumValues[110].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[110].m_type = nullptr;

/* EnumConstant 112 */
self->enumValues[111].m_index = 111;
self->enumValues[111].m_value = 111;
self->enumValues[111].m_name = "ASTC_SRGB8_A8_8x6";
self->enumValues[111].m_tagName = "ASTC_SRGB8_A8_8x6";
self->enumValues[111].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[111].m_type = nullptr;

/* EnumConstant 113 */
self->enumValues[112].m_index = 112;
self->enumValues[112].m_value = 112;
self->enumValues[112].m_name = "ASTC_SRGB8_A8_8x8";
self->enumValues[112].m_tagName = "ASTC_SRGB8_A8_8x8";
self->enumValues[112].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[112].m_type = nullptr;

/* EnumConstant 114 */
self->enumValues[113].m_index = 113;
self->enumValues[113].m_value = 113;
self->enumValues[113].m_name = "ASTC_SRGB8_A8_10x5";
self->enumValues[113].m_tagName = "ASTC_SRGB8_A8_10x5";
self->enumValues[113].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[113].m_type = nullptr;

/* EnumConstant 115 */
self->enumValues[114].m_index = 114;
self->enumValues[114].m_value = 114;
self->enumValues[114].m_name = "ASTC_SRGB8_A8_10x6";
self->enumValues[114].m_tagName = "ASTC_SRGB8_A8_10x6";
self->enumValues[114].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[114].m_type = nullptr;

/* EnumConstant 116 */
self->enumValues[115].m_index = 115;
self->enumValues[115].m_value = 115;
self->enumValues[115].m_name = "ASTC_SRGB8_A8_10x8";
self->enumValues[115].m_tagName = "ASTC_SRGB8_A8_10x8";
self->enumValues[115].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[115].m_type = nullptr;

/* EnumConstant 117 */
self->enumValues[116].m_index = 116;
self->enumValues[116].m_value = 116;
self->enumValues[116].m_name = "ASTC_SRGB8_A8_10x10";
self->enumValues[116].m_tagName = "ASTC_SRGB8_A8_10x10";
self->enumValues[116].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[116].m_type = nullptr;

/* EnumConstant 118 */
self->enumValues[117].m_index = 117;
self->enumValues[117].m_value = 117;
self->enumValues[117].m_name = "ASTC_SRGB8_A8_12x10";
self->enumValues[117].m_tagName = "ASTC_SRGB8_A8_12x10";
self->enumValues[117].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[117].m_type = nullptr;

/* EnumConstant 119 */
self->enumValues[118].m_index = 118;
self->enumValues[118].m_value = 118;
self->enumValues[118].m_name = "ASTC_SRGB8_A8_12x12";
self->enumValues[118].m_tagName = "ASTC_SRGB8_A8_12x12";
self->enumValues[118].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[118].m_type = nullptr;

/* EnumConstant 120 */
self->enumValues[119].m_index = 119;
self->enumValues[119].m_value = 119;
self->enumValues[119].m_name = "_Count";
self->enumValues[119].m_tagName = "_Count";
self->enumValues[119].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[119].m_type = nullptr;

/* EnumConstant 121 */
self->enumValues[120].m_index = 120;
self->enumValues[120].m_value = 4294967295;
self->enumValues[120].m_name = "Unknown";
self->enumValues[120].m_tagName = "Unknown";
self->enumValues[120].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[120].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EPixelFormat),
Hash("loo::vkfg::EPixelFormat"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EPixelFormat",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EPixelFormat>) noexcept
{
return LooGetEnum<loo::vkfg::EPixelFormat>();
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

template<> struct IsSerializable<loo::vkfg::EFragOutput> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EFragOutput>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EFragOutput, 4> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Unknown";
self->enumValues[0].m_tagName = "Unknown";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 37;
self->enumValues[1].m_name = "Int4";
self->enumValues[1].m_tagName = "Int4";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 49;
self->enumValues[2].m_name = "UInt4";
self->enumValues[2].m_tagName = "UInt4";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 58;
self->enumValues[3].m_name = "Float4";
self->enumValues[3].m_tagName = "Float4";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EFragOutput),
Hash("loo::vkfg::EFragOutput"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EFragOutput",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EFragOutput>) noexcept
{
return LooGetEnum<loo::vkfg::EFragOutput>();
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

template<> struct IsSerializable<loo::vkfg::EFilter> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EFilter>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EFilter, 3> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Nearest";
self->enumValues[0].m_tagName = "Nearest";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Linear";
self->enumValues[1].m_tagName = "Linear";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4294967295;
self->enumValues[2].m_name = "Unknown";
self->enumValues[2].m_tagName = "Unknown";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EFilter),
Hash("loo::vkfg::EFilter"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EFilter",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EFilter>) noexcept
{
return LooGetEnum<loo::vkfg::EFilter>();
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

template<> struct IsSerializable<loo::vkfg::EMipmapFilter> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EMipmapFilter>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EMipmapFilter, 3> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Nearest";
self->enumValues[0].m_tagName = "Nearest";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Linear";
self->enumValues[1].m_tagName = "Linear";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4294967295;
self->enumValues[2].m_name = "Unknown";
self->enumValues[2].m_tagName = "Unknown";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EMipmapFilter),
Hash("loo::vkfg::EMipmapFilter"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EMipmapFilter",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EMipmapFilter>) noexcept
{
return LooGetEnum<loo::vkfg::EMipmapFilter>();
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

template<> struct IsSerializable<loo::vkfg::EAddressMode> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EAddressMode>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EAddressMode, 6> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Repeat";
self->enumValues[0].m_tagName = "Repeat";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "MirrorRepeat";
self->enumValues[1].m_tagName = "MirrorRepeat";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "ClampToEdge";
self->enumValues[2].m_tagName = "ClampToEdge";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "ClampToBorder";
self->enumValues[3].m_tagName = "ClampToBorder";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "MirrorClampToEdge";
self->enumValues[4].m_tagName = "MirrorClampToEdge";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 4294967295;
self->enumValues[5].m_name = "Unknown";
self->enumValues[5].m_tagName = "Unknown";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EAddressMode),
Hash("loo::vkfg::EAddressMode"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EAddressMode",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EAddressMode>) noexcept
{
return LooGetEnum<loo::vkfg::EAddressMode>();
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

template<> struct IsSerializable<loo::vkfg::EBorderColor> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EBorderColor>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EBorderColor, 7> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "FloatTransparentBlack";
self->enumValues[0].m_tagName = "FloatTransparentBlack";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "FloatOpaqueBlack";
self->enumValues[1].m_tagName = "FloatOpaqueBlack";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "FloatOpaqueWhite";
self->enumValues[2].m_tagName = "FloatOpaqueWhite";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "IntTransparentBlack";
self->enumValues[3].m_tagName = "IntTransparentBlack";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "IntOpaqueBlack";
self->enumValues[4].m_tagName = "IntOpaqueBlack";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "IntOpaqueWhite";
self->enumValues[5].m_tagName = "IntOpaqueWhite";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 4294967295;
self->enumValues[6].m_name = "Unknown";
self->enumValues[6].m_tagName = "Unknown";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EBorderColor),
Hash("loo::vkfg::EBorderColor"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EBorderColor",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EBorderColor>) noexcept
{
return LooGetEnum<loo::vkfg::EBorderColor>();
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

template<> struct IsSerializable<loo::vkfg::EShader> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EShader>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EShader, 16> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Vertex";
self->enumValues[0].m_tagName = "Vertex";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "TessControl";
self->enumValues[1].m_tagName = "TessControl";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "TessEvaluation";
self->enumValues[2].m_tagName = "TessEvaluation";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "Geometry";
self->enumValues[3].m_tagName = "Geometry";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "Fragment";
self->enumValues[4].m_tagName = "Fragment";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "Compute";
self->enumValues[5].m_tagName = "Compute";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "MeshTask";
self->enumValues[6].m_tagName = "MeshTask";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "Mesh";
self->enumValues[7].m_tagName = "Mesh";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 8;
self->enumValues[8].m_name = "RayGen";
self->enumValues[8].m_tagName = "RayGen";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 9;
self->enumValues[9].m_name = "RayAnyHit";
self->enumValues[9].m_tagName = "RayAnyHit";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 10;
self->enumValues[10].m_name = "RayClosestHit";
self->enumValues[10].m_tagName = "RayClosestHit";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 11;
self->enumValues[11].m_name = "RayMiss";
self->enumValues[11].m_tagName = "RayMiss";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 12;
self->enumValues[12].m_name = "RayIntersection";
self->enumValues[12].m_tagName = "RayIntersection";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 13;
self->enumValues[13].m_name = "RayCallable";
self->enumValues[13].m_tagName = "RayCallable";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 14;
self->enumValues[14].m_name = "_Count";
self->enumValues[14].m_tagName = "_Count";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 4294967295;
self->enumValues[15].m_name = "Unknown";
self->enumValues[15].m_tagName = "Unknown";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EShader),
Hash("loo::vkfg::EShader"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EShader",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EShader>) noexcept
{
return LooGetEnum<loo::vkfg::EShader>();
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

template<> struct IsSerializable<loo::vkfg::EShaderStages> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EShaderStages>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EShaderStages, 18> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "Vertex";
self->enumValues[0].m_tagName = "Vertex";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "TessControl";
self->enumValues[1].m_tagName = "TessControl";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4;
self->enumValues[2].m_name = "TessEvaluation";
self->enumValues[2].m_tagName = "TessEvaluation";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 8;
self->enumValues[3].m_name = "Geometry";
self->enumValues[3].m_tagName = "Geometry";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 16;
self->enumValues[4].m_name = "Fragment";
self->enumValues[4].m_tagName = "Fragment";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 32;
self->enumValues[5].m_name = "Compute";
self->enumValues[5].m_tagName = "Compute";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 64;
self->enumValues[6].m_name = "MeshTask";
self->enumValues[6].m_tagName = "MeshTask";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 128;
self->enumValues[7].m_name = "Mesh";
self->enumValues[7].m_tagName = "Mesh";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 256;
self->enumValues[8].m_name = "RayGen";
self->enumValues[8].m_tagName = "RayGen";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 512;
self->enumValues[9].m_name = "RayAnyHit";
self->enumValues[9].m_tagName = "RayAnyHit";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 1024;
self->enumValues[10].m_name = "RayClosestHit";
self->enumValues[10].m_tagName = "RayClosestHit";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 2048;
self->enumValues[11].m_name = "RayMiss";
self->enumValues[11].m_tagName = "RayMiss";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 4096;
self->enumValues[12].m_name = "RayIntersection";
self->enumValues[12].m_tagName = "RayIntersection";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 8192;
self->enumValues[13].m_name = "RayCallable";
self->enumValues[13].m_tagName = "RayCallable";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 16383;
self->enumValues[14].m_name = "All";
self->enumValues[14].m_tagName = "All";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 223;
self->enumValues[15].m_name = "AllGraphics";
self->enumValues[15].m_tagName = "AllGraphics";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;

/* EnumConstant 17 */
self->enumValues[16].m_index = 16;
self->enumValues[16].m_value = 16128;
self->enumValues[16].m_name = "AllRayTracing";
self->enumValues[16].m_tagName = "AllRayTracing";
self->enumValues[16].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[16].m_type = nullptr;

/* EnumConstant 18 */
self->enumValues[17].m_index = 17;
self->enumValues[17].m_value = 0;
self->enumValues[17].m_name = "Unknown";
self->enumValues[17].m_tagName = "Unknown";
self->enumValues[17].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[17].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EShaderStages),
Hash("loo::vkfg::EShaderStages"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EShaderStages",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EShaderStages>) noexcept
{
return LooGetEnum<loo::vkfg::EShaderStages>();
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

template<> struct IsSerializable<loo::vkfg::EShaderAccess> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EShaderAccess>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EShaderAccess, 4> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "ReadOnly";
self->enumValues[0].m_tagName = "ReadOnly";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "WriteOnly";
self->enumValues[1].m_tagName = "WriteOnly";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "WriteDiscard";
self->enumValues[2].m_tagName = "WriteDiscard";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "ReadWrite";
self->enumValues[3].m_tagName = "ReadWrite";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EShaderAccess),
Hash("loo::vkfg::EShaderAccess"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EShaderAccess",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EShaderAccess>) noexcept
{
return LooGetEnum<loo::vkfg::EShaderAccess>();
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

template<> struct IsSerializable<loo::vkfg::EShaderLangFormat> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EShaderLangFormat>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EShaderLangFormat, 66> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 18;
self->enumValues[0].m_name = "_ApiOffset";
self->enumValues[0].m_tagName = "_ApiOffset";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 3932160;
self->enumValues[1].m_name = "_ApiMask";
self->enumValues[1].m_tagName = "_ApiMask";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 262144;
self->enumValues[2].m_name = "OpenGL";
self->enumValues[2].m_tagName = "OpenGL";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 524288;
self->enumValues[3].m_name = "OpenGLES";
self->enumValues[3].m_tagName = "OpenGLES";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 786432;
self->enumValues[4].m_name = "DirectX";
self->enumValues[4].m_tagName = "DirectX";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 1048576;
self->enumValues[5].m_name = "OpenCL";
self->enumValues[5].m_tagName = "OpenCL";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 1310720;
self->enumValues[6].m_name = "Vulkan";
self->enumValues[6].m_tagName = "Vulkan";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 1572864;
self->enumValues[7].m_name = "Metal";
self->enumValues[7].m_tagName = "Metal";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 1835008;
self->enumValues[8].m_name = "CUDA";
self->enumValues[8].m_tagName = "CUDA";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 2097152;
self->enumValues[9].m_name = "Software";
self->enumValues[9].m_tagName = "Software";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 8;
self->enumValues[10].m_name = "_VersionOffset";
self->enumValues[10].m_tagName = "_VersionOffset";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 261888;
self->enumValues[11].m_name = "_VersionMask";
self->enumValues[11].m_tagName = "_VersionMask";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 346624;
self->enumValues[12].m_name = "OpenGL_330";
self->enumValues[12].m_tagName = "OpenGL_330";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 369664;
self->enumValues[13].m_name = "OpenGL_420";
self->enumValues[13].m_tagName = "OpenGL_420";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 372224;
self->enumValues[14].m_name = "OpenGL_430";
self->enumValues[14].m_tagName = "OpenGL_430";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 374784;
self->enumValues[15].m_name = "OpenGL_440";
self->enumValues[15].m_tagName = "OpenGL_440";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;

/* EnumConstant 17 */
self->enumValues[16].m_index = 16;
self->enumValues[16].m_value = 377344;
self->enumValues[16].m_name = "OpenGL_450";
self->enumValues[16].m_tagName = "OpenGL_450";
self->enumValues[16].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[16].m_type = nullptr;

/* EnumConstant 18 */
self->enumValues[17].m_index = 17;
self->enumValues[17].m_value = 379904;
self->enumValues[17].m_name = "OpenGL_460";
self->enumValues[17].m_tagName = "OpenGL_460";
self->enumValues[17].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[17].m_type = nullptr;

/* EnumConstant 19 */
self->enumValues[18].m_index = 18;
self->enumValues[18].m_value = 575488;
self->enumValues[18].m_name = "OpenGLES_200";
self->enumValues[18].m_tagName = "OpenGLES_200";
self->enumValues[18].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[18].m_type = nullptr;

/* EnumConstant 20 */
self->enumValues[19].m_index = 19;
self->enumValues[19].m_value = 601088;
self->enumValues[19].m_name = "OpenGLES_300";
self->enumValues[19].m_tagName = "OpenGLES_300";
self->enumValues[19].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[19].m_type = nullptr;

/* EnumConstant 21 */
self->enumValues[20].m_index = 20;
self->enumValues[20].m_value = 603648;
self->enumValues[20].m_name = "OpenGLES_310";
self->enumValues[20].m_tagName = "OpenGLES_310";
self->enumValues[20].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[20].m_type = nullptr;

/* EnumConstant 22 */
self->enumValues[21].m_index = 21;
self->enumValues[21].m_value = 606208;
self->enumValues[21].m_name = "OpenGLES_320";
self->enumValues[21].m_tagName = "OpenGLES_320";
self->enumValues[21].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[21].m_type = nullptr;

/* EnumConstant 23 */
self->enumValues[22].m_index = 22;
self->enumValues[22].m_value = 812032;
self->enumValues[22].m_name = "DirectX_10";
self->enumValues[22].m_tagName = "DirectX_10";
self->enumValues[22].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[22].m_type = nullptr;

/* EnumConstant 24 */
self->enumValues[23].m_index = 23;
self->enumValues[23].m_value = 814592;
self->enumValues[23].m_name = "DirectX_11";
self->enumValues[23].m_tagName = "DirectX_11";
self->enumValues[23].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[23].m_type = nullptr;

/* EnumConstant 25 */
self->enumValues[24].m_index = 24;
self->enumValues[24].m_value = 817152;
self->enumValues[24].m_name = "DirectX_12";
self->enumValues[24].m_tagName = "DirectX_12";
self->enumValues[24].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[24].m_type = nullptr;

/* EnumConstant 26 */
self->enumValues[25].m_index = 25;
self->enumValues[25].m_value = 1079296;
self->enumValues[25].m_name = "OpenCL_120";
self->enumValues[25].m_tagName = "OpenCL_120";
self->enumValues[25].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[25].m_type = nullptr;

/* EnumConstant 27 */
self->enumValues[26].m_index = 26;
self->enumValues[26].m_value = 1099776;
self->enumValues[26].m_name = "OpenCL_200";
self->enumValues[26].m_tagName = "OpenCL_200";
self->enumValues[26].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[26].m_type = nullptr;

/* EnumConstant 28 */
self->enumValues[27].m_index = 27;
self->enumValues[27].m_value = 1102336;
self->enumValues[27].m_name = "OpenCL_210";
self->enumValues[27].m_tagName = "OpenCL_210";
self->enumValues[27].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[27].m_type = nullptr;

/* EnumConstant 29 */
self->enumValues[28].m_index = 28;
self->enumValues[28].m_value = 1336320;
self->enumValues[28].m_name = "Vulkan_100";
self->enumValues[28].m_tagName = "Vulkan_100";
self->enumValues[28].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[28].m_type = nullptr;

/* EnumConstant 30 */
self->enumValues[29].m_index = 29;
self->enumValues[29].m_value = 1338880;
self->enumValues[29].m_name = "Vulkan_110";
self->enumValues[29].m_tagName = "Vulkan_110";
self->enumValues[29].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[29].m_type = nullptr;

/* EnumConstant 31 */
self->enumValues[30].m_index = 30;
self->enumValues[30].m_value = 2122752;
self->enumValues[30].m_name = "Software_100";
self->enumValues[30].m_tagName = "Software_100";
self->enumValues[30].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[30].m_type = nullptr;

/* EnumConstant 32 */
self->enumValues[31].m_index = 31;
self->enumValues[31].m_value = 4;
self->enumValues[31].m_name = "_StorageOffset";
self->enumValues[31].m_tagName = "_StorageOffset";
self->enumValues[31].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[31].m_type = nullptr;

/* EnumConstant 33 */
self->enumValues[32].m_index = 32;
self->enumValues[32].m_value = 240;
self->enumValues[32].m_name = "_StorageMask";
self->enumValues[32].m_tagName = "_StorageMask";
self->enumValues[32].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[32].m_type = nullptr;

/* EnumConstant 34 */
self->enumValues[33].m_index = 33;
self->enumValues[33].m_value = 16;
self->enumValues[33].m_name = "Source";
self->enumValues[33].m_tagName = "Source";
self->enumValues[33].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[33].m_type = nullptr;

/* EnumConstant 35 */
self->enumValues[34].m_index = 34;
self->enumValues[34].m_value = 32;
self->enumValues[34].m_name = "Binary";
self->enumValues[34].m_tagName = "Binary";
self->enumValues[34].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[34].m_type = nullptr;

/* EnumConstant 36 */
self->enumValues[35].m_index = 35;
self->enumValues[35].m_value = 48;
self->enumValues[35].m_name = "Executable";
self->enumValues[35].m_tagName = "Executable";
self->enumValues[35].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[35].m_type = nullptr;

/* EnumConstant 37 */
self->enumValues[36].m_index = 36;
self->enumValues[36].m_value = 0;
self->enumValues[36].m_name = "_FormatOffset";
self->enumValues[36].m_tagName = "_FormatOffset";
self->enumValues[36].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[36].m_type = nullptr;

/* EnumConstant 38 */
self->enumValues[37].m_index = 37;
self->enumValues[37].m_value = 15;
self->enumValues[37].m_name = "_FormatMask";
self->enumValues[37].m_tagName = "_FormatMask";
self->enumValues[37].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[37].m_type = nullptr;

/* EnumConstant 39 */
self->enumValues[38].m_index = 38;
self->enumValues[38].m_value = 17;
self->enumValues[38].m_name = "HighLevel";
self->enumValues[38].m_tagName = "HighLevel";
self->enumValues[38].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[38].m_type = nullptr;

/* EnumConstant 40 */
self->enumValues[39].m_index = 39;
self->enumValues[39].m_value = 34;
self->enumValues[39].m_name = "SPIRV";
self->enumValues[39].m_tagName = "SPIRV";
self->enumValues[39].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[39].m_type = nullptr;

/* EnumConstant 41 */
self->enumValues[40].m_index = 40;
self->enumValues[40].m_value = 35;
self->enumValues[40].m_name = "GL_Binary";
self->enumValues[40].m_tagName = "GL_Binary";
self->enumValues[40].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[40].m_type = nullptr;

/* EnumConstant 42 */
self->enumValues[41].m_index = 41;
self->enumValues[41].m_value = 36;
self->enumValues[41].m_name = "DXBC";
self->enumValues[41].m_tagName = "DXBC";
self->enumValues[41].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[41].m_type = nullptr;

/* EnumConstant 43 */
self->enumValues[42].m_index = 42;
self->enumValues[42].m_value = 37;
self->enumValues[42].m_name = "DXIL";
self->enumValues[42].m_tagName = "DXIL";
self->enumValues[42].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[42].m_type = nullptr;

/* EnumConstant 44 */
self->enumValues[43].m_index = 43;
self->enumValues[43].m_value = 22;
self->enumValues[43].m_name = "Assembler";
self->enumValues[43].m_tagName = "Assembler";
self->enumValues[43].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[43].m_type = nullptr;

/* EnumConstant 45 */
self->enumValues[44].m_index = 44;
self->enumValues[44].m_value = 55;
self->enumValues[44].m_name = "Invocable";
self->enumValues[44].m_tagName = "Invocable";
self->enumValues[44].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[44].m_type = nullptr;

/* EnumConstant 46 */
self->enumValues[45].m_index = 45;
self->enumValues[45].m_value = 56;
self->enumValues[45].m_name = "ShaderModule";
self->enumValues[45].m_tagName = "ShaderModule";
self->enumValues[45].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[45].m_type = nullptr;

/* EnumConstant 47 */
self->enumValues[46].m_index = 46;
self->enumValues[46].m_value = 22;
self->enumValues[46].m_name = "_ModeOffset";
self->enumValues[46].m_tagName = "_ModeOffset";
self->enumValues[46].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[46].m_type = nullptr;

/* EnumConstant 48 */
self->enumValues[47].m_index = 47;
self->enumValues[47].m_value = 62914560;
self->enumValues[47].m_name = "_ModeMask";
self->enumValues[47].m_tagName = "_ModeMask";
self->enumValues[47].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[47].m_type = nullptr;

/* EnumConstant 49 */
self->enumValues[48].m_index = 48;
self->enumValues[48].m_value = 4194304;
self->enumValues[48].m_name = "EnableDebugTrace";
self->enumValues[48].m_tagName = "EnableDebugTrace";
self->enumValues[48].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[48].m_type = nullptr;

/* EnumConstant 50 */
self->enumValues[49].m_index = 49;
self->enumValues[49].m_value = 26;
self->enumValues[49].m_name = "_FlagsOffset";
self->enumValues[49].m_tagName = "_FlagsOffset";
self->enumValues[49].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[49].m_type = nullptr;

/* EnumConstant 51 */
self->enumValues[50].m_index = 50;
self->enumValues[50].m_value = 1006632960;
self->enumValues[50].m_name = "_FlagsMask";
self->enumValues[50].m_tagName = "_FlagsMask";
self->enumValues[50].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[50].m_type = nullptr;

/* EnumConstant 52 */
self->enumValues[51].m_index = 51;
self->enumValues[51].m_value = 67108864;
self->enumValues[51].m_name = "HasInputAttachment";
self->enumValues[51].m_tagName = "HasInputAttachment";
self->enumValues[51].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[51].m_type = nullptr;

/* EnumConstant 53 */
self->enumValues[52].m_index = 52;
self->enumValues[52].m_value = 0;
self->enumValues[52].m_name = "Unknown";
self->enumValues[52].m_tagName = "Unknown";
self->enumValues[52].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[52].m_type = nullptr;

/* EnumConstant 54 */
self->enumValues[53].m_index = 53;
self->enumValues[53].m_value = 255;
self->enumValues[53].m_name = "_StorageFormatMask";
self->enumValues[53].m_tagName = "_StorageFormatMask";
self->enumValues[53].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[53].m_type = nullptr;

/* EnumConstant 55 */
self->enumValues[54].m_index = 54;
self->enumValues[54].m_value = 3932415;
self->enumValues[54].m_name = "_ApiStorageFormatMask";
self->enumValues[54].m_tagName = "_ApiStorageFormatMask";
self->enumValues[54].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[54].m_type = nullptr;

/* EnumConstant 56 */
self->enumValues[55].m_index = 55;
self->enumValues[55].m_value = 4194048;
self->enumValues[55].m_name = "_ApiVersionMask";
self->enumValues[55].m_tagName = "_ApiVersionMask";
self->enumValues[55].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[55].m_type = nullptr;

/* EnumConstant 57 */
self->enumValues[56].m_index = 56;
self->enumValues[56].m_value = 1069809408;
self->enumValues[56].m_name = "_VersionModeFlagsMask";
self->enumValues[56].m_tagName = "_VersionModeFlagsMask";
self->enumValues[56].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[56].m_type = nullptr;

/* EnumConstant 58 */
self->enumValues[57].m_index = 57;
self->enumValues[57].m_value = 374801;
self->enumValues[57].m_name = "GLSL_440";
self->enumValues[57].m_tagName = "GLSL_440";
self->enumValues[57].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[57].m_type = nullptr;

/* EnumConstant 59 */
self->enumValues[58].m_index = 58;
self->enumValues[58].m_value = 377361;
self->enumValues[58].m_name = "GLSL_450";
self->enumValues[58].m_tagName = "GLSL_450";
self->enumValues[58].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[58].m_type = nullptr;

/* EnumConstant 60 */
self->enumValues[59].m_index = 59;
self->enumValues[59].m_value = 379921;
self->enumValues[59].m_name = "GLSL_460";
self->enumValues[59].m_tagName = "GLSL_460";
self->enumValues[59].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[59].m_type = nullptr;

/* EnumConstant 61 */
self->enumValues[60].m_index = 60;
self->enumValues[60].m_value = 1336337;
self->enumValues[60].m_name = "VKSL_100";
self->enumValues[60].m_tagName = "VKSL_100";
self->enumValues[60].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[60].m_type = nullptr;

/* EnumConstant 62 */
self->enumValues[61].m_index = 61;
self->enumValues[61].m_value = 1338897;
self->enumValues[61].m_name = "VKSL_110";
self->enumValues[61].m_tagName = "VKSL_110";
self->enumValues[61].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[61].m_type = nullptr;

/* EnumConstant 63 */
self->enumValues[62].m_index = 62;
self->enumValues[62].m_value = 1336354;
self->enumValues[62].m_name = "SPIRV_100";
self->enumValues[62].m_tagName = "SPIRV_100";
self->enumValues[62].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[62].m_type = nullptr;

/* EnumConstant 64 */
self->enumValues[63].m_index = 63;
self->enumValues[63].m_value = 1338914;
self->enumValues[63].m_name = "SPIRV_110";
self->enumValues[63].m_tagName = "SPIRV_110";
self->enumValues[63].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[63].m_type = nullptr;

/* EnumConstant 65 */
self->enumValues[64].m_index = 64;
self->enumValues[64].m_value = 1336376;
self->enumValues[64].m_name = "VkShader_100";
self->enumValues[64].m_tagName = "VkShader_100";
self->enumValues[64].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[64].m_type = nullptr;

/* EnumConstant 66 */
self->enumValues[65].m_index = 65;
self->enumValues[65].m_value = 1338936;
self->enumValues[65].m_name = "VkShader_110";
self->enumValues[65].m_tagName = "VkShader_110";
self->enumValues[65].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[65].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EShaderLangFormat),
Hash("loo::vkfg::EShaderLangFormat"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EShaderLangFormat",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EShaderLangFormat>) noexcept
{
return LooGetEnum<loo::vkfg::EShaderLangFormat>();
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

template<> struct IsSerializable<loo::vkfg::EShaderDebugMode> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EShaderDebugMode>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EShaderDebugMode, 6> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "None";
self->enumValues[0].m_tagName = "None";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Trace";
self->enumValues[1].m_tagName = "Trace";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Asserts";
self->enumValues[2].m_tagName = "Asserts";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "View";
self->enumValues[3].m_tagName = "View";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "InstructionCounter";
self->enumValues[4].m_tagName = "InstructionCounter";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 0;
self->enumValues[5].m_name = "Unknown";
self->enumValues[5].m_tagName = "Unknown";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EShaderDebugMode),
Hash("loo::vkfg::EShaderDebugMode"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EShaderDebugMode",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EShaderDebugMode>) noexcept
{
return LooGetEnum<loo::vkfg::EShaderDebugMode>();
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

template<> struct IsSerializable<loo::vkfg::EVertexType> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EVertexType>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EVertexType, 99> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "_VecOffset";
self->enumValues[0].m_tagName = "_VecOffset";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "_Vec1";
self->enumValues[1].m_tagName = "_Vec1";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "_Vec2";
self->enumValues[2].m_tagName = "_Vec2";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "_Vec3";
self->enumValues[3].m_tagName = "_Vec3";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "_Vec4";
self->enumValues[4].m_tagName = "_Vec4";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 15;
self->enumValues[5].m_name = "_VecMask";
self->enumValues[5].m_tagName = "_VecMask";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 8;
self->enumValues[6].m_name = "_TypeOffset";
self->enumValues[6].m_tagName = "_TypeOffset";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 256;
self->enumValues[7].m_name = "_Byte";
self->enumValues[7].m_tagName = "_Byte";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 512;
self->enumValues[8].m_name = "_UByte";
self->enumValues[8].m_tagName = "_UByte";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 768;
self->enumValues[9].m_name = "_Short";
self->enumValues[9].m_tagName = "_Short";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 1024;
self->enumValues[10].m_name = "_UShort";
self->enumValues[10].m_tagName = "_UShort";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 1280;
self->enumValues[11].m_name = "_Int";
self->enumValues[11].m_tagName = "_Int";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 1536;
self->enumValues[12].m_name = "_UInt";
self->enumValues[12].m_tagName = "_UInt";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 1792;
self->enumValues[13].m_name = "_Long";
self->enumValues[13].m_tagName = "_Long";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 2048;
self->enumValues[14].m_name = "_ULong";
self->enumValues[14].m_tagName = "_ULong";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 2304;
self->enumValues[15].m_name = "_Half";
self->enumValues[15].m_tagName = "_Half";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;

/* EnumConstant 17 */
self->enumValues[16].m_index = 16;
self->enumValues[16].m_value = 2560;
self->enumValues[16].m_name = "_Float";
self->enumValues[16].m_tagName = "_Float";
self->enumValues[16].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[16].m_type = nullptr;

/* EnumConstant 18 */
self->enumValues[17].m_index = 17;
self->enumValues[17].m_value = 2816;
self->enumValues[17].m_name = "_Double";
self->enumValues[17].m_tagName = "_Double";
self->enumValues[17].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[17].m_type = nullptr;

/* EnumConstant 19 */
self->enumValues[18].m_index = 18;
self->enumValues[18].m_value = 3840;
self->enumValues[18].m_name = "_TypeMask";
self->enumValues[18].m_tagName = "_TypeMask";
self->enumValues[18].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[18].m_type = nullptr;

/* EnumConstant 20 */
self->enumValues[19].m_index = 19;
self->enumValues[19].m_value = 16;
self->enumValues[19].m_name = "_FlagsOffset";
self->enumValues[19].m_tagName = "_FlagsOffset";
self->enumValues[19].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[19].m_type = nullptr;

/* EnumConstant 21 */
self->enumValues[20].m_index = 20;
self->enumValues[20].m_value = 65536;
self->enumValues[20].m_name = "NormalizedFlag";
self->enumValues[20].m_tagName = "NormalizedFlag";
self->enumValues[20].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[20].m_type = nullptr;

/* EnumConstant 22 */
self->enumValues[21].m_index = 21;
self->enumValues[21].m_value = 131072;
self->enumValues[21].m_name = "ScaledFlag";
self->enumValues[21].m_tagName = "ScaledFlag";
self->enumValues[21].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[21].m_type = nullptr;

/* EnumConstant 23 */
self->enumValues[22].m_index = 22;
self->enumValues[22].m_value = 257;
self->enumValues[22].m_name = "Byte";
self->enumValues[22].m_tagName = "Byte";
self->enumValues[22].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[22].m_type = nullptr;

/* EnumConstant 24 */
self->enumValues[23].m_index = 23;
self->enumValues[23].m_value = 258;
self->enumValues[23].m_name = "Byte2";
self->enumValues[23].m_tagName = "Byte2";
self->enumValues[23].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[23].m_type = nullptr;

/* EnumConstant 25 */
self->enumValues[24].m_index = 24;
self->enumValues[24].m_value = 259;
self->enumValues[24].m_name = "Byte3";
self->enumValues[24].m_tagName = "Byte3";
self->enumValues[24].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[24].m_type = nullptr;

/* EnumConstant 26 */
self->enumValues[25].m_index = 25;
self->enumValues[25].m_value = 260;
self->enumValues[25].m_name = "Byte4";
self->enumValues[25].m_tagName = "Byte4";
self->enumValues[25].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[25].m_type = nullptr;

/* EnumConstant 27 */
self->enumValues[26].m_index = 26;
self->enumValues[26].m_value = 65793;
self->enumValues[26].m_name = "Byte_Norm";
self->enumValues[26].m_tagName = "Byte_Norm";
self->enumValues[26].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[26].m_type = nullptr;

/* EnumConstant 28 */
self->enumValues[27].m_index = 27;
self->enumValues[27].m_value = 65794;
self->enumValues[27].m_name = "Byte2_Norm";
self->enumValues[27].m_tagName = "Byte2_Norm";
self->enumValues[27].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[27].m_type = nullptr;

/* EnumConstant 29 */
self->enumValues[28].m_index = 28;
self->enumValues[28].m_value = 65795;
self->enumValues[28].m_name = "Byte3_Norm";
self->enumValues[28].m_tagName = "Byte3_Norm";
self->enumValues[28].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[28].m_type = nullptr;

/* EnumConstant 30 */
self->enumValues[29].m_index = 29;
self->enumValues[29].m_value = 65796;
self->enumValues[29].m_name = "Byte4_Norm";
self->enumValues[29].m_tagName = "Byte4_Norm";
self->enumValues[29].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[29].m_type = nullptr;

/* EnumConstant 31 */
self->enumValues[30].m_index = 30;
self->enumValues[30].m_value = 131329;
self->enumValues[30].m_name = "Byte_Scaled";
self->enumValues[30].m_tagName = "Byte_Scaled";
self->enumValues[30].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[30].m_type = nullptr;

/* EnumConstant 32 */
self->enumValues[31].m_index = 31;
self->enumValues[31].m_value = 131330;
self->enumValues[31].m_name = "Byte2_Scaled";
self->enumValues[31].m_tagName = "Byte2_Scaled";
self->enumValues[31].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[31].m_type = nullptr;

/* EnumConstant 33 */
self->enumValues[32].m_index = 32;
self->enumValues[32].m_value = 131331;
self->enumValues[32].m_name = "Byte3_Scaled";
self->enumValues[32].m_tagName = "Byte3_Scaled";
self->enumValues[32].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[32].m_type = nullptr;

/* EnumConstant 34 */
self->enumValues[33].m_index = 33;
self->enumValues[33].m_value = 131332;
self->enumValues[33].m_name = "Byte4_Scaled";
self->enumValues[33].m_tagName = "Byte4_Scaled";
self->enumValues[33].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[33].m_type = nullptr;

/* EnumConstant 35 */
self->enumValues[34].m_index = 34;
self->enumValues[34].m_value = 513;
self->enumValues[34].m_name = "UByte";
self->enumValues[34].m_tagName = "UByte";
self->enumValues[34].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[34].m_type = nullptr;

/* EnumConstant 36 */
self->enumValues[35].m_index = 35;
self->enumValues[35].m_value = 514;
self->enumValues[35].m_name = "UByte2";
self->enumValues[35].m_tagName = "UByte2";
self->enumValues[35].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[35].m_type = nullptr;

/* EnumConstant 37 */
self->enumValues[36].m_index = 36;
self->enumValues[36].m_value = 515;
self->enumValues[36].m_name = "UByte3";
self->enumValues[36].m_tagName = "UByte3";
self->enumValues[36].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[36].m_type = nullptr;

/* EnumConstant 38 */
self->enumValues[37].m_index = 37;
self->enumValues[37].m_value = 516;
self->enumValues[37].m_name = "UByte4";
self->enumValues[37].m_tagName = "UByte4";
self->enumValues[37].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[37].m_type = nullptr;

/* EnumConstant 39 */
self->enumValues[38].m_index = 38;
self->enumValues[38].m_value = 66049;
self->enumValues[38].m_name = "UByte_Norm";
self->enumValues[38].m_tagName = "UByte_Norm";
self->enumValues[38].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[38].m_type = nullptr;

/* EnumConstant 40 */
self->enumValues[39].m_index = 39;
self->enumValues[39].m_value = 66050;
self->enumValues[39].m_name = "UByte2_Norm";
self->enumValues[39].m_tagName = "UByte2_Norm";
self->enumValues[39].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[39].m_type = nullptr;

/* EnumConstant 41 */
self->enumValues[40].m_index = 40;
self->enumValues[40].m_value = 66051;
self->enumValues[40].m_name = "UByte3_Norm";
self->enumValues[40].m_tagName = "UByte3_Norm";
self->enumValues[40].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[40].m_type = nullptr;

/* EnumConstant 42 */
self->enumValues[41].m_index = 41;
self->enumValues[41].m_value = 66052;
self->enumValues[41].m_name = "UByte4_Norm";
self->enumValues[41].m_tagName = "UByte4_Norm";
self->enumValues[41].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[41].m_type = nullptr;

/* EnumConstant 43 */
self->enumValues[42].m_index = 42;
self->enumValues[42].m_value = 131585;
self->enumValues[42].m_name = "UByte_Scaled";
self->enumValues[42].m_tagName = "UByte_Scaled";
self->enumValues[42].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[42].m_type = nullptr;

/* EnumConstant 44 */
self->enumValues[43].m_index = 43;
self->enumValues[43].m_value = 131586;
self->enumValues[43].m_name = "UByte2_Scaled";
self->enumValues[43].m_tagName = "UByte2_Scaled";
self->enumValues[43].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[43].m_type = nullptr;

/* EnumConstant 45 */
self->enumValues[44].m_index = 44;
self->enumValues[44].m_value = 131587;
self->enumValues[44].m_name = "UByte3_Scaled";
self->enumValues[44].m_tagName = "UByte3_Scaled";
self->enumValues[44].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[44].m_type = nullptr;

/* EnumConstant 46 */
self->enumValues[45].m_index = 45;
self->enumValues[45].m_value = 131588;
self->enumValues[45].m_name = "UByte4_Scaled";
self->enumValues[45].m_tagName = "UByte4_Scaled";
self->enumValues[45].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[45].m_type = nullptr;

/* EnumConstant 47 */
self->enumValues[46].m_index = 46;
self->enumValues[46].m_value = 769;
self->enumValues[46].m_name = "Short";
self->enumValues[46].m_tagName = "Short";
self->enumValues[46].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[46].m_type = nullptr;

/* EnumConstant 48 */
self->enumValues[47].m_index = 47;
self->enumValues[47].m_value = 770;
self->enumValues[47].m_name = "Short2";
self->enumValues[47].m_tagName = "Short2";
self->enumValues[47].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[47].m_type = nullptr;

/* EnumConstant 49 */
self->enumValues[48].m_index = 48;
self->enumValues[48].m_value = 771;
self->enumValues[48].m_name = "Short3";
self->enumValues[48].m_tagName = "Short3";
self->enumValues[48].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[48].m_type = nullptr;

/* EnumConstant 50 */
self->enumValues[49].m_index = 49;
self->enumValues[49].m_value = 772;
self->enumValues[49].m_name = "Short4";
self->enumValues[49].m_tagName = "Short4";
self->enumValues[49].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[49].m_type = nullptr;

/* EnumConstant 51 */
self->enumValues[50].m_index = 50;
self->enumValues[50].m_value = 66305;
self->enumValues[50].m_name = "Short_Norm";
self->enumValues[50].m_tagName = "Short_Norm";
self->enumValues[50].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[50].m_type = nullptr;

/* EnumConstant 52 */
self->enumValues[51].m_index = 51;
self->enumValues[51].m_value = 66306;
self->enumValues[51].m_name = "Short2_Norm";
self->enumValues[51].m_tagName = "Short2_Norm";
self->enumValues[51].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[51].m_type = nullptr;

/* EnumConstant 53 */
self->enumValues[52].m_index = 52;
self->enumValues[52].m_value = 66307;
self->enumValues[52].m_name = "Short3_Norm";
self->enumValues[52].m_tagName = "Short3_Norm";
self->enumValues[52].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[52].m_type = nullptr;

/* EnumConstant 54 */
self->enumValues[53].m_index = 53;
self->enumValues[53].m_value = 66308;
self->enumValues[53].m_name = "Short4_Norm";
self->enumValues[53].m_tagName = "Short4_Norm";
self->enumValues[53].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[53].m_type = nullptr;

/* EnumConstant 55 */
self->enumValues[54].m_index = 54;
self->enumValues[54].m_value = 131841;
self->enumValues[54].m_name = "Short_Scaled";
self->enumValues[54].m_tagName = "Short_Scaled";
self->enumValues[54].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[54].m_type = nullptr;

/* EnumConstant 56 */
self->enumValues[55].m_index = 55;
self->enumValues[55].m_value = 131842;
self->enumValues[55].m_name = "Short2_Scaled";
self->enumValues[55].m_tagName = "Short2_Scaled";
self->enumValues[55].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[55].m_type = nullptr;

/* EnumConstant 57 */
self->enumValues[56].m_index = 56;
self->enumValues[56].m_value = 131843;
self->enumValues[56].m_name = "Short3_Scaled";
self->enumValues[56].m_tagName = "Short3_Scaled";
self->enumValues[56].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[56].m_type = nullptr;

/* EnumConstant 58 */
self->enumValues[57].m_index = 57;
self->enumValues[57].m_value = 131844;
self->enumValues[57].m_name = "Short4_Scaled";
self->enumValues[57].m_tagName = "Short4_Scaled";
self->enumValues[57].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[57].m_type = nullptr;

/* EnumConstant 59 */
self->enumValues[58].m_index = 58;
self->enumValues[58].m_value = 1025;
self->enumValues[58].m_name = "UShort";
self->enumValues[58].m_tagName = "UShort";
self->enumValues[58].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[58].m_type = nullptr;

/* EnumConstant 60 */
self->enumValues[59].m_index = 59;
self->enumValues[59].m_value = 1026;
self->enumValues[59].m_name = "UShort2";
self->enumValues[59].m_tagName = "UShort2";
self->enumValues[59].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[59].m_type = nullptr;

/* EnumConstant 61 */
self->enumValues[60].m_index = 60;
self->enumValues[60].m_value = 1027;
self->enumValues[60].m_name = "UShort3";
self->enumValues[60].m_tagName = "UShort3";
self->enumValues[60].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[60].m_type = nullptr;

/* EnumConstant 62 */
self->enumValues[61].m_index = 61;
self->enumValues[61].m_value = 1028;
self->enumValues[61].m_name = "UShort4";
self->enumValues[61].m_tagName = "UShort4";
self->enumValues[61].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[61].m_type = nullptr;

/* EnumConstant 63 */
self->enumValues[62].m_index = 62;
self->enumValues[62].m_value = 66561;
self->enumValues[62].m_name = "UShort_Norm";
self->enumValues[62].m_tagName = "UShort_Norm";
self->enumValues[62].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[62].m_type = nullptr;

/* EnumConstant 64 */
self->enumValues[63].m_index = 63;
self->enumValues[63].m_value = 66562;
self->enumValues[63].m_name = "UShort2_Norm";
self->enumValues[63].m_tagName = "UShort2_Norm";
self->enumValues[63].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[63].m_type = nullptr;

/* EnumConstant 65 */
self->enumValues[64].m_index = 64;
self->enumValues[64].m_value = 66563;
self->enumValues[64].m_name = "UShort3_Norm";
self->enumValues[64].m_tagName = "UShort3_Norm";
self->enumValues[64].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[64].m_type = nullptr;

/* EnumConstant 66 */
self->enumValues[65].m_index = 65;
self->enumValues[65].m_value = 66564;
self->enumValues[65].m_name = "UShort4_Norm";
self->enumValues[65].m_tagName = "UShort4_Norm";
self->enumValues[65].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[65].m_type = nullptr;

/* EnumConstant 67 */
self->enumValues[66].m_index = 66;
self->enumValues[66].m_value = 132097;
self->enumValues[66].m_name = "UShort_Scaled";
self->enumValues[66].m_tagName = "UShort_Scaled";
self->enumValues[66].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[66].m_type = nullptr;

/* EnumConstant 68 */
self->enumValues[67].m_index = 67;
self->enumValues[67].m_value = 132098;
self->enumValues[67].m_name = "UShort2_Scaled";
self->enumValues[67].m_tagName = "UShort2_Scaled";
self->enumValues[67].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[67].m_type = nullptr;

/* EnumConstant 69 */
self->enumValues[68].m_index = 68;
self->enumValues[68].m_value = 132099;
self->enumValues[68].m_name = "UShort3_Scaled";
self->enumValues[68].m_tagName = "UShort3_Scaled";
self->enumValues[68].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[68].m_type = nullptr;

/* EnumConstant 70 */
self->enumValues[69].m_index = 69;
self->enumValues[69].m_value = 132100;
self->enumValues[69].m_name = "UShort4_Scaled";
self->enumValues[69].m_tagName = "UShort4_Scaled";
self->enumValues[69].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[69].m_type = nullptr;

/* EnumConstant 71 */
self->enumValues[70].m_index = 70;
self->enumValues[70].m_value = 1281;
self->enumValues[70].m_name = "Int";
self->enumValues[70].m_tagName = "Int";
self->enumValues[70].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[70].m_type = nullptr;

/* EnumConstant 72 */
self->enumValues[71].m_index = 71;
self->enumValues[71].m_value = 1282;
self->enumValues[71].m_name = "Int2";
self->enumValues[71].m_tagName = "Int2";
self->enumValues[71].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[71].m_type = nullptr;

/* EnumConstant 73 */
self->enumValues[72].m_index = 72;
self->enumValues[72].m_value = 1283;
self->enumValues[72].m_name = "Int3";
self->enumValues[72].m_tagName = "Int3";
self->enumValues[72].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[72].m_type = nullptr;

/* EnumConstant 74 */
self->enumValues[73].m_index = 73;
self->enumValues[73].m_value = 1284;
self->enumValues[73].m_name = "Int4";
self->enumValues[73].m_tagName = "Int4";
self->enumValues[73].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[73].m_type = nullptr;

/* EnumConstant 75 */
self->enumValues[74].m_index = 74;
self->enumValues[74].m_value = 1537;
self->enumValues[74].m_name = "UInt";
self->enumValues[74].m_tagName = "UInt";
self->enumValues[74].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[74].m_type = nullptr;

/* EnumConstant 76 */
self->enumValues[75].m_index = 75;
self->enumValues[75].m_value = 1538;
self->enumValues[75].m_name = "UInt2";
self->enumValues[75].m_tagName = "UInt2";
self->enumValues[75].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[75].m_type = nullptr;

/* EnumConstant 77 */
self->enumValues[76].m_index = 76;
self->enumValues[76].m_value = 1539;
self->enumValues[76].m_name = "UInt3";
self->enumValues[76].m_tagName = "UInt3";
self->enumValues[76].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[76].m_type = nullptr;

/* EnumConstant 78 */
self->enumValues[77].m_index = 77;
self->enumValues[77].m_value = 1540;
self->enumValues[77].m_name = "UInt4";
self->enumValues[77].m_tagName = "UInt4";
self->enumValues[77].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[77].m_type = nullptr;

/* EnumConstant 79 */
self->enumValues[78].m_index = 78;
self->enumValues[78].m_value = 1793;
self->enumValues[78].m_name = "Long";
self->enumValues[78].m_tagName = "Long";
self->enumValues[78].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[78].m_type = nullptr;

/* EnumConstant 80 */
self->enumValues[79].m_index = 79;
self->enumValues[79].m_value = 1794;
self->enumValues[79].m_name = "Long2";
self->enumValues[79].m_tagName = "Long2";
self->enumValues[79].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[79].m_type = nullptr;

/* EnumConstant 81 */
self->enumValues[80].m_index = 80;
self->enumValues[80].m_value = 1795;
self->enumValues[80].m_name = "Long3";
self->enumValues[80].m_tagName = "Long3";
self->enumValues[80].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[80].m_type = nullptr;

/* EnumConstant 82 */
self->enumValues[81].m_index = 81;
self->enumValues[81].m_value = 1796;
self->enumValues[81].m_name = "Long4";
self->enumValues[81].m_tagName = "Long4";
self->enumValues[81].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[81].m_type = nullptr;

/* EnumConstant 83 */
self->enumValues[82].m_index = 82;
self->enumValues[82].m_value = 2049;
self->enumValues[82].m_name = "ULong";
self->enumValues[82].m_tagName = "ULong";
self->enumValues[82].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[82].m_type = nullptr;

/* EnumConstant 84 */
self->enumValues[83].m_index = 83;
self->enumValues[83].m_value = 2050;
self->enumValues[83].m_name = "ULong2";
self->enumValues[83].m_tagName = "ULong2";
self->enumValues[83].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[83].m_type = nullptr;

/* EnumConstant 85 */
self->enumValues[84].m_index = 84;
self->enumValues[84].m_value = 2051;
self->enumValues[84].m_name = "ULong3";
self->enumValues[84].m_tagName = "ULong3";
self->enumValues[84].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[84].m_type = nullptr;

/* EnumConstant 86 */
self->enumValues[85].m_index = 85;
self->enumValues[85].m_value = 2052;
self->enumValues[85].m_name = "ULong4";
self->enumValues[85].m_tagName = "ULong4";
self->enumValues[85].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[85].m_type = nullptr;

/* EnumConstant 87 */
self->enumValues[86].m_index = 86;
self->enumValues[86].m_value = 2305;
self->enumValues[86].m_name = "Half";
self->enumValues[86].m_tagName = "Half";
self->enumValues[86].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[86].m_type = nullptr;

/* EnumConstant 88 */
self->enumValues[87].m_index = 87;
self->enumValues[87].m_value = 2306;
self->enumValues[87].m_name = "Half2";
self->enumValues[87].m_tagName = "Half2";
self->enumValues[87].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[87].m_type = nullptr;

/* EnumConstant 89 */
self->enumValues[88].m_index = 88;
self->enumValues[88].m_value = 2307;
self->enumValues[88].m_name = "Half3";
self->enumValues[88].m_tagName = "Half3";
self->enumValues[88].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[88].m_type = nullptr;

/* EnumConstant 90 */
self->enumValues[89].m_index = 89;
self->enumValues[89].m_value = 2308;
self->enumValues[89].m_name = "Half4";
self->enumValues[89].m_tagName = "Half4";
self->enumValues[89].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[89].m_type = nullptr;

/* EnumConstant 91 */
self->enumValues[90].m_index = 90;
self->enumValues[90].m_value = 2561;
self->enumValues[90].m_name = "Float";
self->enumValues[90].m_tagName = "Float";
self->enumValues[90].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[90].m_type = nullptr;

/* EnumConstant 92 */
self->enumValues[91].m_index = 91;
self->enumValues[91].m_value = 2562;
self->enumValues[91].m_name = "Float2";
self->enumValues[91].m_tagName = "Float2";
self->enumValues[91].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[91].m_type = nullptr;

/* EnumConstant 93 */
self->enumValues[92].m_index = 92;
self->enumValues[92].m_value = 2563;
self->enumValues[92].m_name = "Float3";
self->enumValues[92].m_tagName = "Float3";
self->enumValues[92].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[92].m_type = nullptr;

/* EnumConstant 94 */
self->enumValues[93].m_index = 93;
self->enumValues[93].m_value = 2564;
self->enumValues[93].m_name = "Float4";
self->enumValues[93].m_tagName = "Float4";
self->enumValues[93].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[93].m_type = nullptr;

/* EnumConstant 95 */
self->enumValues[94].m_index = 94;
self->enumValues[94].m_value = 2817;
self->enumValues[94].m_name = "Double";
self->enumValues[94].m_tagName = "Double";
self->enumValues[94].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[94].m_type = nullptr;

/* EnumConstant 96 */
self->enumValues[95].m_index = 95;
self->enumValues[95].m_value = 2818;
self->enumValues[95].m_name = "Double2";
self->enumValues[95].m_tagName = "Double2";
self->enumValues[95].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[95].m_type = nullptr;

/* EnumConstant 97 */
self->enumValues[96].m_index = 96;
self->enumValues[96].m_value = 2819;
self->enumValues[96].m_name = "Double3";
self->enumValues[96].m_tagName = "Double3";
self->enumValues[96].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[96].m_type = nullptr;

/* EnumConstant 98 */
self->enumValues[97].m_index = 97;
self->enumValues[97].m_value = 2820;
self->enumValues[97].m_name = "Double4";
self->enumValues[97].m_tagName = "Double4";
self->enumValues[97].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[97].m_type = nullptr;

/* EnumConstant 99 */
self->enumValues[98].m_index = 98;
self->enumValues[98].m_value = 0;
self->enumValues[98].m_name = "Unknown";
self->enumValues[98].m_tagName = "Unknown";
self->enumValues[98].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[98].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EVertexType),
Hash("loo::vkfg::EVertexType"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EVertexType",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EVertexType>) noexcept
{
return LooGetEnum<loo::vkfg::EVertexType>();
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

template<> struct IsSerializable<loo::vkfg::EVertexInputRate> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EVertexInputRate>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EVertexInputRate, 3> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Vertex";
self->enumValues[0].m_tagName = "Vertex";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Instance";
self->enumValues[1].m_tagName = "Instance";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4294967295;
self->enumValues[2].m_name = "Unknown";
self->enumValues[2].m_tagName = "Unknown";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EVertexInputRate),
Hash("loo::vkfg::EVertexInputRate"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EVertexInputRate",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EVertexInputRate>) noexcept
{
return LooGetEnum<loo::vkfg::EVertexInputRate>();
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

template<> struct IsSerializable<loo::vkfg::EIndex> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EIndex>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EIndex, 3> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "UShort";
self->enumValues[0].m_tagName = "UShort";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "UInt";
self->enumValues[1].m_tagName = "UInt";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4294967295;
self->enumValues[2].m_name = "Unknown";
self->enumValues[2].m_tagName = "Unknown";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EIndex),
Hash("loo::vkfg::EIndex"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EIndex",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EIndex>) noexcept
{
return LooGetEnum<loo::vkfg::EIndex>();
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

template<> struct IsSerializable<loo::vkfg::EBlendFactor> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EBlendFactor>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EBlendFactor, 20> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Zero";
self->enumValues[0].m_tagName = "Zero";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "One";
self->enumValues[1].m_tagName = "One";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "SrcColor";
self->enumValues[2].m_tagName = "SrcColor";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "OneMinusSrcColor";
self->enumValues[3].m_tagName = "OneMinusSrcColor";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "DstColor";
self->enumValues[4].m_tagName = "DstColor";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "OneMinusDstColor";
self->enumValues[5].m_tagName = "OneMinusDstColor";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "SrcAlpha";
self->enumValues[6].m_tagName = "SrcAlpha";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "OneMinusSrcAlpha";
self->enumValues[7].m_tagName = "OneMinusSrcAlpha";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 8;
self->enumValues[8].m_name = "DstAlpha";
self->enumValues[8].m_tagName = "DstAlpha";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 9;
self->enumValues[9].m_name = "OneMinusDstAlpha";
self->enumValues[9].m_tagName = "OneMinusDstAlpha";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 10;
self->enumValues[10].m_name = "ConstColor";
self->enumValues[10].m_tagName = "ConstColor";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 11;
self->enumValues[11].m_name = "OneMinusConstColor";
self->enumValues[11].m_tagName = "OneMinusConstColor";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 12;
self->enumValues[12].m_name = "ConstAlpha";
self->enumValues[12].m_tagName = "ConstAlpha";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 13;
self->enumValues[13].m_name = "OneMinusConstAlpha";
self->enumValues[13].m_tagName = "OneMinusConstAlpha";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 14;
self->enumValues[14].m_name = "SrcAlphaSaturate";
self->enumValues[14].m_tagName = "SrcAlphaSaturate";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 15;
self->enumValues[15].m_name = "Src1Color";
self->enumValues[15].m_tagName = "Src1Color";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;

/* EnumConstant 17 */
self->enumValues[16].m_index = 16;
self->enumValues[16].m_value = 16;
self->enumValues[16].m_name = "OneMinusSrc1Color";
self->enumValues[16].m_tagName = "OneMinusSrc1Color";
self->enumValues[16].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[16].m_type = nullptr;

/* EnumConstant 18 */
self->enumValues[17].m_index = 17;
self->enumValues[17].m_value = 17;
self->enumValues[17].m_name = "Src1Alpha";
self->enumValues[17].m_tagName = "Src1Alpha";
self->enumValues[17].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[17].m_type = nullptr;

/* EnumConstant 19 */
self->enumValues[18].m_index = 18;
self->enumValues[18].m_value = 18;
self->enumValues[18].m_name = "OneMinusSrc1Alpha";
self->enumValues[18].m_tagName = "OneMinusSrc1Alpha";
self->enumValues[18].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[18].m_type = nullptr;

/* EnumConstant 20 */
self->enumValues[19].m_index = 19;
self->enumValues[19].m_value = 4294967295;
self->enumValues[19].m_name = "Unknown";
self->enumValues[19].m_tagName = "Unknown";
self->enumValues[19].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[19].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EBlendFactor),
Hash("loo::vkfg::EBlendFactor"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EBlendFactor",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EBlendFactor>) noexcept
{
return LooGetEnum<loo::vkfg::EBlendFactor>();
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

template<> struct IsSerializable<loo::vkfg::EBlendOp> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EBlendOp>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EBlendOp, 6> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Add";
self->enumValues[0].m_tagName = "Add";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Sub";
self->enumValues[1].m_tagName = "Sub";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "RevSub";
self->enumValues[2].m_tagName = "RevSub";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "Min";
self->enumValues[3].m_tagName = "Min";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "Max";
self->enumValues[4].m_tagName = "Max";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 4294967295;
self->enumValues[5].m_name = "Unknown";
self->enumValues[5].m_tagName = "Unknown";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EBlendOp),
Hash("loo::vkfg::EBlendOp"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EBlendOp",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EBlendOp>) noexcept
{
return LooGetEnum<loo::vkfg::EBlendOp>();
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

template<> struct IsSerializable<loo::vkfg::ELogicOp> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::ELogicOp>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::ELogicOp, 18> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "None";
self->enumValues[0].m_tagName = "None";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Clear";
self->enumValues[1].m_tagName = "Clear";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Set";
self->enumValues[2].m_tagName = "Set";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "Copy";
self->enumValues[3].m_tagName = "Copy";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "CopyInverted";
self->enumValues[4].m_tagName = "CopyInverted";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "NoOp";
self->enumValues[5].m_tagName = "NoOp";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "Invert";
self->enumValues[6].m_tagName = "Invert";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "And";
self->enumValues[7].m_tagName = "And";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 8;
self->enumValues[8].m_name = "NotAnd";
self->enumValues[8].m_tagName = "NotAnd";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 9;
self->enumValues[9].m_name = "Or";
self->enumValues[9].m_tagName = "Or";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 10;
self->enumValues[10].m_name = "NotOr";
self->enumValues[10].m_tagName = "NotOr";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 11;
self->enumValues[11].m_name = "Xor";
self->enumValues[11].m_tagName = "Xor";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 12;
self->enumValues[12].m_name = "Equiv";
self->enumValues[12].m_tagName = "Equiv";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 13;
self->enumValues[13].m_name = "AndReverse";
self->enumValues[13].m_tagName = "AndReverse";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 14;
self->enumValues[14].m_name = "AndInverted";
self->enumValues[14].m_tagName = "AndInverted";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 15;
self->enumValues[15].m_name = "OrReverse";
self->enumValues[15].m_tagName = "OrReverse";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;

/* EnumConstant 17 */
self->enumValues[16].m_index = 16;
self->enumValues[16].m_value = 16;
self->enumValues[16].m_name = "OrInverted";
self->enumValues[16].m_tagName = "OrInverted";
self->enumValues[16].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[16].m_type = nullptr;

/* EnumConstant 18 */
self->enumValues[17].m_index = 17;
self->enumValues[17].m_value = 4294967295;
self->enumValues[17].m_name = "Unknown";
self->enumValues[17].m_tagName = "Unknown";
self->enumValues[17].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[17].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::ELogicOp),
Hash("loo::vkfg::ELogicOp"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::ELogicOp",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::ELogicOp>) noexcept
{
return LooGetEnum<loo::vkfg::ELogicOp>();
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

template<> struct IsSerializable<loo::vkfg::ECompareOp> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::ECompareOp>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::ECompareOp, 9> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Never";
self->enumValues[0].m_tagName = "Never";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Less";
self->enumValues[1].m_tagName = "Less";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Equal";
self->enumValues[2].m_tagName = "Equal";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "LEqual";
self->enumValues[3].m_tagName = "LEqual";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "Greater";
self->enumValues[4].m_tagName = "Greater";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "NotEqual";
self->enumValues[5].m_tagName = "NotEqual";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "GEqual";
self->enumValues[6].m_tagName = "GEqual";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "Always";
self->enumValues[7].m_tagName = "Always";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 255;
self->enumValues[8].m_name = "Unknown";
self->enumValues[8].m_tagName = "Unknown";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::ECompareOp),
Hash("loo::vkfg::ECompareOp"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::ECompareOp",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::ECompareOp>) noexcept
{
return LooGetEnum<loo::vkfg::ECompareOp>();
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

template<> struct IsSerializable<loo::vkfg::EStencilOp> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EStencilOp>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EStencilOp, 9> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Keep";
self->enumValues[0].m_tagName = "Keep";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Zero";
self->enumValues[1].m_tagName = "Zero";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Replace";
self->enumValues[2].m_tagName = "Replace";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "Incr";
self->enumValues[3].m_tagName = "Incr";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "IncrWrap";
self->enumValues[4].m_tagName = "IncrWrap";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "Decr";
self->enumValues[5].m_tagName = "Decr";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "DecrWrap";
self->enumValues[6].m_tagName = "DecrWrap";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "Invert";
self->enumValues[7].m_tagName = "Invert";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 255;
self->enumValues[8].m_name = "Unknown";
self->enumValues[8].m_tagName = "Unknown";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EStencilOp),
Hash("loo::vkfg::EStencilOp"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EStencilOp",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EStencilOp>) noexcept
{
return LooGetEnum<loo::vkfg::EStencilOp>();
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

template<> struct IsSerializable<loo::vkfg::EPolygonMode> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EPolygonMode>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EPolygonMode, 4> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Point";
self->enumValues[0].m_tagName = "Point";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Line";
self->enumValues[1].m_tagName = "Line";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Fill";
self->enumValues[2].m_tagName = "Fill";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 4294967295;
self->enumValues[3].m_name = "Unknown";
self->enumValues[3].m_tagName = "Unknown";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EPolygonMode),
Hash("loo::vkfg::EPolygonMode"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EPolygonMode",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EPolygonMode>) noexcept
{
return LooGetEnum<loo::vkfg::EPolygonMode>();
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

template<> struct IsSerializable<loo::vkfg::EPrimitive> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EPrimitive>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EPrimitive, 12> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Point";
self->enumValues[0].m_tagName = "Point";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "LineList";
self->enumValues[1].m_tagName = "LineList";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "LineStrip";
self->enumValues[2].m_tagName = "LineStrip";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "LineListAdjacency";
self->enumValues[3].m_tagName = "LineListAdjacency";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "LineStripAdjacency";
self->enumValues[4].m_tagName = "LineStripAdjacency";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "TriangleList";
self->enumValues[5].m_tagName = "TriangleList";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "TriangleStrip";
self->enumValues[6].m_tagName = "TriangleStrip";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "TriangleFan";
self->enumValues[7].m_tagName = "TriangleFan";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 8;
self->enumValues[8].m_name = "TriangleListAdjacency";
self->enumValues[8].m_tagName = "TriangleListAdjacency";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 9;
self->enumValues[9].m_name = "TriangleStripAdjacency";
self->enumValues[9].m_tagName = "TriangleStripAdjacency";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 10;
self->enumValues[10].m_name = "Patch";
self->enumValues[10].m_tagName = "Patch";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 4294967295;
self->enumValues[11].m_name = "Unknown";
self->enumValues[11].m_tagName = "Unknown";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EPrimitive),
Hash("loo::vkfg::EPrimitive"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EPrimitive",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EPrimitive>) noexcept
{
return LooGetEnum<loo::vkfg::EPrimitive>();
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

template<> struct IsSerializable<loo::vkfg::ECullMode> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::ECullMode>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::ECullMode, 5> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "None";
self->enumValues[0].m_tagName = "None";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Front";
self->enumValues[1].m_tagName = "Front";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Back";
self->enumValues[2].m_tagName = "Back";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "FontAndBack";
self->enumValues[3].m_tagName = "FontAndBack";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 0;
self->enumValues[4].m_name = "Unknown";
self->enumValues[4].m_tagName = "Unknown";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::ECullMode),
Hash("loo::vkfg::ECullMode"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::ECullMode",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::ECullMode>) noexcept
{
return LooGetEnum<loo::vkfg::ECullMode>();
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

template<> struct IsSerializable<loo::vkfg::EPipelineDynamicState> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EPipelineDynamicState>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EPipelineDynamicState, 10> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Unknown";
self->enumValues[0].m_tagName = "Unknown";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "Viewport";
self->enumValues[1].m_tagName = "Viewport";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "Scissor";
self->enumValues[2].m_tagName = "Scissor";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 4;
self->enumValues[3].m_name = "StencilCompareMask";
self->enumValues[3].m_tagName = "StencilCompareMask";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 8;
self->enumValues[4].m_name = "StencilWriteMask";
self->enumValues[4].m_tagName = "StencilWriteMask";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 16;
self->enumValues[5].m_name = "StencilReference";
self->enumValues[5].m_tagName = "StencilReference";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 32;
self->enumValues[6].m_name = "ShadingRatePalette";
self->enumValues[6].m_tagName = "ShadingRatePalette";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 63;
self->enumValues[7].m_name = "All";
self->enumValues[7].m_tagName = "All";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 63;
self->enumValues[8].m_name = "RasterizerMask";
self->enumValues[8].m_tagName = "RasterizerMask";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 3;
self->enumValues[9].m_name = "Default";
self->enumValues[9].m_tagName = "Default";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EPipelineDynamicState),
Hash("loo::vkfg::EPipelineDynamicState"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EPipelineDynamicState",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EPipelineDynamicState>) noexcept
{
return LooGetEnum<loo::vkfg::EPipelineDynamicState>();
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

template<> struct IsSerializable<loo::vkfg::EResourceState> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::EResourceState>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::EResourceState, 68> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 0;
self->enumValues[0].m_name = "Unknown";
self->enumValues[0].m_tagName = "Unknown";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 1;
self->enumValues[1].m_name = "_Access_ShaderStorage";
self->enumValues[1].m_tagName = "_Access_ShaderStorage";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 2;
self->enumValues[2].m_name = "_Access_Uniform";
self->enumValues[2].m_tagName = "_Access_Uniform";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 3;
self->enumValues[3].m_name = "_Access_ShaderSample";
self->enumValues[3].m_tagName = "_Access_ShaderSample";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 4;
self->enumValues[4].m_name = "_Access_InputAttachment";
self->enumValues[4].m_tagName = "_Access_InputAttachment";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 5;
self->enumValues[5].m_name = "_Access_Transfer";
self->enumValues[5].m_tagName = "_Access_Transfer";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;

/* EnumConstant 7 */
self->enumValues[6].m_index = 6;
self->enumValues[6].m_value = 6;
self->enumValues[6].m_name = "_Access_ColorAttachment";
self->enumValues[6].m_tagName = "_Access_ColorAttachment";
self->enumValues[6].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[6].m_type = nullptr;

/* EnumConstant 8 */
self->enumValues[7].m_index = 7;
self->enumValues[7].m_value = 7;
self->enumValues[7].m_name = "_Access_DepthStencilAttachment";
self->enumValues[7].m_tagName = "_Access_DepthStencilAttachment";
self->enumValues[7].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[7].m_type = nullptr;

/* EnumConstant 9 */
self->enumValues[8].m_index = 8;
self->enumValues[8].m_value = 8;
self->enumValues[8].m_name = "_Access_Host";
self->enumValues[8].m_tagName = "_Access_Host";
self->enumValues[8].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[8].m_type = nullptr;

/* EnumConstant 10 */
self->enumValues[9].m_index = 9;
self->enumValues[9].m_value = 9;
self->enumValues[9].m_name = "_Access_Present";
self->enumValues[9].m_tagName = "_Access_Present";
self->enumValues[9].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[9].m_type = nullptr;

/* EnumConstant 11 */
self->enumValues[10].m_index = 10;
self->enumValues[10].m_value = 10;
self->enumValues[10].m_name = "_Access_IndirectBuffer";
self->enumValues[10].m_tagName = "_Access_IndirectBuffer";
self->enumValues[10].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[10].m_type = nullptr;

/* EnumConstant 12 */
self->enumValues[11].m_index = 11;
self->enumValues[11].m_value = 11;
self->enumValues[11].m_name = "_Access_IndexBuffer";
self->enumValues[11].m_tagName = "_Access_IndexBuffer";
self->enumValues[11].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[11].m_type = nullptr;

/* EnumConstant 13 */
self->enumValues[12].m_index = 12;
self->enumValues[12].m_value = 12;
self->enumValues[12].m_name = "_Access_VertexBuffer";
self->enumValues[12].m_tagName = "_Access_VertexBuffer";
self->enumValues[12].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[12].m_type = nullptr;

/* EnumConstant 14 */
self->enumValues[13].m_index = 13;
self->enumValues[13].m_value = 13;
self->enumValues[13].m_name = "_Access_ConditionalRendering";
self->enumValues[13].m_tagName = "_Access_ConditionalRendering";
self->enumValues[13].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[13].m_type = nullptr;

/* EnumConstant 15 */
self->enumValues[14].m_index = 14;
self->enumValues[14].m_value = 14;
self->enumValues[14].m_name = "_Access_CommandProcess";
self->enumValues[14].m_tagName = "_Access_CommandProcess";
self->enumValues[14].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[14].m_type = nullptr;

/* EnumConstant 16 */
self->enumValues[15].m_index = 15;
self->enumValues[15].m_value = 15;
self->enumValues[15].m_name = "_Access_ShadingRateImage";
self->enumValues[15].m_tagName = "_Access_ShadingRateImage";
self->enumValues[15].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[15].m_type = nullptr;

/* EnumConstant 17 */
self->enumValues[16].m_index = 16;
self->enumValues[16].m_value = 16;
self->enumValues[16].m_name = "_Access_BuildRayTracingAS";
self->enumValues[16].m_tagName = "_Access_BuildRayTracingAS";
self->enumValues[16].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[16].m_type = nullptr;

/* EnumConstant 18 */
self->enumValues[17].m_index = 17;
self->enumValues[17].m_value = 17;
self->enumValues[17].m_name = "_Access_RTASBuildingBuffer";
self->enumValues[17].m_tagName = "_Access_RTASBuildingBuffer";
self->enumValues[17].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[17].m_type = nullptr;

/* EnumConstant 19 */
self->enumValues[18].m_index = 18;
self->enumValues[18].m_value = 18;
self->enumValues[18].m_name = "_AccessLast";
self->enumValues[18].m_tagName = "_AccessLast";
self->enumValues[18].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[18].m_type = nullptr;

/* EnumConstant 20 */
self->enumValues[19].m_index = 19;
self->enumValues[19].m_value = 255;
self->enumValues[19].m_name = "_AccessMask";
self->enumValues[19].m_tagName = "_AccessMask";
self->enumValues[19].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[19].m_type = nullptr;

/* EnumConstant 21 */
self->enumValues[20].m_index = 20;
self->enumValues[20].m_value = 256;
self->enumValues[20].m_name = "_VertexShader";
self->enumValues[20].m_tagName = "_VertexShader";
self->enumValues[20].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[20].m_type = nullptr;

/* EnumConstant 22 */
self->enumValues[21].m_index = 21;
self->enumValues[21].m_value = 512;
self->enumValues[21].m_name = "_TessControlShader";
self->enumValues[21].m_tagName = "_TessControlShader";
self->enumValues[21].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[21].m_type = nullptr;

/* EnumConstant 23 */
self->enumValues[22].m_index = 22;
self->enumValues[22].m_value = 1024;
self->enumValues[22].m_name = "_TessEvaluationShader";
self->enumValues[22].m_tagName = "_TessEvaluationShader";
self->enumValues[22].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[22].m_type = nullptr;

/* EnumConstant 24 */
self->enumValues[23].m_index = 23;
self->enumValues[23].m_value = 2048;
self->enumValues[23].m_name = "_GeometryShader";
self->enumValues[23].m_tagName = "_GeometryShader";
self->enumValues[23].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[23].m_type = nullptr;

/* EnumConstant 25 */
self->enumValues[24].m_index = 24;
self->enumValues[24].m_value = 4096;
self->enumValues[24].m_name = "_FragmentShader";
self->enumValues[24].m_tagName = "_FragmentShader";
self->enumValues[24].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[24].m_type = nullptr;

/* EnumConstant 26 */
self->enumValues[25].m_index = 25;
self->enumValues[25].m_value = 8192;
self->enumValues[25].m_name = "_ComputeShader";
self->enumValues[25].m_tagName = "_ComputeShader";
self->enumValues[25].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[25].m_type = nullptr;

/* EnumConstant 27 */
self->enumValues[26].m_index = 26;
self->enumValues[26].m_value = 16384;
self->enumValues[26].m_name = "_MeshTaskShader";
self->enumValues[26].m_tagName = "_MeshTaskShader";
self->enumValues[26].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[26].m_type = nullptr;

/* EnumConstant 28 */
self->enumValues[27].m_index = 27;
self->enumValues[27].m_value = 32768;
self->enumValues[27].m_name = "_MeshShader";
self->enumValues[27].m_tagName = "_MeshShader";
self->enumValues[27].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[27].m_type = nullptr;

/* EnumConstant 29 */
self->enumValues[28].m_index = 28;
self->enumValues[28].m_value = 65536;
self->enumValues[28].m_name = "_RayTracingShader";
self->enumValues[28].m_tagName = "_RayTracingShader";
self->enumValues[28].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[28].m_type = nullptr;

/* EnumConstant 30 */
self->enumValues[29].m_index = 29;
self->enumValues[29].m_value = 3840;
self->enumValues[29].m_name = "_AllGraphics";
self->enumValues[29].m_tagName = "_AllGraphics";
self->enumValues[29].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[29].m_type = nullptr;

/* EnumConstant 31 */
self->enumValues[30].m_index = 30;
self->enumValues[30].m_value = 77568;
self->enumValues[30].m_name = "_ShaderMask";
self->enumValues[30].m_tagName = "_ShaderMask";
self->enumValues[30].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[30].m_type = nullptr;

/* EnumConstant 32 */
self->enumValues[31].m_index = 31;
self->enumValues[31].m_value = 33554432;
self->enumValues[31].m_name = "_BufferDynamicOffset";
self->enumValues[31].m_tagName = "_BufferDynamicOffset";
self->enumValues[31].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[31].m_type = nullptr;

/* EnumConstant 33 */
self->enumValues[32].m_index = 32;
self->enumValues[32].m_value = 67108864;
self->enumValues[32].m_name = "InvalidateBefore";
self->enumValues[32].m_tagName = "InvalidateBefore";
self->enumValues[32].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[32].m_type = nullptr;

/* EnumConstant 34 */
self->enumValues[33].m_index = 33;
self->enumValues[33].m_value = 134217728;
self->enumValues[33].m_name = "InvalidateAfter";
self->enumValues[33].m_tagName = "InvalidateAfter";
self->enumValues[33].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[33].m_type = nullptr;

/* EnumConstant 35 */
self->enumValues[34].m_index = 34;
self->enumValues[34].m_value = 268435456;
self->enumValues[34].m_name = "EarlyFragmentTests";
self->enumValues[34].m_tagName = "EarlyFragmentTests";
self->enumValues[34].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[34].m_type = nullptr;

/* EnumConstant 36 */
self->enumValues[35].m_index = 35;
self->enumValues[35].m_value = 536870912;
self->enumValues[35].m_name = "LateFragmentTests";
self->enumValues[35].m_tagName = "LateFragmentTests";
self->enumValues[35].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[35].m_type = nullptr;

/* EnumConstant 37 */
self->enumValues[36].m_index = 36;
self->enumValues[36].m_value = 1073741824;
self->enumValues[36].m_name = "_Read";
self->enumValues[36].m_tagName = "_Read";
self->enumValues[36].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[36].m_type = nullptr;

/* EnumConstant 38 */
self->enumValues[37].m_index = 37;
self->enumValues[37].m_value = 2147483648;
self->enumValues[37].m_name = "_Write";
self->enumValues[37].m_tagName = "_Write";
self->enumValues[37].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[37].m_type = nullptr;

/* EnumConstant 39 */
self->enumValues[38].m_index = 38;
self->enumValues[38].m_value = 3221225472;
self->enumValues[38].m_name = "_ReadWrite";
self->enumValues[38].m_tagName = "_ReadWrite";
self->enumValues[38].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[38].m_type = nullptr;

/* EnumConstant 40 */
self->enumValues[39].m_index = 39;
self->enumValues[39].m_value = 3221225727;
self->enumValues[39].m_name = "_StateMask";
self->enumValues[39].m_tagName = "_StateMask";
self->enumValues[39].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[39].m_type = nullptr;

/* EnumConstant 41 */
self->enumValues[40].m_index = 40;
self->enumValues[40].m_value = 1073741825;
self->enumValues[40].m_name = "ShaderRead";
self->enumValues[40].m_tagName = "ShaderRead";
self->enumValues[40].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[40].m_type = nullptr;

/* EnumConstant 42 */
self->enumValues[41].m_index = 41;
self->enumValues[41].m_value = 2147483649;
self->enumValues[41].m_name = "ShaderWrite";
self->enumValues[41].m_tagName = "ShaderWrite";
self->enumValues[41].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[41].m_type = nullptr;

/* EnumConstant 43 */
self->enumValues[42].m_index = 42;
self->enumValues[42].m_value = 3221225473;
self->enumValues[42].m_name = "ShaderReadWrite";
self->enumValues[42].m_tagName = "ShaderReadWrite";
self->enumValues[42].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[42].m_type = nullptr;

/* EnumConstant 44 */
self->enumValues[43].m_index = 43;
self->enumValues[43].m_value = 1073741826;
self->enumValues[43].m_name = "UniformRead";
self->enumValues[43].m_tagName = "UniformRead";
self->enumValues[43].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[43].m_type = nullptr;

/* EnumConstant 45 */
self->enumValues[44].m_index = 44;
self->enumValues[44].m_value = 1073741827;
self->enumValues[44].m_name = "ShaderSample";
self->enumValues[44].m_tagName = "ShaderSample";
self->enumValues[44].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[44].m_type = nullptr;

/* EnumConstant 46 */
self->enumValues[45].m_index = 45;
self->enumValues[45].m_value = 1073741828;
self->enumValues[45].m_name = "InputAttachment";
self->enumValues[45].m_tagName = "InputAttachment";
self->enumValues[45].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[45].m_type = nullptr;

/* EnumConstant 47 */
self->enumValues[46].m_index = 46;
self->enumValues[46].m_value = 1073741829;
self->enumValues[46].m_name = "TransferSrc";
self->enumValues[46].m_tagName = "TransferSrc";
self->enumValues[46].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[46].m_type = nullptr;

/* EnumConstant 48 */
self->enumValues[47].m_index = 47;
self->enumValues[47].m_value = 2147483653;
self->enumValues[47].m_name = "TransferDst";
self->enumValues[47].m_tagName = "TransferDst";
self->enumValues[47].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[47].m_type = nullptr;

/* EnumConstant 49 */
self->enumValues[48].m_index = 48;
self->enumValues[48].m_value = 1073741830;
self->enumValues[48].m_name = "ColorAttachmentRead";
self->enumValues[48].m_tagName = "ColorAttachmentRead";
self->enumValues[48].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[48].m_type = nullptr;

/* EnumConstant 50 */
self->enumValues[49].m_index = 49;
self->enumValues[49].m_value = 2147483654;
self->enumValues[49].m_name = "ColorAttachmentWrite";
self->enumValues[49].m_tagName = "ColorAttachmentWrite";
self->enumValues[49].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[49].m_type = nullptr;

/* EnumConstant 51 */
self->enumValues[50].m_index = 50;
self->enumValues[50].m_value = 3221225478;
self->enumValues[50].m_name = "ColorAttachmentReadWrite";
self->enumValues[50].m_tagName = "ColorAttachmentReadWrite";
self->enumValues[50].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[50].m_type = nullptr;

/* EnumConstant 52 */
self->enumValues[51].m_index = 51;
self->enumValues[51].m_value = 1073741831;
self->enumValues[51].m_name = "DepthStencilAttachmentRead";
self->enumValues[51].m_tagName = "DepthStencilAttachmentRead";
self->enumValues[51].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[51].m_type = nullptr;

/* EnumConstant 53 */
self->enumValues[52].m_index = 52;
self->enumValues[52].m_value = 2147483655;
self->enumValues[52].m_name = "DepthStencilAttachmentWrite";
self->enumValues[52].m_tagName = "DepthStencilAttachmentWrite";
self->enumValues[52].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[52].m_type = nullptr;

/* EnumConstant 54 */
self->enumValues[53].m_index = 53;
self->enumValues[53].m_value = 3221225479;
self->enumValues[53].m_name = "DepthStencilAttachmentReadWrite";
self->enumValues[53].m_tagName = "DepthStencilAttachmentReadWrite";
self->enumValues[53].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[53].m_type = nullptr;

/* EnumConstant 55 */
self->enumValues[54].m_index = 54;
self->enumValues[54].m_value = 1073741832;
self->enumValues[54].m_name = "HostRead";
self->enumValues[54].m_tagName = "HostRead";
self->enumValues[54].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[54].m_type = nullptr;

/* EnumConstant 56 */
self->enumValues[55].m_index = 55;
self->enumValues[55].m_value = 2147483656;
self->enumValues[55].m_name = "HostWrite";
self->enumValues[55].m_tagName = "HostWrite";
self->enumValues[55].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[55].m_type = nullptr;

/* EnumConstant 57 */
self->enumValues[56].m_index = 56;
self->enumValues[56].m_value = 3221225480;
self->enumValues[56].m_name = "HostReadWrite";
self->enumValues[56].m_tagName = "HostReadWrite";
self->enumValues[56].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[56].m_type = nullptr;

/* EnumConstant 58 */
self->enumValues[57].m_index = 57;
self->enumValues[57].m_value = 1073741833;
self->enumValues[57].m_name = "PresentImage";
self->enumValues[57].m_tagName = "PresentImage";
self->enumValues[57].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[57].m_type = nullptr;

/* EnumConstant 59 */
self->enumValues[58].m_index = 58;
self->enumValues[58].m_value = 1073741834;
self->enumValues[58].m_name = "IndirectBuffer";
self->enumValues[58].m_tagName = "IndirectBuffer";
self->enumValues[58].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[58].m_type = nullptr;

/* EnumConstant 60 */
self->enumValues[59].m_index = 59;
self->enumValues[59].m_value = 1073741835;
self->enumValues[59].m_name = "IndexBuffer";
self->enumValues[59].m_tagName = "IndexBuffer";
self->enumValues[59].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[59].m_type = nullptr;

/* EnumConstant 61 */
self->enumValues[60].m_index = 60;
self->enumValues[60].m_value = 1073741836;
self->enumValues[60].m_name = "VertexBuffer";
self->enumValues[60].m_tagName = "VertexBuffer";
self->enumValues[60].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[60].m_type = nullptr;

/* EnumConstant 62 */
self->enumValues[61].m_index = 61;
self->enumValues[61].m_value = 1073741840;
self->enumValues[61].m_name = "BuildRayTracingStructRead";
self->enumValues[61].m_tagName = "BuildRayTracingStructRead";
self->enumValues[61].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[61].m_type = nullptr;

/* EnumConstant 63 */
self->enumValues[62].m_index = 62;
self->enumValues[62].m_value = 2147483664;
self->enumValues[62].m_name = "BuildRayTracingStructWrite";
self->enumValues[62].m_tagName = "BuildRayTracingStructWrite";
self->enumValues[62].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[62].m_type = nullptr;

/* EnumConstant 64 */
self->enumValues[63].m_index = 63;
self->enumValues[63].m_value = 3221225488;
self->enumValues[63].m_name = "BuildRayTracingStructReadWrite";
self->enumValues[63].m_tagName = "BuildRayTracingStructReadWrite";
self->enumValues[63].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[63].m_type = nullptr;

/* EnumConstant 65 */
self->enumValues[64].m_index = 64;
self->enumValues[64].m_value = 1073741841;
self->enumValues[64].m_name = "RTASBuildingBufferRead";
self->enumValues[64].m_tagName = "RTASBuildingBufferRead";
self->enumValues[64].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[64].m_type = nullptr;

/* EnumConstant 66 */
self->enumValues[65].m_index = 65;
self->enumValues[65].m_value = 3221225489;
self->enumValues[65].m_name = "RTASBuildingBufferReadWrite";
self->enumValues[65].m_tagName = "RTASBuildingBufferReadWrite";
self->enumValues[65].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[65].m_type = nullptr;

/* EnumConstant 67 */
self->enumValues[66].m_index = 66;
self->enumValues[66].m_value = 1073807361;
self->enumValues[66].m_name = "RayTracingShaderRead";
self->enumValues[66].m_tagName = "RayTracingShaderRead";
self->enumValues[66].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[66].m_type = nullptr;

/* EnumConstant 68 */
self->enumValues[67].m_index = 67;
self->enumValues[67].m_value = 1073741839;
self->enumValues[67].m_name = "ShadingRateImageRead";
self->enumValues[67].m_tagName = "ShadingRateImageRead";
self->enumValues[67].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[67].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::EResourceState),
Hash("loo::vkfg::EResourceState"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::EResourceState",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::EResourceState>) noexcept
{
return LooGetEnum<loo::vkfg::EResourceState>();
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

template<> struct IsSerializable<loo::vkfg::ERayTracingGeometryFlags> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::ERayTracingGeometryFlags>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::ERayTracingGeometryFlags, 3> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "Opaque";
self->enumValues[0].m_tagName = "Opaque";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "NoDuplicateAnyHitInvocation";
self->enumValues[1].m_tagName = "NoDuplicateAnyHitInvocation";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 0;
self->enumValues[2].m_name = "Unknown";
self->enumValues[2].m_tagName = "Unknown";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::ERayTracingGeometryFlags),
Hash("loo::vkfg::ERayTracingGeometryFlags"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::ERayTracingGeometryFlags",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::ERayTracingGeometryFlags>) noexcept
{
return LooGetEnum<loo::vkfg::ERayTracingGeometryFlags>();
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

template<> struct IsSerializable<loo::vkfg::ERayTracingInstanceFlags> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::ERayTracingInstanceFlags>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::ERayTracingInstanceFlags, 5> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "TriangleCullDisable";
self->enumValues[0].m_tagName = "TriangleCullDisable";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "TriangleFrontCCW";
self->enumValues[1].m_tagName = "TriangleFrontCCW";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4;
self->enumValues[2].m_name = "ForceOpaque";
self->enumValues[2].m_tagName = "ForceOpaque";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 8;
self->enumValues[3].m_name = "ForceNonOpaque";
self->enumValues[3].m_tagName = "ForceNonOpaque";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 0;
self->enumValues[4].m_name = "Unknown";
self->enumValues[4].m_tagName = "Unknown";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::ERayTracingInstanceFlags),
Hash("loo::vkfg::ERayTracingInstanceFlags"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::ERayTracingInstanceFlags",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::ERayTracingInstanceFlags>) noexcept
{
return LooGetEnum<loo::vkfg::ERayTracingInstanceFlags>();
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

template<> struct IsSerializable<loo::vkfg::ERayTracingFlags> { static constexpr bool value = true; };
namespace detail
{
template<>
inline LooEnum const *
LooGetEnumImpl(LooEnumTag<loo::vkfg::ERayTracingFlags>) noexcept
{
static detail::LooEnumBuilder<loo::vkfg::ERayTracingFlags, 6> reflected([](auto self) {

/* EnumConstant 1 */
self->enumValues[0].m_index = 0;
self->enumValues[0].m_value = 1;
self->enumValues[0].m_name = "AllowUpdate";
self->enumValues[0].m_tagName = "AllowUpdate";
self->enumValues[0].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[0].m_type = nullptr;

/* EnumConstant 2 */
self->enumValues[1].m_index = 1;
self->enumValues[1].m_value = 2;
self->enumValues[1].m_name = "AllowCompaction";
self->enumValues[1].m_tagName = "AllowCompaction";
self->enumValues[1].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[1].m_type = nullptr;

/* EnumConstant 3 */
self->enumValues[2].m_index = 2;
self->enumValues[2].m_value = 4;
self->enumValues[2].m_name = "PreferFastTrace";
self->enumValues[2].m_tagName = "PreferFastTrace";
self->enumValues[2].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[2].m_type = nullptr;

/* EnumConstant 4 */
self->enumValues[3].m_index = 3;
self->enumValues[3].m_value = 8;
self->enumValues[3].m_name = "PreferFastBuild";
self->enumValues[3].m_tagName = "PreferFastBuild";
self->enumValues[3].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[3].m_type = nullptr;

/* EnumConstant 5 */
self->enumValues[4].m_index = 4;
self->enumValues[4].m_value = 16;
self->enumValues[4].m_name = "LowMemory";
self->enumValues[4].m_tagName = "LowMemory";
self->enumValues[4].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[4].m_type = nullptr;

/* EnumConstant 6 */
self->enumValues[5].m_index = 5;
self->enumValues[5].m_value = 0;
self->enumValues[5].m_name = "Unknown";
self->enumValues[5].m_tagName = "Unknown";
self->enumValues[5].m_flags = LooField::kFlagsNull | LooField::kFlagsSerialized;
self->enumValues[5].m_type = nullptr;
});
static LooEnum cache(
sizeof(loo::vkfg::ERayTracingFlags),
Hash("loo::vkfg::ERayTracingFlags"),
reflected.enumValues,
reflected.enumValues + reflected.numValues,
"loo::vkfg::ERayTracingFlags",
LooClass::kFlagsNull);
return &cache;
}

template<>
inline LooType const *
LooGetTypeImpl(LooTypeTag<loo::vkfg::ERayTracingFlags>) noexcept
{
return LooGetEnum<loo::vkfg::ERayTracingFlags>();
}
} /* namespace detail */
} /* namespace looreflect */

