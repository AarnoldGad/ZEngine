#include "zepch.hpp"
#include <zengine/Common/Time/Time.hpp>

namespace ze
{
	Time const Time::Null = Time();

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
		return Time(static_cast<int64_t>(milliseconds * 1e+3));
	}

	Time Time::Microseconds(int64_t microseconds) noexcept
	{
		return Time(microseconds);
	}

	Time Time::operator-() const noexcept
	{
		return Microseconds(-m_microseconds);
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
		m_microseconds = Seconds(asSeconds() * factor).asMicroseconds();
		return *this;
	}

	Time& Time::operator*=(int64_t factor) noexcept
	{
		m_microseconds *= factor;
		return *this;
	}

	Time& Time::operator/=(float factor) noexcept
	{
		if (factor >= 0.f)
			m_microseconds = Seconds(asSeconds() / factor).asMicroseconds();
		return *this;
	}

	Time& Time::operator/=(int64_t factor) noexcept
	{
		if (factor)
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
		return Microseconds(asMicroseconds() + other.asMicroseconds());
	}

	Time Time::operator-(Time const& other) const noexcept
	{
		return Microseconds(asMicroseconds() - other.asMicroseconds());
	}

	Time Time::operator*(float factor) const noexcept
	{
		return Seconds(asSeconds() * factor);
	}

	Time Time::operator*(int64_t factor) const noexcept
	{
		return Microseconds(asMicroseconds() * factor);
	}

	Time Time::operator/(Time const& other) const noexcept
	{
		return Microseconds(asMicroseconds()) / other.asMicroseconds();
	}

	Time Time::operator/(float factor) const noexcept
	{
		return Seconds(asSeconds()) /= factor;
	}

	Time Time::operator/(int64_t factor) const noexcept
	{
		return Microseconds(asMicroseconds()) /= factor;
	}

	Time Time::operator%(Time const& other) const noexcept
	{
		return Microseconds(asMicroseconds() % other.asMicroseconds());
	}
}
