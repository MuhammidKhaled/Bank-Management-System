#include "bond.h"

Date Bond::purchaseDate() const {
	return purDate;
}

Date Bond::maturity() const {
	Date maturityDate = purDate;
	maturityDate.addMonths(months);
	return maturityDate;
}

double Bond::investment() const {
	return value;
}

float Bond::interestRate() const {
	return fixedInterestRate;
}

float Bond::numberOfYearsHeld(int currentMonth, int currentDay, int currentYear) const {
	int diffYears = currentYear - purDate.getYear();

	if (currentMonth == purDate.getMonth() && currentDay < purDate.getDay()) {
		diffYears--;
	}

	return diffYears;
}

double Bond::marketValue(int numberOfMonthsHeld) const {
	double interestFactor = pow(1 + fixedInterestRate / 12, numberOfMonthsHeld);
	return value * interestFactor;
}

double Bond::marketValue() const {
	Date currentDate;

	int numberOfYears = numberOfYearsHeld(currentDate.getMonth(), currentDate.getDay(), currentDate.getYear()) * 12;

	return marketValue(numberOfYears);
}

double Bond::marketValue(Date targetDate) const {
	int yearsHeld = numberOfYearsHeld(targetDate.getYear(), targetDate.getMonth(), targetDate.getDay()) * 12;

	if (targetDate == purDate) {
		return value;
	}
	else {
		return marketValue(yearsHeld);
	}
}


double Bond::finalWorth() const {
	return marketValue(months);
}

Bond::Bond() : value(0), purDate(), fixedInterestRate(0), months(0) {
}

Bond::Bond(double initialInvestment, int termInMonths, float rate)
	: value(initialInvestment), purDate(), fixedInterestRate(rate), months(termInMonths) {}

