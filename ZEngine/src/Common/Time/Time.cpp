#include "zepch.hpp"
#include <zengine/Common/Time/Time.hpp>

namespace ze
{
   Time const Time::Null = Time(0);

   Time::Time()
      : m_microseconds{} {}

   Time::Time(int64_t microseconds)
      : m_microseconds(microseconds) {}

   Time Time::Now() noexcept
   {
      std::timespec ts;
      if (std::timespec_get(&ts, TIME_UTC))
         return Seconds(static_cast<float>(ts.tv_sec)) + Microseconds(ts.tv_nsec / 1000);

      return Time::Null;
   }

   Time Time::Seconds(float seconds) noexcept
   {
      return Time(static_cast<int64_t>(seconds * 1e+6));
   }

   Time Time::Milliseconds(int milliseconds) noexcept
   {
      return Time(static_cast<int64_t>(milliseconds) * 1000);
   }

   Time Time::Microseconds(int64_t microseconds) noexcept
   {
      return Time(microseconds);
   }

   Time Time::operator-() const noexcept
   {
      return -asMicroseconds();
   }

   Time& Time::operator+=(Time const& other) noexcept
   {
      m_microseconds += other.asMicroseconds();
      return *this;
   }

   Time& Time::operator-=(Time const& other) noexcept
   {
      m_microseconds -= other.asMicroseconds();
      return *this;
   }

   Time& Time::operator*=(float factor) noexcept
   {
      m_microseconds = static_cast<int64_t>(static_cast<float>(asMicroseconds()) * factor);
      return *this;
   }

   Time& Time::operator*=(int64_t factor) noexcept
   {
      m_microseconds *= factor;
      return *this;
   }

   Time& Time::operator/=(float factor)
   {
      m_microseconds = static_cast<int64_t>(static_cast<float>(asMicroseconds()) / factor);
      return *this;
   }

   Time& Time::operator/=(int64_t factor)
   {
      m_microseconds /= factor;
      return *this;
   }

   Time& Time::operator%=(Time const& other) noexcept
   {
      m_microseconds %= other.asMicroseconds();
      return *this;
   }

   bool Time::operator==(Time const& other) const noexcept
   {
      return asMicroseconds() == other.asMicroseconds();
   }

   bool Time::operator!=(Time const& other) const noexcept
   {
      return asMicroseconds() != other.asMicroseconds();
   }

   bool Time::operator<=(Time const& other) const noexcept
   {
      return asMicroseconds() <= other.asMicroseconds();
   }

   bool Time::operator>=(Time const& other) const noexcept
   {
      return asMicroseconds() >= other.asMicroseconds();
   }

   bool Time::operator<(Time const& other) const noexcept
   {
      return asMicroseconds() < other.asMicroseconds();
   }

   bool Time::operator>(Time const& other) const noexcept
   {
      return asMicroseconds() > other.asMicroseconds();
   }

   Time Time::operator+(Time const& other) const noexcept
   {
      return asMicroseconds() + other.asMicroseconds();
   }

   Time Time::operator-(Time const& other) const noexcept
   {
      return asMicroseconds() - other.asMicroseconds();
   }

   Time Time::operator*(float factor) const noexcept
   {
      return static_cast<int64_t>(static_cast<float>(asMicroseconds()) * factor);
   }

   Time Time::operator*(int64_t factor) const noexcept
   {
      return asMicroseconds() * factor;
   }

   Time Time::operator/(Time const& other) const
   {
      return asMicroseconds() / other.asMicroseconds();
   }

   Time Time::operator/(float factor) const
   {
      return static_cast<int64_t>(static_cast<float>(asMicroseconds()) / factor);
   }

   Time Time::operator/(int64_t factor) const
   {
      return asMicroseconds() / factor;
   }

   Time Time::operator%(Time const& other) const noexcept
   {
      return asMicroseconds() % other.asMicroseconds();
   }
}
