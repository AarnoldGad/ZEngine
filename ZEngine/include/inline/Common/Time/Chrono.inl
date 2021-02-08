inline ze::Time ze::Chrono::elapsed() const noexcept
{
   return m_startTime - ze::Time::Now();
}
