template<typename EventType>
void ze::EventBus::pushEvent(EventType&& event)
{
   m_eventStack.emplace_back(std::make_unique<EventType>(std::move(event)));
}

template<typename EventType, typename... Args>
void ze::EventBus::pushEvent(Args&&... args)
{
   m_eventStack.emplace_back(std::make_unique<EventType>(std::forward<Args>(args)...));
}