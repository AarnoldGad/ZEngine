#include "zepch.hpp"
#include <zengine/Event/EventBus.hpp>
#include <zengine/Event/EventCallback.hpp>

namespace ze
{
   void EventBus::dispatchEvents()
   {
      for (auto& it : m_eventStack)
         fireEvent(*it);

      clearStack();
   }

   void EventBus::fireEvent(Event& event)
   {
      for (auto& it : m_callbacks)
         for (auto& callback : it.second)
            if (!event.isCanceled())
               (*callback)(event);
            else
               return;
   }

   void EventBus::subscribe(EventCallback* callback)
   {
      m_callbacks[callback->getPriority()].push_back(callback);
      m_callbacks[callback->getPriority()].sort();
      m_callbacks[callback->getPriority()].unique();
   }

   void EventBus::unsubscribe(EventCallback* callback)
   {
      m_callbacks[callback->getPriority()].remove(callback);
   }

   void EventBus::clearStack()
   {
      for (auto& it : m_eventStack)
         delete it;

      m_eventStack.clear();
   }

   EventBus::~EventBus()
   {
      clearStack();
   }
}
