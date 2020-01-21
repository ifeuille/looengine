#include "core/application/window.h"
#include "core/context.h"
#include "global/global.h"
#include "global/mutex.h"

namespace loo
{
	namespace core
	{
		void Window::UpdateDpiScale (float scale)
		{
			dpi_scale = scale;

			float const max_dpi_scale = Context::Get ().Config ().graphic_settings.max_dpi_scale;
			if (max_dpi_scale > 0)
			{
				effective_dpi_scale = min (max_dpi_scale, dpi_scale);
			}
			else
			{
				effective_dpi_scale = dpi_scale;
			}
		}
	}
}