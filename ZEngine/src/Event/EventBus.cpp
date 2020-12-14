#include "zepch.hpp"
#include <zengine/Event/EventBus.hpp>
#include <zengine/Event/EventCallback.hpp>

void ze::EventBus::dispatchEvents()
{
	for (auto& it : m_eventStack)
		fireEvent(*it);

	clearStack();
}

void ze::EventBus::fireEvent(Event& event)
{
	for (auto& it : m_callbacks)
		for (auto& callback : it.second)
			(*callback)(event);
}

void ze::EventBus::subscribe(EventCallback* callback)
{
	m_callbacks[callback->getPriority()].push_back(callback);
	m_callbacks[callback->getPriority()].sort();
	m_callbacks[callback->getPriority()].unique();
}

void ze::EventBus::unsubscribe(EventCallback* callback)
{
	m_callbacks[callback->getPriority()].remove(callback);
}

void ze::EventBus::clearStack()
{
	for (auto& it : m_eventStack)
		delete it;

	m_eventStack.clear();
}

ze::EventBus::~EventBus()
{
	clearStack();
}
