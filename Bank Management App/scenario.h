#ifndef SCENARIO_H
#define SCENARIO_H

#include "account.h"
#include "creditcard.h"
#include "mortgage.h"

class Scenario {
public:
	void run();
	Scenario(double wOB, double hOB, double loan, int term, double rate, double cl);
	Scenario();
	~Scenario();
private:
// data members
	Account hAccount, wAccount;
	CreditCard jointCard;
	Mortgage homeMortgage;
// private member functions for internal use by the Scenario factory
	void displayMenu();
	void cardTransaction();
	void accountTransaction();
	void mortgageTransaction();
	void displayFinances();
};
#endif // !SCENARIO_H


