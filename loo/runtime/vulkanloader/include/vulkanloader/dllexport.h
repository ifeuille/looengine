#ifndef VULKANLOADER_DLLEXPORT_H
#define VULKANLOADER_DLLEXPORT_H
#ifdef VULKANLOADER_DLL_EXPORT
#define VULKANLOADER_EXPORT __declspec(dllexport)
#else
#define VULKANLOADER_EXPORT __declspec(dllimport)
#endif

#endif