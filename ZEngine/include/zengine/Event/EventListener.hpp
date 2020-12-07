#ifndef ZE_EVENTLISTENER
#define ZE_EVENTLISTENER

#include <type_traits>
#include <functional>
#include <zengine/Event/Event.hpp>

namespace ze
{
   template<typename Type>
   using enable_if_is_event = std::enable_if_t<std::is_base_of_v<ze::Event, Type> >;

   template<typename EventType, typename = enable_if_is_event<EventType> >
   class EventListener
   {
   public:
      EventListener(std::function<void(EventType&)> callback);

   private:
      std::function<void(EventType&)> m_callback;

   };
}

#include <zengine/Event/EventListener.inl>

#endif // ZE_EVENTLISTENER