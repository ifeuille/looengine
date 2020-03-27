#ifndef LOO_RHI_CREATEINFO_H
#define LOO_RHI_CREATEINFO_H
#pragma once
#include "global/global.h"
#include "rhi/elementformat.h"

namespace loo
{
	namespace rhi
	{
		typedef struct LOOApplicationInfo {
			////LEStructureType    sType;
			const char*        pApplicationName;
			uint32_t           applicationVersion;
			const char*        pEngineName;
			uint32_t           engineVersion;
			uint32_t           apiVersion;
		} LOOApplicationInfo;

		typedef struct LOOInstanceCreateInfo {
			LOOInstanceCreateFlags       flags;
			const LOOApplicationInfo*    pApplicationInfo;
			uint32_t                    enabledLayerCount;
			const char* const*          ppEnabledLayerNames;
			uint32_t                    enabledExtensionCount;
			const char* const*          ppEnabledExtensionNames;
		} LOOInstanceCreateInfo;
	}
}

#endif