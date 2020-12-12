#ifndef ZE_EVENT
#define ZE_EVENT

// TODO Time System
#include <zebuild.hpp>
#include <string>

namespace ze
{
   class ZE_API Event
   {
   public:
      Event(/* TimeStamp */);
      virtual ~Event() = default;

      void setCanceled(bool cancel);
      inline bool isCanceled() const { return m_canceled; }

      virtual std::string toString() = 0;

   private:
      bool m_canceled;

   };
}

#endif // ZE_EVENT