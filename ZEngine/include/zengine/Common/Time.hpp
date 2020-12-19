#ifndef ZE_TIME
#define ZE_TIME

#include <zebuild.hpp>

namespace ze
{
	class ZE_API Time
	{
	public:
		static Time const Null;
		static Time GetTime() noexcept;

		static Time Seconds(int seconds) noexcept;
		static Time Milliseconds(int milliseconds) noexcept;
		static Time Microseconds(int64_t microseconds) noexcept;

		int asSeconds() const noexcept;
		int asMilliseconds() const noexcept;
		int64_t asMicroseconds() const noexcept;

		void operator=(Time const& other) noexcept;

		Time& operator+=(Time const& other) noexcept;

		Time& operator-=(Time const& other) noexcept;

		Time& operator*=(float factor) noexcept;
		Time& operator*=(int64_t factor) noexcept;

		Time& operator/=(float factor) noexcept;
		Time& operator/=(int64_t factor) noexcept;

		Time& operator%=(Time const& mod) noexcept;

		explicit Time(int64_t microseconds = 0);

	private:
		int64_t m_microseconds;
	};

	ZE_API bool operator==(Time const& left, Time const& right) noexcept;
	ZE_API bool operator!=(Time const& left, Time const& right) noexcept;
	ZE_API bool operator<=(Time const& left, Time const& right) noexcept;
	ZE_API bool operator>=(Time const& left, Time const& right) noexcept;
	ZE_API bool operator<(Time const& left, Time const& right) noexcept;
	ZE_API bool operator>(Time const& left, Time const& right) noexcept;

	ZE_API Time operator+(Time left, Time right) noexcept;

	ZE_API Time operator-(Time left, Time right) noexcept;
	ZE_API Time operator-(Time time) noexcept;

	ZE_API Time operator*(Time left, float factor) noexcept;
	ZE_API Time operator*(float factor, Time right) noexcept;
	ZE_API Time operator*(Time left, int64_t factor) noexcept;
	ZE_API Time operator*(int64_t factor, Time right) noexcept;

	ZE_API Time operator/(Time left, Time right) noexcept;
	ZE_API Time operator/(Time left, float factor) noexcept;
	ZE_API Time operator/(Time left, int64_t factor) noexcept;

	ZE_API Time operator%(Time left, Time right) noexcept;
}

#endif // ZE_TIME
