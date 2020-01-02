#ifndef CORE_DLLEXPORT_H
#define CORE_DLLEXPORT_H
#ifdef FILEMANAGER_DLL_EXPORT
#define CORE_EXPORT __declspec(dllexport)
#else
#define CORE_EXPORT __declspec(dllimport)
#endif
#define MODULENAME_CORE "core"
#endif