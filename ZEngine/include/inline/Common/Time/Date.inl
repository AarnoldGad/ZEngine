inline bool ze::Date::IsLeapYear(int year) noexcept
{
	return !(year % 4);
}

inline bool ze::Date::Is30DaysMonth(Month month) noexcept
{
	return month == Month::APRIL     ||
			 month == Month::JUNE      ||
			 month == Month::SEPTEMBER ||
			 month == Month::NOVEMBER;
}

inline bool ze::Date::Is31DaysMonth(Month month) noexcept
{
	return month == Month::JANUARY ||
			 month == Month::MARCH   ||
			 month == Month::MAY     ||
			 month == Month::JULY    ||
			 month == Month::AUGUST  ||
			 month == Month::OCTOBER ||
			 month == Month::DECEMBER;
}

inline int ze::Date::getDay() const noexcept { return m_day; }

inline ze::Date::Month ze::Date::getMonth() const noexcept { return m_month; }

inline int ze::Date::getYear() const noexcept { return m_year; }