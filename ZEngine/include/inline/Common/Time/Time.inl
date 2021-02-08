inline float ze::Time::asSeconds() const noexcept
{
   return static_cast<float>(m_microseconds) / 1000000.0F;
}

inline int ze::Time::asSecondsInt() const noexcept
{
   return static_cast<int>(m_microseconds / 1000000);
}

inline int32_t ze::Time::asMilliseconds() const noexcept
{
   return static_cast<int32_t>(m_microseconds / 1000);
}

inline int64_t ze::Time::asMicroseconds() const noexcept
{
   return m_microseconds;
}
