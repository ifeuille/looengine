#ifndef LOOREFLECT_DLLEXPORT_H
#define LOOREFLECT_DLLEXPORT_H
#ifdef LOOREFLECT_DLL_EXPORT
#define LOOREFLECT_EXPORT __declspec(dllexport)
#else
#define LOOREFLECT_EXPORT __declspec(dllimport)
#endif
#define MODULENAME_LOOREFLECT "looreflect"
#endif