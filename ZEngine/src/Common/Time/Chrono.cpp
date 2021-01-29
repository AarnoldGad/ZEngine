#include "zepch.hpp"
#include <zengine/Common/Time/Chrono.hpp>

namespace ze
{
	Chrono::Chrono()
		: m_startTime(Time::Now()), m_accumTime(Time::Null), m_paused(false) {}

	Time Chrono::lap() const noexcept
	{
		return m_paused ? m_accumTime : (m_startTime - Time::Now() + m_accumTime);
	}

	Time Chrono::restart() noexcept
	{
		Time elapsed = lap();

		m_startTime = Time::Now();
		m_accumTime = Time::Null;
		m_paused = false;

		return elapsed;
	}

	void Chrono::pause() noexcept
	{
		m_accumTime += lap();
		m_paused = true;
	}

	void Chrono::resume() noexcept
	{
		m_startTime = Time::Now();
		m_paused = false;
	}
}