#include "rhi/renderutils.h"


const loo::uint16 GCubeIndices[12 * 3] =
{
	0, 2, 3,
	0, 3, 1,
	4, 5, 7,
	4, 7, 6,
	0, 1, 5,
	0, 5, 4,
	2, 6, 7,
	2, 7, 3,
	0, 4, 6,
	0, 6, 2,
	1, 3, 7,
	1, 7, 5,
};

PixelFormatInfo	GPixelFormats[loo::rhi::PF_MAX] =
{
	// Name						BlockSizeX	BlockSizeY	BlockSizeZ	BlockBytes	NumComponents	PlatformFormat	Supported		UnrealFormat

	{ TEXT ("unknown"),			0,			0,			0,			0,			0,				0,				0,				loo::rhi::PF_Unknown			},
	{ TEXT ("A32B32G32R32F"),	1,			1,			1,			16,			4,				0,				1,				loo::rhi::PF_A32B32G32R32F	},
	{ TEXT ("B8G8R8A8"),			1,			1,			1,			4,			4,				0,				1,				loo::rhi::PF_B8G8R8A8			},
	{ TEXT ("G8"),				1,			1,			1,			1,			1,				0,				1,				loo::rhi::PF_G8				},
	{ TEXT ("G16"),				1,			1,			1,			2,			1,				0,				1,				loo::rhi::PF_G16				},
	{ TEXT ("DXT1"),				4,			4,			1,			8,			3,				0,				1,				loo::rhi::PF_DXT1				},
	{ TEXT ("DXT3"),				4,			4,			1,			16,			4,				0,				1,				loo::rhi::PF_DXT3				},
	{ TEXT ("DXT5"),				4,			4,			1,			16,			4,				0,				1,				loo::rhi::PF_DXT5				},
	{ TEXT ("UYVY"),				2,			1,			1,			4,			4,				0,				0,				loo::rhi::PF_UYVY				},
	{ TEXT ("FloatRGB"),			1,			1,			1,			4,			3,				0,				1,				loo::rhi::PF_FloatRGB			},
	{ TEXT ("FloatRGBA"),		1,			1,			1,			8,			4,				0,				1,				loo::rhi::PF_FloatRGBA		},
	{ TEXT ("DepthStencil"),		1,			1,			1,			4,			1,				0,				0,				loo::rhi::PF_DepthStencil		},
	{ TEXT ("ShadowDepth"),		1,			1,			1,			4,			1,				0,				0,				loo::rhi::PF_ShadowDepth		},
	{ TEXT ("R32_FLOAT"),		1,			1,			1,			4,			1,				0,				1,				loo::rhi::PF_R32_FLOAT		},
	{ TEXT ("G16R16"),			1,			1,			1,			4,			2,				0,				1,				loo::rhi::PF_G16R16			},
	{ TEXT ("G16R16F"),			1,			1,			1,			4,			2,				0,				1,				loo::rhi::PF_G16R16F			},
	{ TEXT ("G16R16F_FILTER"),	1,			1,			1,			4,			2,				0,				1,				loo::rhi::PF_G16R16F_FILTER	},
	{ TEXT ("G32R32F"),			1,			1,			1,			8,			2,				0,				1,				loo::rhi::PF_G32R32F			},
	{ TEXT ("A2B10G10R10"),      1,          1,          1,          4,          4,              0,              1,				loo::rhi::PF_A2B10G10R10		},
	{ TEXT ("A16B16G16R16"),		1,			1,			1,			8,			4,				0,				1,				loo::rhi::PF_A16B16G16R16		},
	{ TEXT ("D24"),				1,			1,			1,			4,			1,				0,				1,				loo::rhi::PF_D24				},
	{ TEXT ("PF_R16F"),			1,			1,			1,			2,			1,				0,				1,				loo::rhi::PF_R16F				},
	{ TEXT ("PF_R16F_FILTER"),	1,			1,			1,			2,			1,				0,				1,				loo::rhi::PF_R16F_FILTER		},
	{ TEXT ("BC5"),				4,			4,			1,			16,			2,				0,				1,				loo::rhi::PF_BC5				},
	{ TEXT ("V8U8"),				1,			1,			1,			2,			2,				0,				1,				loo::rhi::PF_V8U8				},
	{ TEXT ("A1"),				1,			1,			1,			1,			1,				0,				0,				loo::rhi::PF_A1				},
	{ TEXT ("FloatR11G11B10"),	1,			1,			1,			4,			3,				0,				0,				loo::rhi::PF_FloatR11G11B10	},
	{ TEXT ("A8"),				1,			1,			1,			1,			1,				0,				1,				loo::rhi::PF_A8				},
	{ TEXT ("R32_UINT"),			1,			1,			1,			4,			1,				0,				1,				loo::rhi::PF_R32_UINT			},
	{ TEXT ("R32_SINT"),			1,			1,			1,			4,			1,				0,				1,				loo::rhi::PF_R32_SINT			},

	// IOS Support
	{ TEXT ("PVRTC2"),			8,			4,			1,			8,			4,				0,				0,				loo::rhi::PF_PVRTC2			},
	{ TEXT ("PVRTC4"),			4,			4,			1,			8,			4,				0,				0,				loo::rhi::PF_PVRTC4			},

	{ TEXT ("R16_UINT"),			1,			1,			1,			2,			1,				0,				1,				loo::rhi::PF_R16_UINT			},
	{ TEXT ("R16_SINT"),			1,			1,			1,			2,			1,				0,				1,				loo::rhi::PF_R16_SINT			},
	{ TEXT ("R16G16B16A16_UINT"),1,			1,			1,			8,			4,				0,				1,				loo::rhi::PF_R16G16B16A16_UINT},
	{ TEXT ("R16G16B16A16_SINT"),1,			1,			1,			8,			4,				0,				1,				loo::rhi::PF_R16G16B16A16_SINT},
	{ TEXT ("R5G6B5_UNORM"),     1,          1,          1,          2,          3,              0,              1,              loo::rhi::PF_R5G6B5_UNORM		},
	{ TEXT ("R8G8B8A8"),			1,			1,			1,			4,			4,				0,				1,				loo::rhi::PF_R8G8B8A8			},
	{ TEXT ("A8R8G8B8"),			1,			1,			1,			4,			4,				0,				1,				loo::rhi::PF_A8R8G8B8			},
	{ TEXT ("BC4"),				4,			4,			1,			8,			1,				0,				1,				loo::rhi::PF_BC4				},
	{ TEXT ("R8G8"),				1,			1,			1,			2,			2,				0,				1,				loo::rhi::PF_R8G8				},

	{ TEXT ("ATC_RGB"),			4,			4,			1,			8,			3,				0,				0,				loo::rhi::PF_ATC_RGB			},
	{ TEXT ("ATC_RGBA_E"),		4,			4,			1,			16,			4,				0,				0,				loo::rhi::PF_ATC_RGBA_E		},
	{ TEXT ("ATC_RGBA_I"),		4,			4,			1,			16,			4,				0,				0,				loo::rhi::PF_ATC_RGBA_I		},
	{ TEXT ("X24_G8"),			1,			1,			1,			1,			1,				0,				0,				loo::rhi::PF_X24_G8			},
	{ TEXT ("ETC1"),				4,			4,			1,			8,			3,				0,				0,				loo::rhi::PF_ETC1				},
	{ TEXT ("ETC2_RGB"),			4,			4,			1,			8,			3,				0,				0,				loo::rhi::PF_ETC2_RGB			},
	{ TEXT ("ETC2_RGBA"),		4,			4,			1,			16,			4,				0,				0,				loo::rhi::PF_ETC2_RGBA		},
	{ TEXT ("PF_R32G32B32A32_UINT"),1,		1,			1,			16,			4,				0,				1,				loo::rhi::PF_R32G32B32A32_UINT},
	{ TEXT ("PF_R16G16_UINT"),	1,			1,			1,			4,			4,				0,				1,				loo::rhi::PF_R16G16_UINT},

	// ASTC support
	{ TEXT ("ASTC_4x4"),			4,			4,			1,			16,			4,				0,				0,				loo::rhi::PF_ASTC_4x4			},
	{ TEXT ("ASTC_6x6"),			6,			6,			1,			16,			4,				0,				0,				loo::rhi::PF_ASTC_6x6			},
	{ TEXT ("ASTC_8x8"),			8,			8,			1,			16,			4,				0,				0,				loo::rhi::PF_ASTC_8x8			},
	{ TEXT ("ASTC_10x10"),		10,			10,			1,			16,			4,				0,				0,				loo::rhi::PF_ASTC_10x10		},
	{ TEXT ("ASTC_12x12"),		12,			12,			1,			16,			4,				0,				0,				loo::rhi::PF_ASTC_12x12		},

	{ TEXT ("BC6H"),				4,			4,			1,			16,			3,				0,				1,				loo::rhi::PF_BC6H				},
	{ TEXT ("BC7"),				4,			4,			1,			16,			4,				0,				1,				loo::rhi::PF_BC7				},
	{ TEXT ("R8_UINT"),			1,			1,			1,			1,			1,				0,				1,				loo::rhi::PF_R8_UINT			},
	{ TEXT ("L8"),				1,			1,			1,			1,			1,				0,				0,				loo::rhi::PF_L8				},
	{ TEXT ("XGXR8"),			1,			1,			1,			4,			4,				0,				1,				loo::rhi::PF_XGXR8 			},
	{ TEXT ("R8G8B8A8_UINT"),	1,			1,			1,			4,			4,				0,				1,				loo::rhi::PF_R8G8B8A8_UINT	},
	{ TEXT ("R8G8B8A8_SNORM"),	1,			1,			1,			4,			4,				0,				1,				loo::rhi::PF_R8G8B8A8_SNORM	},
};

static struct FValidatePixelFormats
{
	FValidatePixelFormats ()
	{
		for (loo::int32 X = 0; X < ARRAY_COUNT (GPixelFormats); ++X)
		{
			// Make sure GPixelFormats has an entry for every unreal format
			assert (X == GPixelFormats[X].UnrealFormat);
		}
	}
} ValidatePixelFormats;

SIZE_T CalculateImageBytes (loo::uint32 SizeX, loo::uint32 SizeY, loo::uint32 SizeZ, loo::uint8 Format)
{
	if (Format == loo::rhi::PF_A1)
	{
		// The number of bytes needed to store all 1 bit pixels in a line is the width of the image divided by the number of bits in a byte
		loo::uint32 BytesPerLine = SizeX / 8;
		// The number of actual bytes in a 1 bit image is the bytes per line of pixels times the number of lines
		return sizeof (loo::uint8) * BytesPerLine * SizeY;
	}
	else if (SizeZ > 0)
	{
		return (SizeX / GPixelFormats[Format].BlockSizeX) * (SizeY / GPixelFormats[Format].BlockSizeY) * (SizeZ / GPixelFormats[Format].BlockSizeZ) * GPixelFormats[Format].BlockBytes;
	}
	else
	{
		return (SizeX / GPixelFormats[Format].BlockSizeX) * (SizeY / GPixelFormats[Format].BlockSizeY) * GPixelFormats[Format].BlockBytes;
	}
}
