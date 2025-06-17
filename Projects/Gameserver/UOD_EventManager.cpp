#include "UOD_EventManager.h"
#include "UOD_Event.h"
#include "UOD_Arena.h"
#include "UOD_Mission.h"
#include "Basedef.h"

TOD_EventManager::TOD_EventManager()
{
	_events[TOD_EventType::Mission] = std::make_unique<TOD_Mission>(800ms);
}

std::map<TOD_EventType, std::unique_ptr<TOD_Event>>& TOD_EventManager::GetEvents() 
{
	return _events;
}

TOD_Event* TOD_EventManager::GetEvent(TOD_EventType type) 
{
	auto eventIt = _events.find(type);
	if (eventIt == std::end(_events))
		return nullptr;

	return &*eventIt->second;
}

TOD_EventItem* TOD_EventManager::GetEventItem(TOD_EventType type)
{
	auto eventIt = _events.find(type);
	if (eventIt == std::end(_events))
		return nullptr;

	return static_cast<TOD_EventItem*>(&*eventIt->second);
}