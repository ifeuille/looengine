#ifndef LOOVKFG_DLLEXPORT_H
#define LOOVKFG_DLLEXPORT_H
#ifndef __LOOREFLECT__
#include "global/compiler.h"
#ifdef LOOVKFG_DLL_EXPORT
#define LOOVKFG_EXPORT LOO_SYMBOL_EXPORT
#else
#define LOOVKFG_EXPORT LOO_SYMBOL_IMPORT
#endif
#else
#define LOOVKFG_EXPORT
#define LOOVKFG_EXPORT
#endif
#define MODULENAME_LOOVKFG "vkfg"
#endif