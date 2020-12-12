#ifndef ZE_EVENTBUS
#define ZE_EVENTBUS

#include <zebuild.hpp>
#include <list>
#include <map>
#include <memory>
#include <zengine/Event/Event.hpp>
#include <zengine/Event/EventCallback.hpp>

namespace ze
{
   enum class Priority : unsigned int
   {
      VeryLow = FLAG(0),
      Low = FLAG(1),
      Normal = FLAG(2),
      High = FLAG(3),
      VeryHigh = FLAG(4)
   };

   class ZE_API EventBus
   {
   public:
      EventBus() = default;

      void dispatchEvents();
      void fireEvent(Event& event);

      template<typename EventType>
      void pushEvent(EventType&& event);
      template<typename EventType, typename... Args>
      void pushEvent(Args&&... args);

      void subscribe(EventCallback* callback);
      void unsubscribe(EventCallback* callback);

   private:
      std::list<std::unique_ptr<Event> > m_eventStack; // Raw Pointers more efficient ?
      std::map<Priority, std::list<EventCallback*>, std::greater<Priority> > m_callbacks;
   };
}

#include <zengine/Event/EventBus.inl>

#endif // ZE_EVENTBUS