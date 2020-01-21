#ifndef LOO_RHI_RENDERUTILS_H
#define LOO_RHI_RENDERUTILS_H
#include "rhi/dllexporter.h"
#include "global/global.h"
#include "rhi/elementformat.h"
#include "global/template/external.h"


/** The indices for drawing a cube. */
extern RHI_EXPORT const loo::uint16 GCubeIndices[12 * 3];


/** Information about a pixel format. */
struct PixelFormatInfo
{
	const TCHAR*	Name;
	loo::int32				BlockSizeX,
		BlockSizeY,
		BlockSizeZ,
		BlockBytes,
		NumComponents;
	/** Platform specific token, e.g. D3DFORMAT with D3DDrv										*/
	loo::uint32			PlatformFormat;
	/** Whether the texture format is supported on the current platform/ rendering combination	*/
	bool			Supported;
	loo::rhi::EPixelFormat	UnrealFormat;
};

extern RHI_EXPORT PixelFormatInfo GPixelFormats[loo::rhi::PF_MAX];		// Maps members of EPixelFormat to a FPixelFormatInfo describing the format.



extern RHI_EXPORT SIZE_T CalculateImageBytes (loo::uint32 SizeX, loo::uint32 SizeY, loo::uint32 SizeZ, loo::uint8 Format);



#endif