#include "zepch.hpp"
#include <zengine/Common/Time.hpp>

namespace ze
{
	Time const Time::Null = Time();

	Time::Time(int64_t microseconds)
		: m_microseconds(microseconds) {}

	int Time::asSeconds() const noexcept
	{
		return static_cast<int>(m_microseconds / 1000000);
	}

	int Time::asMilliseconds() const noexcept
	{
		return static_cast<int>(m_microseconds / 1000);
	}

	int64_t Time::asMicroseconds() const noexcept
	{
		return m_microseconds;
	}

	Time Time::GetTime() noexcept
	{
		std::timespec ts;
		if (std::timespec_get(&ts, TIME_UTC))
			return Time((ts.tv_sec * 1000000) + (ts.tv_nsec / 1000));

		return Time::Null;
	}

	Time Time::Seconds(int seconds) noexcept
	{
		return Time(static_cast<int64_t>(seconds) * 1000000);
	}

	Time Time::Milliseconds(int milliseconds) noexcept
	{
		return Time(static_cast<int64_t>(milliseconds) * 1000);
	}

	Time Time::Microseconds(int64_t microseconds) noexcept
	{
		return Time(microseconds);
	}

	void Time::operator=(Time const& other) noexcept
	{
		m_microseconds = other.asMicroseconds();
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
		m_microseconds = static_cast<int64_t>(static_cast<float>(m_microseconds) * factor);
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
			m_microseconds = static_cast<int64_t>(static_cast<float>(m_microseconds) / factor);
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

	bool operator==(Time const& left, Time const& right) noexcept
	{
		return left.asMicroseconds() == right.asMicroseconds();
	}

	bool operator!=(Time const& left, Time const& right) noexcept
	{
		return left.asMicroseconds() != right.asMicroseconds();
	}

	bool operator<=(Time const& left, Time const& right) noexcept
	{
		return left.asMicroseconds() <= right.asMicroseconds();
	}

	bool operator>=(Time const& left, Time const& right) noexcept
	{
		return left.asMicroseconds() >= right.asMicroseconds();
	}

	bool operator<(Time const& left, Time const& right) noexcept
	{
		return left.asMicroseconds() < right.asMicroseconds();
	}

	bool operator>(Time const& left, Time const& right) noexcept
	{
		return left.asMicroseconds() > right.asMicroseconds();
	}

	Time operator+(Time left, Time right) noexcept
	{
		return left += right;
	}

	Time operator-(Time left, Time right) noexcept
	{
		return left -= right;
	}

	Time operator-(Time time) noexcept
	{
		return Time(-time.asMicroseconds());
	}

	Time operator*(Time left, float factor) noexcept
	{
		return left *= factor;
	}

	Time operator*(float factor, Time right) noexcept
	{
		return right *= factor;
	}

	Time operator*(Time left, int64_t factor) noexcept
	{
		return left *= factor;
	}

	Time operator*(int64_t factor, Time right) noexcept
	{
		return right *= factor;
	}

	Time operator/(Time left, Time right) noexcept
	{
		if (right != Time::Null)
			return Time(left.asMicroseconds() / right.asMicroseconds());
		return Time::Null;
	}

	Time operator/(Time left, float factor) noexcept
	{
		return left /= factor;
	}

	Time operator/(Time left, int64_t factor) noexcept
	{
		return left /= factor;
	}

	Time operator%(Time left, Time right) noexcept
	{
		return left %= right;
	}
}
