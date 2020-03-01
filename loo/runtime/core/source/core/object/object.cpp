#include "core/privatemodule.h"
#include "core/object/object.h"
#ifndef __LOOREFLECT__
#include "core/object/generate/object.looprivate.h"
#endif

const char * loo::Object::name ()
{
	return m_Name;
}
