#ifndef ZE_EVENTCALLBACK
#define ZE_EVENTCALLBACK

#include <zebuild.hpp>
#include <zengine/Event/Event.hpp>
#include <zengine/Event/EventBus.hpp>

namespace ze
{
   class ZE_API EventCallback
   {
   public:
      explicit EventCallback(Priority priority);

      virtual void operator()(Event&) = 0;

      inline Priority getPriority() const { return m_priority; }

   private:
      Priority m_priority;
   };
}

#endif // ZE_EVENTCALLBACK