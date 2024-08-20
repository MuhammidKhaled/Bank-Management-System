#ifndef BOND_H
#define BOND_H

#include "date.h"

class Bond {
public:
//Accessor Members
	Date purchaseDate() const;
	Date maturity() const;
	double investment() const;
	float interestRate() const;
//Implementor Members
	double marketValue(int numberOfMonthsHeld) const;
	double marketValue() const; // Returns the market value as today's Date.
	double marketValue(Date targetDate) const; // Returns the market value on the targetDate
	double finalWorth() const;
	float numberOfYearsHeld(int currentMonth, int currentDay, int currentYear) const;
//Backbone Members
	Bond();
	Bond(double initialInvestment, int termInMonths, float rate);
private:
	double value; // Original cost of the investment
	Date purDate;
	float fixedInterestRate;
	int months; // Number of months to maturity from date of purchase.
};
#endif // !BOND_H
