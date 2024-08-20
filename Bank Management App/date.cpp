#include "date.h"

// Getters
int Date::getDay() const {
	return day;
}

int Date::getMonth() const {
	return month;
}

int Date::getYear() const {
	return year;
}
// Assignment operator
Date Date::operator=(const Date& d) {
	day = d.day;
	month = d.month;
	year = d.year;
	return *this;
}

// Comparison operators
int Date::operator<(const Date& d) const {
	if (year < d.year) return 1;
	if (year == d.year && month < d.month) return 1;
	if (year == d.year && month == d.month && day < d.day) return 1;
	return 0;
}

int Date::operator>(const Date& d) const {
	if (year > d.year) return 1;
	if (year == d.year && month > d.month) return 1;
	if (year == d.year && month == d.month && day > d.day) return 1;
	return 0;
}

int Date::operator==(const Date& d) const {
	return (year == d.year && month == d.month && day == d.day);
}

int Date::operator!=(const Date& d) const {
	return ~(*this == d);
}

// Arithmetic operators
Date Date::operator+(int ndays) {
	Date result = *this;
	result.day += ndays;
	if (result.day > getMaxDay(result.month, result.year)) {
		result.day -= getMaxDay(result.month, result.year);
		result.month++;
		if (result.month > 12) {
			result.month = 1;
			result.year++;
		}
	}
	return result;
}

Date Date::operator-(int ndays) {
	Date result = *this;
	result.day -= ndays;
	if (result.day < 1) {
		result.month--;
		if (result.month < 1) {
			result.month = 12;
			result.year--;
		}
		result.day += getMaxDay(result.month, result.year);
	}
	return result;
}

Date Date::operator+=(int ndays) {
	Date d = *this + ndays;
	if (d.day > getMaxDay(d.month, d.year)) {
		d.day -= getMaxDay(d.month, d.year);
		d.month++;
		if (d.month > 12) {
			d.month = 1;
			d.year++;
		}
	}
	return d;
}

Date Date::operator-=(int ndays) {
	*this = *this - ndays;
	return *this;
}

int Date::operator-(Date d) {
	if (*this == d) {
		return 0;
	}

	int diff = 0;
	Date later = *this, earlier = d;
	if (*this < d) {
		later = d;
		earlier = *this;
	}

	while (later > earlier) {
		later -= 1;
		diff++;
	}

	return diff;
}
void Date::addMonths(int monthsToAdd) {
	int initialMonth = month;
	int initialYear = year;

	month += monthsToAdd;
	year += month / 12;
	month %= 12;

	if (month == 0) {
		month = 12;
		year--;
	}

	int maxDaysThisMonth = getMaxDay(month, year);
	if (day > maxDaysThisMonth) {
		day = maxDaysThisMonth;
	}

	if (initialMonth != month || initialYear != year) {
		day = std::min(day, getMaxDay(month, year));
	}
}

// Constructors
Date::Date(int d, int m, int y) {
	year = y;
	month = m;
	day = d;
	if (!isValidDate(day, month, year)) {
		time_t now = time(0);
		tm localtm;
		localtime_s(&localtm, &now);

		day = localtm.tm_mday;
		month = localtm.tm_mon + 1;
		year = localtm.tm_year + 1900;
	}
}

Date::Date() {
	time_t now = time(0);
	tm localtm;
	localtime_s(&localtm, &now);
	day = localtm.tm_mday;
	month = localtm.tm_mon + 1;
	year = localtm.tm_year + 1900;
}

// Destructor
Date::~Date() {}

// Stream operators
std::ostream& operator<<(std::ostream& out, Date d) {
	out << d.month << "/" << d.day << "/" << d.year;
	return out;
}

std::istream& operator>> (std::istream& in, Date d) {
	in >> d.day >> d.month >> d.year;
	if (!isValidDate(d.day, d.month, d.year)) {
		in.clear(std::ios::failbit);
	}
	return in;
}

// Helper functions
int getMaxDay(int month, int year) {
	int maxDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && isLeapYear(year))
		return 29;
	return maxDay[month - 1];
}

bool isValidDate(int day, int month, int year) {
	if (year < 1) {
		return false;
	}

	// Checking for valid month (between 1 and 12)
	if (month < 1 || month > 12) {
		return false;
	}

	// Checking for valid day based on the month
	int maxDay = getMaxDay(month, year);
	if (day < 1 || day > maxDay) {
		return false;
	}

	return true;
}

bool isLeapYear(int year) {
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}