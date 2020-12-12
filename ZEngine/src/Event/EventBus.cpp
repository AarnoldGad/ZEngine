#include "zepch.hpp"
#include <zengine/Event/EventBus.hpp>

void ze::EventBus::dispatchEvents()
{

}

void ze::EventBus::fireEvent(Event& event)
{

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