#include "zepch.hpp"
#include <zengine/Common/Time/Chrono.hpp>

namespace ze
{
   Chrono::Chrono()
      : m_startTime(Time::Now()), m_accumTime(Time::Null), m_paused(false) {}

   Time Chrono::lap() const noexcept
   {
      return m_paused ? m_accumTime : (elapsed() + m_accumTime);
   }

   Time Chrono::restart() noexcept
   {
      Time totalTimeElapsed = elapsed() + m_accumTime;

      m_startTime = Time::Now();
      m_accumTime = Time::Null;
      m_paused = false;

      return totalTimeElapsed;
   }

   void Chrono::pause() noexcept
   {
      m_accumTime += elapsed(); // Accumulate elapsed time so we can reset startTime
      m_paused = true;
   }

   void Chrono::resume() noexcept
   {
      m_startTime = Time::Now();
      m_paused = false;
   }
}
