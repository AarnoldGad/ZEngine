#ifndef ZE_EVENT
#define ZE_EVENT

// TODO Time System

namespace ze
{
   class Event
   {
   public:
      Event(/* TimeStamp */) = default;
      virtual ~Event() = default;

      void setCancelled(bool cancel);
      inline bool isCancelled() const { return m_cancelled; }

      virtual std::string toString() = 0;

   private:
      bool m_cancelled;

   };
}

#endif // ZE_EVENT