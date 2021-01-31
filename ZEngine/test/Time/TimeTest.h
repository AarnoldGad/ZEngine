#ifndef ZETEST_TIME
#define ZETEST_TIME

void TestTime()
{

}

void TestChrono()
{

}

void TestDate()
{
	// Spoiler : I Have no experience in Unit Testing
	assert(!ze::Date::IsLeapYear(2001));
	assert(!ze::Date::IsLeapYear(2006));
	assert(!ze::Date::IsLeapYear(2011));
	assert(ze::Date::IsLeapYear(2016));

	assert(ze::Date::Is31DaysMonth(ze::Date::Month::JANUARY));
	assert(ze::Date::Is30DaysMonth(ze::Date::Month::APRIL));
	assert(!ze::Date::Is30DaysMonth(ze::Date::Month::FEBRUARY));

	assert(ze::Date::MonthMaxDays(ze::Date::Month::FEBRUARY, 2012) == 29);
	assert(ze::Date::MonthMaxDays(ze::Date::Month::FEBRUARY, 2013) == 28);

	ze::Date date(30, ze::Date::Month::FEBRUARY, 2016);

	assert(date.getDay() == 29);

	date.addDays(1);

	assert(date.getDay() == 1);
	assert(date.getMonth() == ze::Date::Month::MARCH);

	date.setDay(31);
	date.addMonths(1);
	
	assert(date.getDay() == 30);
	assert(date.getMonth() == ze::Date::Month::APRIL);

	date.setMonth(ze::Date::FEBRUARY);
	date.setDay(31);

	assert(date.getDay() == 29);

	date.addYears(1);

	assert(date.getDay() == 28);

	date = ze::Date();

	assert(date.getDay() == 1 && date.getMonth() == ze::Date::JANUARY && date.getYear() == 0);

	date = ze::Date(5, ze::Date::NOVEMBER, 1955);

	assert(date.getDay() == 5 && date.getMonth() == ze::Date::NOVEMBER && date.getYear() == 1955);
}

#endif // ZETEST_TIME
