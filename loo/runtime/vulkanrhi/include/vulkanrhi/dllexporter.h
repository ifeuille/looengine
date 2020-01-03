#ifndef VULKANRHI_DLLEXPORT_H
#define VULKANRHI_DLLEXPORT_H
#ifdef VULKANRHI_DLL_EXPORT
#define VULKANRHI_EXPORT __declspec(dllexport)
#else
#define VULKANRHI_EXPORT __declspec(dllimport)
#endif
#define MODULENAME_VULKANRHI "vulkanrhi"
#endif