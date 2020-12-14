template<typename EventType, typename E>
ze::EventHandler<EventType, E>::EventHandler(CallbackType callback, ze::Priority priority)
	: EventCallback(priority), m_callback(callback) {}

template<typename EventType, typename E>
void ze::EventHandler<EventType, E>::operator()(Event& event)
{
	if (isEventReceivable(event))
		m_callback(*(dynamic_cast<EventType*>(&event)));
}

template<typename EventType, typename E>
inline bool ze::EventHandler<EventType, E>::isEventReceivable(Event& event) const
{
	return dynamic_cast<EventType*>(&event);
}
