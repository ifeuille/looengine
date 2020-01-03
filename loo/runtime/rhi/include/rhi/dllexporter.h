#ifndef RHI_DLLEXPORT_H
#define RHI_DLLEXPORT_H
#ifdef RHI_DLL_EXPORT
#define RHI_EXPORT __declspec(dllexport)
#else
#define RHI_EXPORT __declspec(dllimport)
#endif
#define MODULENAME_RHI "rhi"
#endif