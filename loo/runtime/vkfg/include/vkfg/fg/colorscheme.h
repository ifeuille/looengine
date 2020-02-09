
#pragma once

#include "global/types.h"

namespace loo
{
	namespace LOOColorScheme
	{

		//
		// Default Dark
		//
		struct DefaultDark
		{
			static constexpr math::RGBA8u		RenderPass = math::HtmlColor::OrangeRed;
			static constexpr math::RGBA8u		Compute = math::HtmlColor::MediumBlue;
			static constexpr math::RGBA8u		DeviceLocalTransfer = math::HtmlColor::Green;
			static constexpr math::RGBA8u		HostToDeviceTransfer = math::HtmlColor::BlueViolet;
			static constexpr math::RGBA8u		DeviceToHostTransfer = math::HtmlColor::BlueViolet;
			static constexpr math::RGBA8u		Present = math::HtmlColor::Red;
			static constexpr math::RGBA8u		RayTracing = math::HtmlColor::Lime;
			static constexpr math::RGBA8u		BuildRayTracingStruct = math::HtmlColor::Lime;

			static constexpr math::RGBA8u		Draw = math::HtmlColor::Bisque;
			static constexpr math::RGBA8u		DrawMeshes = math::HtmlColor::Bisque;
			static constexpr math::RGBA8u		CustomDraw = math::HtmlColor::Bisque;

			static constexpr math::RGBA8u		CmdSubBatchBackground = math::RGBA8u{ 0x28, 0x28, 0x28, 0xFF };
			static constexpr math::RGBA8u		CmdSubBatchLavel = math::RGBA8u{ 0xdc, 0xdc, 0xdc, 0xFF };
			static constexpr math::RGBA8u		CmdBatchBackground = math::RGBA8u{ 0x18, 0x18, 0x18, 0xFF };
			static constexpr math::RGBA8u		CmdBatchLabel = math::RGBA8u{ 0xdc, 0xdc, 0xdc, 0xFF };
			static constexpr math::RGBA8u		TaskLabel = math::HtmlColor::White;
			static constexpr math::RGBA8u		ResourceBackground = math::HtmlColor::Silver;
			//static constexpr math::RGBA8u	ResourceToResourceEdge	= math::HtmlColor::Silver;
			static constexpr math::RGBA8u		BarrierGroupBorder = math::HtmlColor::Olive;
			static constexpr math::RGBA8u		GroupBorder = math::HtmlColor::DarkGray;
			static constexpr math::RGBA8u		TaskDependencyEdge = math::RGBA8u{ 0xd3, 0xd3, 0xd3, 0xFF };

			static constexpr math::RGBA8u		Debug = math::HtmlColor::Pink;		// all invalid data will be drawn with this color

			// old-style barriers
			static constexpr bool		EnabledOldStyleBarriers = false;
			static constexpr math::RGBA8u		LayoutBarrier = math::HtmlColor::Yellow;
			static constexpr math::RGBA8u		WriteAfterWriteBarrier = math::HtmlColor::DodgerBlue;
			static constexpr math::RGBA8u		WriteAfterReadBarrier = math::HtmlColor::LimeGreen;
			static constexpr math::RGBA8u		ReadAfterWriteBarrier = math::HtmlColor::Red;
		};


	}

	using ColorScheme = LOOColorScheme::DefaultDark;

}	// loo
