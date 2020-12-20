inline float ze::Time::asSeconds() const noexcept
{
	return static_cast<float>(m_microseconds / 1e-6);
}

inline int ze::Time::asSecondsInt() const noexcept
{
	return static_cast<int>(m_microseconds / 1e-6);
}

inline int ze::Time::asMilliseconds() const noexcept
{
	return static_cast<int>(m_microseconds / 1e-3);
}

inline int64_t ze::Time::asMicroseconds() const noexcept
{
	return m_microseconds;
}