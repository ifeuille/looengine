#include "config.h"
#include "core/application/application.h"
#include "vkfg/vulkan/framework/vulkandeviceext.h"
#include "vkfg/vkfg.h"
#include "global/algorithms/stringutils.h"

class GraphicApp :public loo::core::Application
{
	// types
private:
	using TestFunc_t = bool (GraphicApp::*) ();
	using TestQueue_t = loo::Deque<loo::Pair< TestFunc_t, loo::uint >>;
	using DebugReport = loo::vkfg::VulkanDeviceExt::DebugReport;
	using VPipelineCompilerPtr = loo::SharedPtr< class loo::vkfg::VPipelineCompiler >;

	// variables
private:
	loo::vkfg::VulkanDeviceExt			_vulkan;
	loo::vkfg::FrameGraph				_frameGraph;
	VPipelineCompilerPtr				_pplnCompiler;
	loo::vkfg::SwapchainID				_swapchainId;

	TestQueue_t				_tests;
	loo::uint					_testInvocations = 0;
	loo::uint					_testsPassed = 0;
	loo::uint					_testsFailed;
	// helpers
private:

	bool Visualize (loo::StringView name) const;
	bool CompareDumps (loo::StringView filename) const;
	bool SavePNG (const loo::String &filename, const loo::vkfg::ImageView &imageData) const;

	template <typename Arg0, typename ...Args>
	inline void DeleteResources (Arg0 &arg0, Args& ...args);

	ND_ loo::Array<uint8_t>	CreateData (loo::BytesU size) const;

	ND_ static loo::String  GetFuncName (loo::StringView src);

	// implementation tests
private:
	bool Test_Draw1 ();

public:
	GraphicApp (const std::string& name,uint32_t appid, loo::core::ContextConfig setting);
	virtual ~GraphicApp ();
	virtual bool OnCreate ();
	virtual bool OnDestroy ();
	virtual bool OnSuspend ();
	virtual bool OnResume ();
	virtual bool OnRefresh ();
	virtual bool OnResize (uint32_t width, uint32_t height);
	virtual bool DoUpdateOverlay () ;
	virtual uint32_t DoUpdate (uint64_t pass);

private:


};

template <typename Arg0, typename ...Args>
inline void GraphicApp::DeleteResources (Arg0 &arg0, Args& ...args)
{
	_frameGraph->ReleaseResource (INOUT arg0);

	if constexpr (loo::CountOf<Args...> ())
		DeleteResources (std::forward<Args&> (args)...);
}



#	define TEST_NAME	GetFuncName( LOO_FUNCTION_NAME )
