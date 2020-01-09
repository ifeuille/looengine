#ifndef LOO_GLOBAL_OBJECT_H
#define LOO_GLOBAL_OBJECT_H
#include "looreflect/dllexport.h"
#include "looreflect/looreflect.h"
#include "global/template/refcounting.h"
using namespace looreflect;

namespace loo
{
	LOOCLASS() LOOREFLECT_EXPORT Object:public loo::global::FRefCountedObject<Object>
	{
	public:
		LOOMETA_OBJECT;

		Object(const char* name_)
		:m_Name(name_)
		{
		}

		LOOFUNCTION()
		const char* name() { return m_Name; }


	private:
		LOOPROPERTY(Serialized, cstring)
		const char* m_Name;
		LOOPROPERTY(Serialized)
		mutable int m_NumRefs;
	};
}

#endif