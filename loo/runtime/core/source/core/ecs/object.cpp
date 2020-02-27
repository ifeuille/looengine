#include "core/privatemodule.h"
#include "core/ecs/object.h"
#ifndef __LOOREFLECT__
#include "core/ecs/generate/object.looprivate.h"
#endif

const char * loo::Object::name ()
{
	return m_Name;
}
