#ifndef ZE_TIME
#define ZE_TIME

#include <zebuild.hpp>

namespace ze
{
	class ZE_API Time
	{
	public:
		static Time const Null;

		static Time Now() noexcept;
		static Time Seconds(float seconds) noexcept;
		static Time Milliseconds(int milliseconds) noexcept;
		static Time Microseconds(int64_t microseconds) noexcept;

		float asSeconds() const noexcept;
		int asSecondsInt() const noexcept;
		int asMilliseconds() const noexcept;
		int64_t asMicroseconds() const noexcept;

		Time operator-() const noexcept;

		Time& operator+=(Time const& other) noexcept;

		Time& operator-=(Time const& other) noexcept;

		Time& operator*=(float factor) noexcept;
		Time& operator*=(int64_t factor) noexcept;

		Time& operator/=(float factor) noexcept;
		Time& operator/=(int64_t factor) noexcept;

		Time& operator%=(Time const& mod) noexcept;

		bool operator==(Time const& other) const noexcept;
		bool operator!=(Time const& other) const noexcept;
		bool operator<=(Time const& other) const noexcept;
		bool operator>=(Time const& other) const noexcept;
		bool operator<(Time const& other) const noexcept;
		bool operator>(Time const& other) const noexcept;

		Time operator+(Time const& other) const noexcept;

		Time operator-(Time const& other) const noexcept;

		Time operator*(float factor) const noexcept;
		Time operator*(int64_t factor) const noexcept;

		Time operator/(Time const& other) const noexcept;
		Time operator/(float factor) const noexcept;
		Time operator/(int64_t factor) const noexcept;

		Time operator%(Time const& other) const noexcept;

		Time();

	private:
		explicit Time(int64_t microseconds);

		int64_t m_microseconds;
	};
}

#endif // ZE_TIME
