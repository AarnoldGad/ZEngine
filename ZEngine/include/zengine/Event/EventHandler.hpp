/**
 * EventHandler.hpp
 * 12 Dec 2020
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
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
      bool isEventReceivable(Event& event) const;

      CallbackType m_callback;
   };
}

#include <inline/Event/EventHandler.inl>

#endif // ZE_EVENTHANDLER
