template<typename ReturnType, typename... Args>
ze::Connection<ReturnType(Args...)>::Connection() noexcept
   : m_signal(nullptr), m_receiver() {}

template<typename ReturnType, typename... Args>
ze::Connection<ReturnType(Args...)>::Connection(ConnectionType const& other) noexcept
   : m_signal(other.m_signal), m_receiver(other.m_receiver) {}

template<typename ReturnType, typename... Args>
ze::Connection<ReturnType(Args...)>::Connection(ConnectionType&& other) noexcept
   : m_signal(std::exchange(other.m_signal, nullptr)), m_receiver(std::move(other.m_receiver))
{
   if (m_signal) m_signal->replaceConnection(other, *this);
}

template<typename ReturnType, typename... Args>
ze::Connection<ReturnType(Args...)>::Connection(SignalType* signal, ReceiverType receiver) noexcept
   : m_signal(signal), m_receiver(std::move(receiver))
{
   if (m_signal) m_signal->connect(*this);
}

template<typename ReturnType, typename... Args>
ze::Connection<ReturnType(Args...)>& ze::Connection<ReturnType(Args...)>::operator=(ConnectionType const& other) noexcept
{
   m_signal = other.m_signal;
   m_receiver = other.m_receiver;
}

template<typename ReturnType, typename... Args>
ze::Connection<ReturnType(Args...)>& ze::Connection<ReturnType(Args...)>::operator=(ConnectionType&& other) noexcept
{
   m_signal = std::exchange(other.m_signal, nullptr);
   m_receiver = std::move(other.m_receiver);
   if (m_signal) m_signal->replaceConnection(other, *this);
}

template<typename ReturnType, typename... Args>
void ze::Connection<ReturnType(Args...)>::connect(SignalType* signal, ReceiverType receiver) noexcept
{
   disconnect();

   m_signal = signal;
   m_receiver = std::move(receiver);

   m_signal->connect(*this);
}

template<typename ReturnType, typename... Args>
void ze::Connection<ReturnType(Args...)>::disconnect() noexcept
{
   if (isConnected())
   {
      m_signal->disconnect(*this);
      m_signal = nullptr;
   }
}

template<typename ReturnType, typename... Args>
void ze::Connection<ReturnType(Args...)>::receiveSignal(Args&&... args)
{
   m_receiver(std::forward<Args>(args)...);
}

template<typename ReturnType, typename... Args>
ze::Connection<ReturnType(Args...)>::operator bool() const noexcept
{
   return isConnected();
}

template<typename ReturnType, typename... Args>
bool ze::Connection<ReturnType(Args...)>::isConnected() const noexcept
{
   return m_signal && std::find(m_signal->m_connections.begin(), m_signal->m_connections.end(), this) != m_signal->m_connections.end();
}

template<typename ReturnType, typename... Args>
ze::Connection<ReturnType(Args...)>::~Connection() noexcept
{
   disconnect();
}
