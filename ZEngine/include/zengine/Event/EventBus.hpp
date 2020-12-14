/**
 * EventBus.hpp
 * 12 Dec 2020
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020 Gaétan Jalin
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
#ifndef ZE_EVENTBUS
#define ZE_EVENTBUS

#include <zebuild.hpp>
#include <zengine/Event/Event.hpp>
#include <zengine/Common/Priority.hpp>

namespace ze
{
	class EventCallback;

	class ZE_API EventBus
	{
	public:
		template<typename EventType>
		void pushEvent(EventType&& event);

		template<typename EventType, typename... Args>
		void pushEvent(Args&&... args);

		void subscribe(EventCallback* callback);
		void unsubscribe(EventCallback* callback);

		void dispatchEvents();
		void fireEvent(Event& event);

		EventBus() = default;
		~EventBus();

	private:
		void clearStack();

		std::list<Event*> m_eventStack;
		std::map<Priority, std::list<EventCallback*>, std::greater<Priority> > m_callbacks;
	};
}

#include <inline/Event/EventBus.inl>

#endif // ZE_EVENTBUS
