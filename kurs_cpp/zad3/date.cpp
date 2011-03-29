#include "date.h"

Date::Date() : day(1), month(1), year(2000) // pobierz date systemowa
{
}

Date::Date(const int d, const int m, const int y)
	: day(d), month(m), year(y)
{
	validate();
}

bool Date::przestepny() const
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

void Date::validate() const
{
	if(day < 1)
	{
		std::stringstream ss;
		ss << "Date " << *this << " has invalid day.";
		throw std::string(ss.str());
	}
	if(month > 12 || month < 1)
	{
		std::stringstream ss;
		ss << "Date " << *this << " has invalid month.";
		throw std::string(ss.str());
	}
	if(day > days_of_month[przestepny()][month])
	{
		std::stringstream ss;
		ss << "Date " << *this << " has invalid day (>" << days_of_month[przestepny()][month] << ").";
		throw std::string(ss.str());
	}
	if(year <= 1582 && month <= 10 && day < 15)
	{
		std::stringstream ss;
		ss << "Date " << *this << " is not gregorian.";
		throw std::string(ss.str());
	}
}

int Date::days_from_begining() const
{
	const int przestepnych_lat_do_stycznia = (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400; // wzor wlaczen i wylaczen
	const int zwyklych_lat_do_stycznia = year - 1 - przestepnych_lat_do_stycznia;

	return przestepnych_lat_do_stycznia * 366 +
		zwyklych_lat_do_stycznia * 365 +
		days_from_beg[przestepny()][month] + day;
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	os << d.year << '/' << d.month << '/' << d.day;
	return os;
}

int Date::diff(const Date& from, const Date& to)
{
	return to.days_from_begining() - from.days_from_begining();
}

const int Date::days_from_beg[2][13] =
{
	{0,31,59,90,120,151,181,212,243,273,304,334,365}, // lata zwyk³e
	{0,31,60,91,121,152,182,213,244,274,305,335,366} // lata przestêpne
};

const int Date::days_of_month[2][13] =
{
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};
