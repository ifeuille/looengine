#include "graphicapp.h"
#include "global/stream/filestream.h"
#include "global/algorithms/stringparser.h"
#include "pipeline_compiler/VPipelineCompiler.h"

extern void UnitTest_VResourceManager (const loo::vkfg::FrameGraph &fg);

namespace loo
{
	namespace vkfg
	{
		static constexpr uint	UpdateAllReferenceDumps = false;
	}
}
GraphicApp::GraphicApp (const std::string & name, uint32_t appid, loo::core::ContextConfig setting)
	:loo::core::Application(name,appid, setting)
{
	_tests.push_back (std::make_pair (&GraphicApp::Test_Draw1, 1));

}

GraphicApp::~GraphicApp ()
{

}

bool GraphicApp::OnCreate ()
{
	// initialize vulkan device
	{


		//loo::ArrayView<loo::vkfg::VulkanDevice::QueueCreateInfo> queueCIList (
		//	{
		//		{VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_SPARSE_BINDING_BIT | VK_QUEUE_PRESENT_BIT, 0.0f },
		//	{ VK_QUEUE_COMPUTE_BIT,  0.0f },
		//	{ VK_QUEUE_TRANSFER_BIT, 0.0f }
		//	}
		//);
		CHECK_ERR (_vulkan.Create (main_wnd->GetVulkanSurface (), "Test", "FrameGraph", VK_API_VERSION_1_2,
			"",
			loo::ArrayView<loo::vkfg::VulkanDevice::QueueCreateInfo> (
			 { 
				 { VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_SPARSE_BINDING_BIT | loo::vkfg::VK_QUEUE_PRESENT_BIT, 0.0f },
				 { VK_QUEUE_COMPUTE_BIT,  0.0f },
				 { VK_QUEUE_TRANSFER_BIT, 0.0f } 
			 }
			 ),
			loo::vkfg::VulkanDevice::GetRecomendedInstanceLayers (),
			loo::vkfg::VulkanDevice::GetRecomendedInstanceExtensions (),
			loo::vkfg::VulkanDevice::GetAllDeviceExtensions_v110 ()
		));

		// this is a test and the test should fail for any validation error
		_vulkan.CreateDebugUtilsCallback (loo::vkfg::DebugUtilsMessageSeverity_All,
			[](const loo::vkfg::VulkanDeviceExt::DebugReport &rep) { CHECK_FATAL (not rep.isError); });
	}

	// setup device info
	loo::vkfg::VulkanDeviceInfo					vulkan_info;
	loo::vkfg::IFrameGraph::SwapchainCreateInfo_t	swapchain_info;
	{
		vulkan_info.instance = loo::BitCast<loo::vkfg::InstanceVk_t> (_vulkan.GetVkInstance ());
		vulkan_info.physicalDevice = loo::BitCast<loo::vkfg::PhysicalDeviceVk_t> (_vulkan.GetVkPhysicalDevice ());
		vulkan_info.device = loo::BitCast<loo::vkfg::DeviceVk_t> (_vulkan.GetVkDevice ());

		loo::vkfg::VulkanSwapchainCreateInfo	swapchain_ci;
		swapchain_ci.surface = loo::BitCast<loo::vkfg::SurfaceVk_t> (_vulkan.GetVkSurface ());
		swapchain_ci.surfaceSize = main_wnd->GetSize ();
		swapchain_info = swapchain_ci;

		for (auto& q : _vulkan.GetVkQueues ())
		{
			loo::vkfg::VulkanDeviceInfo::QueueInfo	qi;
			qi.handle = loo::BitCast<loo::vkfg::QueueVk_t> (q.handle);
			qi.familyFlags = loo::BitCast<loo::vkfg::QueueFlagsVk_t> (q.flags);
			qi.familyIndex = q.familyIndex;
			qi.priority = q.priority;
			qi.debugName = "";

			vulkan_info.queues.push_back (qi);
		}
	}

	// initialize framegraph
	{
		_frameGraph = loo::vkfg::IFrameGraph::CreateFrameGraph (vulkan_info);
		CHECK_ERR (_frameGraph);

		_swapchainId = _frameGraph->CreateSwapchain (swapchain_info, loo::Default, "Window");
		CHECK_ERR (_swapchainId);
	}

	// add glsl pipeline compiler
	{
		_pplnCompiler = loo::global::MakeSharedPtr<loo::vkfg::VPipelineCompiler> (vulkan_info.instance, vulkan_info.physicalDevice, vulkan_info.device);
		_pplnCompiler->SetCompilationFlags (loo::vkfg::EShaderCompilationFlags::Quiet |
			loo::vkfg::EShaderCompilationFlags::ParseAnnotations |
			loo::vkfg::EShaderCompilationFlags::UseCurrentDeviceLimits);

		_frameGraph->AddPipelineCompiler (_pplnCompiler);
	}

	UnitTest_VResourceManager (_frameGraph);
	return true;
}

bool GraphicApp::OnDestroy ()
{
	_pplnCompiler = null;

	if (_swapchainId and _frameGraph)
	{
		_frameGraph->ReleaseResource (INOUT _swapchainId);
	}

	if (_frameGraph)
	{
		_frameGraph->Deinitialize ();
		_frameGraph = null;
	}

	_vulkan.Destroy ();

	return true;
}
bool GraphicApp::OnSuspend ()
{
	return true;
}
bool GraphicApp::OnResume ()
{
	return true;
}
bool GraphicApp::OnRefresh ()
{
	if (_tests.empty ())
	{
		Quit ();
		return false;
	}
	TestFunc_t	func = _tests.front ().first;
	const loo::uint	max_invoc = _tests.front ().second;
	bool		passed = (this->*func)();

	if (_testInvocations == 0)
	{
		_testsPassed += loo::uint (passed);
		_testsFailed += loo::uint (not passed);
	}

	if ((not passed) or (++_testInvocations >= max_invoc))
	{
		_tests.pop_front ();
		_testInvocations = 0;

		// reset
		loo::String	temp;
		_frameGraph->DumpToGraphViz (OUT temp);
		_frameGraph->DumpToString (OUT temp);
	}
	return true;
}

bool GraphicApp::OnResize (uint32_t width, uint32_t height)
{
	if (width == 0 || height == 0)
	{
		return false;
	}
	CHECK (_frameGraph->WaitIdle ());

	loo::vkfg::VulkanSwapchainCreateInfo	swapchain_info;
	swapchain_info.surface = loo::BitCast<loo::vkfg::SurfaceVk_t> (_vulkan.GetVkSurface ());
	swapchain_info.surfaceSize = loo::math::uint2(width,height);

	_swapchainId = _frameGraph->CreateSwapchain (swapchain_info, _swapchainId.Release ());
	CHECK_FATAL (_swapchainId);
	return true;
}
bool GraphicApp::DoUpdateOverlay ()
{
	return true;
}
uint32_t GraphicApp::DoUpdate (uint64_t pass)
{
	LOO_UNUSED (pass);
	return true;
}
bool GraphicApp::Visualize (loo::StringView name_) const
{
#	if defined(LOO_GRAPHVIZ_DOT_EXECUTABLE) and defined(FG_STD_FILESYSTEM)

	String	str;
	CHECK_ERR (_frameGraph->DumpToGraphViz (OUT str));

	auto	path = std::filesystem::path{ FG_TEST_GRAPHS_DIR }.append (name_.data ()).replace_extension ("dot");

	CHECK (GraphViz::Visualize (str, path, "png", false, true));

#	else
	LOO_UNUSED (name_);
	// not supported
#	endif
	return false;
}

bool GraphicApp::CompareDumps (loo::StringView filename) const
{
	loo::String	fname{ LOO_TEST_DUMPS_DIR };	
	fname.append ("/");
	fname.append (filename.data ());
	fname.append (".txt");

	loo::String	right;
	CHECK_ERR (_frameGraph->DumpToString (OUT right));

	// override dump
	if (loo::vkfg::UpdateAllReferenceDumps)
	{
		loo::FileWStream		wfile{ fname };
		CHECK_ERR (wfile.IsOpen ());
		CHECK_ERR (wfile.Write (loo::StringView{ right }));
		return true;
	}

	// read from file
	loo::String	left;
	{
		loo::FileRStream		rfile{ fname };
		CHECK_ERR (rfile.IsOpen ());
		CHECK_ERR (rfile.Read (size_t (rfile.Size ()), OUT left));
	}

	size_t		l_pos = 0;
	size_t		r_pos = 0;
	loo::math::uint2		line_number;
	loo::StringView	line_str[2];

	const auto	LeftValid = [&l_pos, &left]() { return l_pos < left.length (); };
	const auto	RightValid = [&r_pos, &right]() { return r_pos < right.length (); };

	const auto	IsEmptyLine = [](loo::StringView str)
	{
		for (auto& c : str) {
			if (c != '\n' and c != '\r' and c != ' ' and c != '\t')
				return false;
		}
		return true;
	};


	// compare line by line
	for (; LeftValid () and RightValid (); )
	{
		// read left line
		do {
			loo::StringParser::ReadLineToEnd (left, INOUT l_pos, OUT line_str[0]);
			++line_number[0];
		} while (IsEmptyLine (line_str[0]) and LeftValid ());

		// read right line
		do {
			loo::StringParser::ReadLineToEnd (right, INOUT r_pos, OUT line_str[1]);
			++line_number[1];
		} while (IsEmptyLine (line_str[1]) and RightValid ());

		if (line_str[0] != line_str[1])
		{
			RETURN_ERR ("in: " << filename.data () << "\n\n"
				<< "line mismatch:" << "\n(" << loo::ToString (line_number[0]).c_str () << "): " << line_str[0].data ()
				<< "\n(" << loo::ToString (line_number[1]).c_str() << "): " << line_str[1].data ());
		}
	}

	if (LeftValid () != RightValid ())
	{
		RETURN_ERR ("in: " << filename.data() << "\n\n" << "sizes of dumps are not equal!");
	}

	return true;
}

bool GraphicApp::SavePNG (const loo::String & filename, const loo::vkfg::ImageView & imageData) const
{
#ifdef LOO_ENABLE_LODEPNG
	LodePNGColorType	colortype = LodePNGColorType (-1);
	uint				bitdepth = 0;
	uint				bitperpixel = 0;

	switch (imageData.Format ())
	{
	case EPixelFormat::RGBA8_UNorm:
	case EPixelFormat::BGRA8_UNorm:
		colortype = LodePNGColorType::LCT_RGBA;
		bitdepth = 8;
		bitperpixel = 4 * 8;
		break;

	case EPixelFormat::RGBA16_UNorm:
		colortype = LodePNGColorType::LCT_RGBA;
		bitdepth = 16;
		bitperpixel = 4 * 16;
		break;

	case EPixelFormat::RGB8_UNorm:
	case EPixelFormat::BGR8_UNorm:
		colortype = LodePNGColorType::LCT_RGB;
		bitdepth = 8;
		bitperpixel = 3 * 8;
		break;

	case EPixelFormat::RGB16_UNorm:
		colortype = LodePNGColorType::LCT_RGB;
		bitdepth = 16;
		bitperpixel = 3 * 16;
		break;

	case EPixelFormat::R8_UNorm:
		colortype = LodePNGColorType::LCT_GREY;
		bitdepth = 8;
		bitperpixel = 8;
		break;

	case EPixelFormat::R16_UNorm:
		colortype = LodePNGColorType::LCT_GREY;
		bitdepth = 16;
		bitperpixel = 16;
		break;

	default:
		RETURN_ERR ("unsupported pixel format!");
	}


	uint	err = 0;

	if (imageData.Parts ().size () == 1 and imageData.RowPitch () == imageData.RowSize ())
	{
		err = lodepng::encode (filename, imageData.data (), imageData.Dimension ().x, imageData.Dimension ().y, colortype, bitdepth);
	}
	else
	{
		const size_t	row_size = size_t (imageData.RowSize ());
		Array<uint8_t>	pixels;		pixels.resize (row_size * imageData.Dimension ().y);

		for (uint y = 0; y < imageData.Dimension ().y; ++y)
		{
			auto	row = imageData.GetRow (y);

			std::memcpy (pixels.data () + (row_size * y), row.data (), row_size);
		}

		err = lodepng::encode (filename, pixels.data (), imageData.Dimension ().x, imageData.Dimension ().y, colortype, bitdepth);
	}

	CHECK_ERR (err == 0);
	//const char * error_text = lodepng_error_text( err );

	return true;
#else
	LOO_UNUSED (filename);
	LOO_UNUSED (imageData);
	return false;
#endif
}


ND_ loo::Array<uint8_t> GraphicApp::CreateData (loo::BytesU size) const
{
	loo::Array<uint8_t>	arr;
	arr.resize (size_t (size));

	return arr;
}

ND_ loo::String GraphicApp::GetFuncName(loo::StringView src)
{
	size_t	pos = src.find_last_of("::");

	if (pos != loo::StringView::npos)
		return loo::String{ src.substr(pos + 1) };
	else
		return loo::String{ src };
}
