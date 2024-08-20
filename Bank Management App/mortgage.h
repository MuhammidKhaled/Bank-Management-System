#ifndef MORTGAGE_H
#define MORTGAGE_H

#include "creditcard.h"
#include "date.h"

#include <cmath>

class Mortgage
{
public:
// Modifiers
	void makeMonthlyPayment();
	int makeMonthlyPayment(CreditCard& sourceCreditCard);
// Accessors
	double rate() const;
		// Return the yearly interest rate.
	double getOriginalLoan() const;
	double getRemainingPrincipal() const;
	double getFixedMonthlyPayment() const;
		// Return the fixed monthly payment.
	double monthlyInterest() const;
		// Return the interest due that month.
	double interestPaidSoFar() const;
		// Accumulates the amount of interest paid.
	int mortgageTerm() const;
		// Returns the total number of years of the mortgage.
	double marketValue() const;
	Date startDate() const;
		// Returns the starting date of the mortgage.
//Backbone members
	Mortgage(double principal, double yearlyInterestRate, int lengthOfTermInYears);
	Mortgage();
	~Mortgage();
private:
	double fixedMonthlyPayment;
	double monthlyPayment;
	double originalLoan;
	double remainingPrincipal;
	double monthlyInterestPayment; // This varies month to month.
	double totalInterest; // Accumulates the interest paid so far.
	double monthlyInterestRate;
	int term;
	Date startingDate;  // Date the mortgage is constructed.
	double computeMonthlyPayment();
	static const int DEFAULT_TERM;
	static const double DEFAULT_LOAN;
	static const double DEFAULT_RATE;
};
#endif // !MORTGAGE_H
