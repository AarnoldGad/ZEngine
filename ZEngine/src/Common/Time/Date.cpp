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

	int Date::MonthMaxDays(Month month, int year) noexcept
	{
		if (Is31DaysMonth(month))
			return 31;
		else if (Is30DaysMonth(month))
			return 30;
		else if (IsLeapYear(year))
			return 29;
		else
			return 28;
	}

	Date::Date()
		: m_day(1), m_month{}, m_year{} {}

	Date::Date(int day, Month month, int year)
		: m_day(day), m_month(month), m_year(year)
	{
		fixDayValidity();
	}

	void Date::setDay(int day) noexcept
	{
		m_day = day;
		fixDayValidity();
	}

	void Date::setMonth(Month month) noexcept
	{
		m_month = month;
		fixDayValidity();
	}

	void Date::setYear(int year) noexcept
	{
		m_year = year;
	}

	void Date::addDays(int days) noexcept
	{
		int effectiveDays = days + m_day;

		while (effectiveDays > MonthMaxDays(m_month, m_year))
		{
			effectiveDays -= MonthMaxDays(m_month, m_year);
			addMonths(1);
		}

		m_day = effectiveDays;
	}

	void Date::addMonths(int months) noexcept
	{
		std::div_t monthDiv = std::div(months + static_cast<int>(m_month), 12);

		m_year += monthDiv.quot;
		m_month = static_cast<Month>(monthDiv.rem);
		
		fixDayValidity();
	}

	void Date::addYears(int years) noexcept
	{
		m_year += years;

		fixDayValidity();
	}

	void Date::add(int days, int months, int years) noexcept
	{
		addYears(years);
		addMonths(months);
		addDays(days);
	}

	std::string Date::format(std::string const& formatString) const noexcept
	{
		std::stringstream formatted;

		std::tm time;
		time.tm_year = m_year - 1900;
		time.tm_mon = static_cast<int>(m_month);
		time.tm_mday = m_day;

		std::mktime(&time);
		formatted << std::put_time(&time, formatString.c_str());

		return formatted.str();
	}

	void Date::fixDayValidity() noexcept
	{
		if (m_day <= 0)
			m_day = 1;
		else if (m_day > 28)
		{
			if (m_month == Month::FEBRUARY && !IsLeapYear(m_year))
				m_day = 28;
			else if (m_month == Month::FEBRUARY && IsLeapYear(m_year))
				m_day = 29;
			else if (Is30DaysMonth(m_month))
				m_day = 30;
			else
				m_day = 31;
		}
	}

	Date::Month operator++(Date::Month& month, int) noexcept
	{
		Date::Month previousMonth = month;
		unsigned char incrementedMonth = static_cast<unsigned char>(month);

		incrementedMonth++;
		if (incrementedMonth > static_cast<unsigned char>(Date::Month::DECEMBER))
			incrementedMonth = 0;

		month = static_cast<Date::Month>(incrementedMonth);
		return previousMonth;
	}

	Date::Month operator--(Date::Month& month, int) noexcept
	{
		Date::Month previousMonth = month;
		unsigned char decrementedMonth = static_cast<unsigned char>(month);

		decrementedMonth--;
		if (decrementedMonth > static_cast<unsigned char>(Date::Month::DECEMBER))
			decrementedMonth = 0;

		month = static_cast<Date::Month>(decrementedMonth);
		return previousMonth;
	}

	Date::Month& operator++(Date::Month& month) noexcept
	{
		month++;
		return month;
	}

	Date::Month& operator--(Date::Month& month) noexcept
	{
		month--;
		return month;
	}
}