#ifndef CORE_DLLEXPORT_H
#define CORE_DLLEXPORT_H

#ifndef __LOOREFLECT__
#include "global/compiler.h"
#ifdef CORE_DLL_EXPORT
#define CORE_EXPORT LOO_SYMBOL_EXPORT
#else
#define CORE_EXPORT LOO_SYMBOL_IMPORT
#endif
#else
#define CORE_EXPORT
#define CORE_EXPORT
#endif

#define MODULENAME_CORE "core"
#endif