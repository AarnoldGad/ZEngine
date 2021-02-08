template<typename EventType>
void ze::EventBus::pushEvent(EventType&& event)
{
   m_eventStack.push_back(new EventType(std::move(event)));
}

template<typename EventType, typename... Args>
void ze::EventBus::pushEvent(Args&&... args)
{
   m_eventStack.push_back(new EventType(std::forward<Args>(args)...));
}
