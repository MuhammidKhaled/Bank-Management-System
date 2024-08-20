#ifndef DEBIT_H
#define DEBIT_H

#include "account.h"

class Account;
class DebitCard {
public:
// Modifier Members
	int cash(double amount); // Deducts amount from card
	void operator += (double incrementAmount);
		// Increments cash supply
		// There is a small fee for this service.
	DebitCard& operator= (const DebitCard& rhs); 
		// Single or multiple assignment operator
		// Turns the object enacting the method into a copy of rhs.
// Accessor Members
	double retrieveBalance(); // Returns the remaining balance of existing card.
	static double outstandingDebt(); // Returns the total of all the balances of existing cards.
	double startUpFee(); // Returns the fee for constructing a new card.
	double incrementFee(); // Returns the fee for the fee for the adding funds to an existing card.
// Conversion Members
	operator Account(); // Type cast from a DebitCard object to an Account object.
// Constructors
	DebitCard(double purchasePrice); // Creates a DebitCard
	DebitCard(Account anExistingAccount); // Conversion constructor.
		// Type casts from an Account object to a DebitCard object.
	DebitCard(const DebitCard& anExistingAccount); // Copy constructor
	DebitCard();  
		// Default constructor
		// Creates a DebitCard with no money.
	~DebitCard(); 
		// Destroys card.
		// Updates outstanding total debt on the existing cards.
private:
	double balance; // Cash value of the card.
	static double outstandingFunds; // Total debt on all cards.
};
#endif // !DEBIT_H
