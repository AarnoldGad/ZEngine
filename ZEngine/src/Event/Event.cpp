#include "zepch.hpp"
#include <zengine/Event/Event.hpp>

namespace ze
{
   Event::Event()
      : m_canceled(false) {}

   void Event::cancel()
   {
      m_canceled = true;
   }

   void Event::setCanceled(bool cancel)
   {
      m_canceled = cancel;
   }
}
