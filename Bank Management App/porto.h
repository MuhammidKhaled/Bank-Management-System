#ifndef PORTO_H
#define PORTO_H

#include "cd.h"
#include "bond.h"
#include "creditcard.h"
#include "date.h"


class Portfolio {
public:
// Modifier Members
	int attachBond(Bond* locationOfExistingBond);
	int attachCD(CertificateOfDeposit* locationOfExistingCD);

	// The following 2 detach members detach the investments from the portfolio, but doesn't
	//destroy the investment.
	void detachBond();
	void detachCd();

// Accessor Members
	std::string& socialSecurityNumber();
	Bond* bondLocation() const;
	CertificateOfDeposit* cDLocation() const;
	CreditCard* cardLocation() const;

	// The next 3 methods query the Portfolio about its investments.
	int hasCD() const;
	int hasBond() const;
	int hasCreditCard() const;

// Implementor Members
	double totalWorth(Date targetDate) const;
	double totalWorth() const; // Current totat worth

// Backbone Members Assignment
	Portfolio& operator= (const Portfolio& rhs);

	// Constructors
	Portfolio(const std::string& ssn); // Constructs a portfolio using ssn for identification.
	Portfolio(const Portfolio& existingPortfolio);
	Portfolio();

	// Destructor
	~Portfolio();

private:
	std::string id;

	CertificateOfDeposit* cdLoc; 
	Bond* bondLoc; 
	CreditCard* complimentaryCardLoc;

	static const double AWARD_CARD_Amount;
	static const double CREDIT_LIMIT;     
};
#endif // !PORTO_H

