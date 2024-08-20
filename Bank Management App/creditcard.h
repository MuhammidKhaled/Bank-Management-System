#ifndef CREDIT_H
#define CREDIT_H

#include "date.h"

/*The CreditCard class represents a credit card account with functionalities for managing
charges, payments, interest accrual, and credit limit modifications. It simulates real-world
credit card behavior, including: Balance Management, Charge Processing, Payment Processing,
Interest Calculations, Overdue Management, Credit Limit and Interest Rate.
*/

double calculateLateFee(double lateFeePercent, double balance);

class CreditCard {
public:
// Modifiers
	int postCharge(double chargeAmount);
	void makePayment(double paymentAmount);
	void chargeInterest();
		// postcondition: applies interest for overdue payments.
		// Usually this is daily
	void modifyLimit(double newLimit);
		// postcondition: Modifies the cards credit limit
	static void modifyRate(double newRate);
		/* postcondition: Modifies the card's interest rate.
		since every card has the same interest rate, ModifyRate()
		is static */
	void overDue();
		// postcondition: marks the card as being late on payments
	
//Accessors
	double currentBalance() const;
	double marketValue() const;
	double financeCharge() const;
	double availableCredit() const;
	double getInterestDue() const {
		return interestDue;
	}
	int isExpired() const;
	int isOverdue() const;

	CreditCard(double limit);
	CreditCard();
	~CreditCard();
private:
	double creditLimit;

	double balance;		  
	double overdueBalance; // Subject to finance charge

	double interestDue;   // Interest due on overdue balance.

	int overdue;     // This flag indicates whether or not the payment is overdue.

	static double interestRate; 	// Every credit card has the same rate.

	Date expirationDate;

	static Date lastInterestDate;
};
#endif // !CREDIT_H

