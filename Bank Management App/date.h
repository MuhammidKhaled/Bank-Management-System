#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <iostream>
#include <iomanip>

// Helper functions
	static int getMaxDay(int month, int year); // It calculates the maximum number of days in
	//a given month and year, with the considering of the leap year.
	static bool isValidDate(int day, int month, int year);
	static bool isLeapYear(int year);
class Date {
public:
// Getters
	int getDay() const;
	int getMonth() const;
	int getYear() const;
// Assignment operator
	Date operator = (const Date& d);
// Comparison operators. 
	int operator< (const Date& d) const;
	int operator> (const Date& d) const;
	int operator== (const Date& d) const;
	int operator!= (const Date& d) const;
// Arithmetic operators
// For the following members the parameter represents the number of days.
	Date operator+ (int ndays);
	Date operator- (int ndays);
	Date operator+= (int ndays);
	Date operator-= (int ndays);
	void addMonths(int monthsToAdd);
	// The next parameter is a date.
	int operator- (Date d); // d1- d2 is the number of days between d1 and d2.
	Date(int day, int month, int year);
	/* Precondition:
	using all four digits for entering the year.
	For example, Date d(23,12, 2023) represents Dec. 23, 2023.
	Postcondition:
	In case the parameters represent an invaild date, Date uses the
	current system date as the initialization value. The constructor is
	friendly. Date d(31,11,2023) is constructed as Dec. 1, 2023 since
	November has only 30 days.*/
	Date(); //initializes to the current date.
	~Date();
	friend std::ostream& operator<< (std::ostream& out, Date d);
	// Precondition: none
	// Postcondition: Displays d
	friend std::istream& operator>> (std::istream& in, Date d);
	/* Precondition:
			The user keys in three integers separated by blanks. The first
			integer is between 1 and 31 and represents the day. The second
			integer is between 1 and 12 and represents a month. The third
			is greater than 1.
	   Postcondition:
			If the input doesn't represent a valid date, then d is unchanged.
			*/
private:
	int day;
	int month;
	int year;
};
#endif // !DATE_H