#ifndef ZE_EVENTHANDLER
#define ZE_EVENTHANDLER

#include <zengine/Event/Event.hpp>
#include <zengine/Event/EventCallback.hpp>

template<typename Type>
using enable_if_is_event = std::enable_if_t<std::is_base_of_v<ze::Event, Type> >;

namespace ze
{
   template<typename EventType, typename = enable_if_is_event<EventType>>
   class EventHandler : public EventCallback
   {
   public:
      using CallbackType = std::function<void(EventType&)>;

      explicit EventHandler(CallbackType callback, Priority priority = Priority::Normal);

      virtual void operator()(Event& event) override final;

   private:
      inline bool isEventReceivable(Event& event) const { return dynamic_cast<EventType*>(&event); }

      CallbackType m_callback;
      EventHandler(std::function<void(EventType&)> callback, ze::Priority priority);
   };
}

#include <zengine/Event/EventHandler.inl>

#endif // ZE_EVENTHANDLER