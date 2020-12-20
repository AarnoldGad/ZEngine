#include "zepch.hpp"
#include <zengine/Common/Clock.hpp>

namespace ze
{
	Clock::Clock()
		: m_startTime(Time::Now()), m_accumTime(Time::Null), m_paused(false) {}

	Time Clock::lap() const noexcept
	{
		return m_paused ? m_accumTime : (m_startTime - Time::Now() + m_accumTime);
	}

	Time Clock::restart() noexcept
	{
		Time elapsed = lap();

		m_startTime = Time::Now();
		m_accumTime = Time::Null;
		m_paused = false;

		return elapsed;
	}

	void Clock::pause() noexcept
	{
		m_accumTime += lap();
		m_paused = true;
	}

	void Clock::resume() noexcept
	{
		m_startTime = Time::Now();
		m_paused = false;
	}
}