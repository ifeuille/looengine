#ifndef LOO_CORE_OBJECT_H
#define LOO_CORE_OBJECT_H
#pragma once

#include "looreflect/looreflect.h"//must include this
#include "looreflect/looreflectmanager.h"
#include "global/template/refcounting.h"
#include "core/dllexporter.h"

namespace loo
{
	class LOOCLASS() CORE_EXPORT Object:public loo::global::TRefCountPtr<Object>
	{
		LOOMETA_OBJECT;
	public:
		Object(const char* name_)
		:m_Name(name_), NumRefs (0)
		{
		}
		
		virtual ~Object () { assert (!NumRefs); }

		uint32 AddRef () const
		{
			return uint32 (++NumRefs);
		}

		uint32 Release () const
		{
			uint32 Refs = uint32 (--NumRefs);
			if (Refs == 0)
			{
				delete this;
			}
			return Refs;
		}

		uint32 GetRefCount () const
		{
			return uint32 (NumRefs);
		}

		LOOFUNCTION ()
		const char* name ();

	private:
		//LOOPROPERTY(Serialized, cstring)
		const char* m_Name;
		mutable int32 NumRefs;
	};
}
#ifndef __LOOREFLECT__
#include "core/object/generate/object.loo.h"
#endif
#endif