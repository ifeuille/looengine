#ifndef LOOVKFG_DLLEXPORT_H
#define LOOVKFG_DLLEXPORT_H
#ifdef LOOVKFG_DLL_EXPORT
#define LOOVKFG_EXPORT __declspec(dllexport)
#else
#define LOOVKFG_EXPORT __declspec(dllimport)
#endif
#define MODULENAME_LOOVKFG "vkfg"
#endif