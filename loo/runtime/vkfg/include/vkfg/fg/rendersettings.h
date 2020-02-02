#ifndef LOO_VKFG_RENDERSETTINGS_H
#define LOO_VKFG_RENDERSETTINGS_H
#include "global/global.h"

namespace loo
{
	namespace vkfg
	{
		struct RenderSettings
		{
			bool	hide_win;
			bool	full_screen;
			int		left;
			int		top;
			int		width;
			int		height;
			//EPixelFormat color_fmt;
			//EPixelFormat depth_stencil_fmt;
			uint32_t sample_count;
			uint32_t sample_quality;
			uint32_t sync_interval;
			bool hdr;
			bool fft_lens_effects;
			bool ppaa;
			bool gamma;
			bool color_grading;

			float bloom;
			bool blue_shift;

			bool keep_screen_on;

			//StereoMethod stereo_method;
			float stereo_separation;

			//DisplayOutputMethod display_output_method;
			uint32_t paper_white;
			uint32_t display_max_luminance;

			float max_dpi_scale;

			std::vector<std::pair<std::string, std::string>> options;

			RenderSettings ()
				:hide_win (false),
				full_screen (false),
				left (64),
				top (64),
				width (720),
				height (680)
				//color_fmt ()
			{

			}

		};

	}
}


#endif