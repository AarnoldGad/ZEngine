#include "zepch.hpp"
#include <zengine/Common/Time/Timer.hpp>

namespace ze
{
	Timer::Timer()
		: m_startTime(Time::Now()), m_accumTime(Time::Null), m_paused(false) {}

	Time Timer::lap() const noexcept
	{
		return m_paused ? m_accumTime : (m_startTime - Time::Now() + m_accumTime);
	}

	Time Timer::restart() noexcept
	{
		Time elapsed = lap();

		m_startTime = Time::Now();
		m_accumTime = Time::Null;
		m_paused = false;

		return elapsed;
	}

	void Timer::pause() noexcept
	{
		m_accumTime += lap();
		m_paused = true;
	}

	void Timer::resume() noexcept
	{
		m_startTime = Time::Now();
		m_paused = false;
	}
}