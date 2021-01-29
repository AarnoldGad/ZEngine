#include "zepch.hpp"
#include <zengine/Common/Time/Date.hpp>

namespace ze
{
	Date Date::CurrentDate()
	{
		std::time_t t = time(0);
		std::tm tm;
		localtime_s(&tm, &t);
		return Date(tm.tm_mday, static_cast<Date::Month>(tm.tm_mon), tm.tm_year);
	}

	Date::Date(int day, Month month, int year)
		: m_month(month), m_year(year)
	{
		setDay(day);
	}

	void Date::setDay(int day) noexcept
	{
		if (day <= 28)
			m_day = day;
		else if (m_month == Month::FEBRUARY && IsLeapYear(m_year))
			m_day = 29;
		else if (Is30DaysMonth(m_month))
			m_day = 30;
		else
			m_day = 31;
	}
}