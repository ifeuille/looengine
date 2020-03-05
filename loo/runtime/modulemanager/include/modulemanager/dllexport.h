#ifndef LOOMODULEMANAGER_DLLEXPORT_H
#define LOOMODULEMANAGER_DLLEXPORT_H
#ifndef __LOOREFLECT__
#include "global/compiler.h"
#ifdef LOOMODULEMANAGER_DLL_EXPORT
#define LOOMODULEMANAGER_EXPORT LOO_SYMBOL_EXPORT
#else
#define LOOMODULEMANAGER_EXPORT LOO_SYMBOL_IMPORT
#endif
#else
#define LOOMODULEMANAGER_EXPORT
#define LOOMODULEMANAGER_EXPORT
#endif
#define MODULENAME_MODULEMANAGER "modulemanager"
#endif