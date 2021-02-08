template<typename ReturnType, typename... Args>
ze::Signal<ReturnType(Args...)>::Signal() noexcept
   : m_connections{} {}

template<typename ReturnType, typename... Args>
ze::Connection<ReturnType(Args...)> ze::Signal<ReturnType(Args...)>::connect(ReceiverType receiver) noexcept
{
   return ConnectionType(this, receiver);
}

template<typename ReturnType, typename... Args>
void ze::Signal<ReturnType(Args...)>::connect(ConnectionType& connection) noexcept
{
   if (connection.m_signal != this) return; // TODO Error Handling ?

   m_connections.push_back(&connection);
}

template<typename ReturnType, typename... Args>
void ze::Signal<ReturnType(Args...)>::disconnect(ConnectionType& connection) noexcept
{
   m_connections.remove(&connection);
}

template<typename ReturnType, typename... Args>
void ze::Signal<ReturnType(Args...)>::clearConnections() noexcept
{
   for (auto& connection : m_connections)
      connection->disconnect();
}

template<typename ReturnType, typename... Args>
void ze::Signal<ReturnType(Args...)>::emit(Args&&... args)
{
   for (auto& connection : m_connections)
      connection->receiveSignal(std::forward<Args>(args)...);
}

template<typename ReturnType, typename... Args>
void ze::Signal<ReturnType(Args...)>::replaceConnection(ConnectionType& oldConnection, ConnectionType& newConnection) noexcept
{
   auto it = std::find(m_connections.begin(), m_connections.end(), &oldConnection);
   if (it != m_connections.end())
      it = &newConnection;
}

template<typename ReturnType, typename... Args>
ze::Signal<ReturnType(Args...)>::~Signal() noexcept
{
   clearConnections();
}
