#include "zepch.hpp"
#include <zengine/Event/Event.hpp>

void ze::Event::setCancelled(bool cancel)
{
   m_cancelled = cancel;
}