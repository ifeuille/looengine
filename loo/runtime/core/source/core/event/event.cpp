#include "core/privatemodule.h"
#include "core/event/event.h"
#ifndef __LOOREFLECT__
#include "core/event/generate/event.looprivate.h"
#endif
#include <mutex>
#include <unordered_map>
#include <shared_mutex>
#include <algorithm>
#include "global/utils/log.h"

loo::core::Event::Event ( const char* name_)
	:Object (name_),
	sender (nullptr),
	typeID (-1),
	flags (0),
	canceled (false)
{}

loo::core::Event::~Event ()
{
	sender = nullptr;
	typeID = -1;
	flags = 0;
	canceled = false;
}

void loo::core::EventListener::listen (int eventType)
{
	EventManager::Get ().listen (eventType, this);
}

void loo::core::EventListener::unlisten (int eventType)
{
	EventManager::Get ().unlisten (eventType, this);
}

bool loo::core::EventListener::onEvent (Event*)
{
	utils::slog.i << "INFO:EventListener::onEvent called" << utils::io::endl;
	return false;
}

loo::core::EventManager::EventManager ()
	:Object("g_EventManager")
{

}

loo::core::EventManager::~EventManager ()
{
}

loo::core::EventManager& loo::core::EventManager::Get ()
{
	static EventManager* instance = nullptr;
	static std::mutex singleton_mutex_mmgr;
	if (!instance)
	{
		std::unique_lock<std::mutex> lock (singleton_mutex_mmgr);
		if (!instance)
		{
			instance = new EventManager ();
		}
	}
	return *instance;
}

bool loo::core::EventManager::sendEvent (Event * e)
{
	if (!e)return false;
	bool ret = false;
	auto itlist = eventListenersMap.find (e->typeID);
	if (itlist == eventListenersMap.end ())
	{
		return ret;
	}
	for (auto it = itlist->second.begin (); it != itlist->second.end (); ++it)
	{
		if (*it)
		{
			ret  = ret & (*it)->onEvent (e);
		}
		else
		{
			utils::slog.e << "EventManager::sendEvent nullptr" << utils::io::endl;
		}
	}
	return ret;
}

void loo::core::EventManager::postEvent (Event * e)
{
	sendEvent (e);//TODO
}

void loo::core::EventManager::listen (int eventid, loo::core::EventListener * listener)
{
	ListenersList& lst = eventListenersMap[eventid];
	auto result = std::find (lst.begin (), lst.end (), listener);
	if (result == lst.end ())
	{
		lst.push_back (listener);
	}
}

void loo::core::EventManager::unlisten (int eventid, loo::core::EventListener * listener)
{
	ListenersList& lst = eventListenersMap[eventid];
	auto result = std::find (lst.begin (), lst.end (), listener);
	if (result != lst.end ())
	{
		lst.erase (result);
	}
}
