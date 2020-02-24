#pragma once
#include "core/dllexporter.h"
#include "global/global.h"
#include "core/application/keycode.h"


namespace loo
{
	namespace core
	{


		class CORE_EXPORT SystemEventBus final
		{
		public:
			typedef sigslot::signal< SAppEvent&> SysEvent;
		public:

			SystemEventBus () {}
			virtual ~SystemEventBus () {}

			SysEvent& GetTypeBus (SAppEventType type) { return type_handlers[type]; }
			bool Dispatch (SAppEvent& event);


		private:

			std::unordered_map<SAppEventType, SysEvent> type_handlers;
		};
	}
}