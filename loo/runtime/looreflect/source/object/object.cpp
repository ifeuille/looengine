#include "privatemodule.h"
#include "object/object.h"
#ifndef __LOOREFLECT__
#include "object/generate/object.looprivate.h"
#endif

const char * loo::Object::name ()
{
	return m_Name;
}
