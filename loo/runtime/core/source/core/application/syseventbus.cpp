#include "core/application/syseventbus.h"

bool loo::core::SystemEventBus::Dispatch (SAppEvent * e)
{
	SysEvent& bus = GetTypeBus (e->type);
	bus (e);
	return true;
}
