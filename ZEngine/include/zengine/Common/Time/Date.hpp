/**
 * Date.hpp
 * 29 Jan 2021
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_DATE
#define ZE_DATE

#include <zebuild.hpp>

namespace ze
{
	class ZE_API Date
	{
	public:
		enum class Month : unsigned char
		{
			JANUARY = 0, FEBRUARY, MARCH, APRIL, MAY, JUNE,
			JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
		};

		static Date CurrentDate();

		static bool IsLeapYear(int year) noexcept;
		static bool Is30DaysMonth(Month month) noexcept;
		static bool Is31DaysMonth(Month month) noexcept;
		static int MonthMaxDays(Month month, int year) noexcept;

		void addDays(int days) noexcept;
		void addMonths(int months) noexcept;
		void addYears(int years) noexcept;
		void add(int days, int months, int years) noexcept;

		void setDay(int day) noexcept;
		void setMonth(Month month) noexcept;
		void setYear(int year) noexcept;

		int getDay() const noexcept;
		Month getMonth() const noexcept;
		int getYear() const noexcept;

		std::string format(std::string const& formatString) const noexcept;

		Date(int day, Month month, int year);
		Date();

		// Temp
		Date(Date const&) = delete;
		Date& operator=(Date const&) = delete;

	private:
		int m_day;
		Month m_month;
		int m_year;
	};

	Date::Month operator++(Date::Month& month, int) noexcept;
	Date::Month operator--(Date::Month& month, int) noexcept;

	Date::Month& operator++(Date::Month& month) noexcept;
	Date::Month& operator--(Date::Month& month) noexcept;
}

#include <inline/Common/Time/Date.inl>

#endif // ZE_DATE
