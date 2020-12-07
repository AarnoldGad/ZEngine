#ifndef ZE_EVENTBUS
#define ZE_EVENTBUS

#include <zengine/Event/Event.hpp>

namespace ze
{
   class EventBus
   {
   public:
      EventBus() = default;

      void dispatchEvents();
      void fireEvent(Event& event);

      template<typename EventType>
      void pushEvent(EventType&& event);
      template<typename EventType, typename... Args>
      void pushEvent(Args&&... args);

   private:
      std::vector<std::unique_ptr<Event> > m_eventStack;

   };
}

#include <zengine/Event/EventBus.inl>

#endif // ZE_EVENTBUS