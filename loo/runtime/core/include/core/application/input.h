#pragma once
#include "global/types.h"
#include "core/application/window.h"
#include "core/application/keycode.h"

namespace loo
{
	namespace core
	{

		class Input
		{
		public:
			Input (loo::core::Window& win);
			virtual ~Input ();
			void Init ();
			void CleanUp();
			void Update();

			//public callback
			void cb_CharEvent (Window const &, wchar_t);

			//for windows
#ifdef LOO_PLATFORM_WINDOWS
			
#else

#endif

		private:
			loo::core::Window* windowptr;

		};
	}
}