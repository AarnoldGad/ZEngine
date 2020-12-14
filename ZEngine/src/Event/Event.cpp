#include "zepch.hpp"
#include <zengine/Event/Event.hpp>

ze::Event::Event()
   : m_canceled(false) {}

void ze::Event::cancel()
{
   m_canceled = true;
}

void ze::Event::setCanceled(bool cancel)
{
   m_canceled = cancel;
}
