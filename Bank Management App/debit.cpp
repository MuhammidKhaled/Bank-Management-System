#include "debit.h"

const double START_UP_FEE = 1.00; // Fee for constructing a DebitCard
const double INCREMENT_FEE = 0.25; // Fee for adding funds to an existing DebitCard

double DebitCard::outstandingFunds = 0.0; // Construction of static data member

int DebitCard::cash(double amount) {
	if (amount > balance)
		return 0;
	else {
		outstandingFunds -= amount;
		balance -= amount;
		return 1;
	}
}

void DebitCard::operator+= (double amount) {
	double fee;
	if (balance <= 0.0)
		fee = START_UP_FEE;
	else
		fee = INCREMENT_FEE;

	double temp = balance + amount - fee;

	if (temp >= 0) {
		outstandingFunds -= balance;
		balance = temp;
		outstandingFunds += balance;
	}
	else {// The amount being added to the card cannot cover the fee.
	}
}

DebitCard& DebitCard::operator= (const DebitCard& rhs) {
	if (this == &rhs) {
	}
	else {
		outstandingFunds -= balance;
		balance = rhs.balance;
		outstandingFunds += balance;
	}
	return *this;
}

double DebitCard::retrieveBalance() {
	return balance;
}

double DebitCard::outstandingDebt() {
	return outstandingFunds;
}

double DebitCard::startUpFee() {
	return START_UP_FEE;
}

double DebitCard::incrementFee() {
	return INCREMENT_FEE;
}

// Conversion operator to convert from a DebitCard to an Account
DebitCard::operator Account() {
	//Construct an Account with an opening balance equal to the card's cash value.
	return Account(balance);
}

// Constructor to convert from an Account to a DebitCard
DebitCard::DebitCard(Account anExistingAccount): 
	balance(anExistingAccount.retrieveBalance() - START_UP_FEE)
{
	outstandingFunds += balance;
}

DebitCard::DebitCard(double purchaseAmount) :balance(purchaseAmount - START_UP_FEE) {
	outstandingFunds += balance;
}

DebitCard::DebitCard(const DebitCard& anExitingCard) :balance(anExitingCard.balance)
{
	outstandingFunds += balance;
}

DebitCard::DebitCard() :balance(0.0)
{
}

DebitCard::~DebitCard() {
	outstandingFunds -= balance;
}
