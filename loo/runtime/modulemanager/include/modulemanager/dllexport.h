#ifndef LOOMODULEMANAGER_DLLEXPORT_H
#define LOOMODULEMANAGER_DLLEXPORT_H
#ifdef LOOMODULEMANAGER_DLL_EXPORT
#define LOOMODULEMANAGER_EXPORT __declspec(dllexport)
#else
#define LOOMODULEMANAGER_EXPORT __declspec(dllimport)
#endif
#define MODULENAME_MODULEMANAGER "modulemanager"
#endif