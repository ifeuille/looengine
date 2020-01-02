#ifndef LOOREFLECT_DLLEXPORT_H
#define LOOREFLECT_DLLEXPORT_H
#ifdef FILEMANAGER_DLL_EXPORT
#define FILEMANAGER_EXPORT __declspec(dllexport)
#else
#define FILEMANAGER_EXPORT __declspec(dllimport)
#endif
#define MODULENAME_FILEMANAGER "filemanager"
#endif