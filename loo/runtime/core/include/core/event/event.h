#pragma once
#include "core/dllexporter.h"
#include <type_traits>
#include <cstddef>
#include <atomic>
#include <list>
#include <unordered_map>
#include "core/object/object.h"
#include "looreflect/looreflect.h"//must include this
#include "looreflect/looreflectmanager.h"

namespace loo
{
	namespace core
	{
		struct LOOCLASS () CORE_EXPORT Event : public Object
		{
			LOOMETA_OBJECT;
			/**
			* 0x1~0x0fff for system event
			*/
			LOOPROPERTY (Serialized)
			int typeID;
			LOOPROPERTY (Serialized)
			int flags;
			LOOPROPERTY (Serialized)
			bool canceled;

			LOOPROPERTY (Serialized)
			Object* sender;

			Event (const char* name_);
			virtual ~Event ();

		};


		class LOOCLASS () CORE_EXPORT EventListener
		{
			LOOMETA_OBJECT;
		public:
			LOOFUNCTION ()
			void listen (int eventType);
			LOOFUNCTION ()
			void unlisten (int eventType);
			LOOFUNCTION ()
			virtual bool onEvent (Event*);

		};

		class LOOCLASS () CORE_EXPORT EventManager final : public Object
		{
			LOOMETA_OBJECT;
		public:
			EventManager ();

			virtual ~EventManager ();

			//LOOFUNCTION ()
			static EventManager& Get ();

			LOOFUNCTION ()
			bool sendEvent (Event* e);

			LOOFUNCTION ()
			void postEvent (Event* e);

			LOOFUNCTION ()
			void listen (int eventid, EventListener* listener);

			LOOFUNCTION ()
			void unlisten (int eventid, EventListener* listener);

		private:
			typedef std::list< EventListener*> ListenersList;
			typedef std::unordered_map<int, ListenersList> EventListenersMap;

		private:

			EventListenersMap eventListenersMap;
		};



	}
}

#ifndef __LOOREFLECT__
#include "core/event/generate/event.loo.h"
#endif