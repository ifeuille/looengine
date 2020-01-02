#ifndef FILENAMAGER_DLLEXPORT_H
#define FILENAMAGER_DLLEXPORT_H
#ifdef FILEMANAGER_DLL_EXPORT
#define FILEMANAGER_EXPORT __declspec(dllexport)
#else
#define FILEMANAGER_EXPORT __declspec(dllimport)
#endif
#define MODULENAME_FILEMANAGER "filemanager"
#endif