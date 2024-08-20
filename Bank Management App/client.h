#ifndef CLIENT_H
#define CLIENT_H

#include "porto.h"
#include "account.h"
#include "date.h"

class Client {
public:
// Modifier Members
	int openAccount(double openingBalance); 
		// Constructs an Account component.
	double closeAccount(); 
		// Destroys the Account component.
		// Returns the balance of money in the Account.
	int attachPortfolio(Portfolio& aPortfolio);
		// Attaches a Portfolio
		// The Client neither creates nor destroys its Portfolio component.
	void detachPortfolio();
// Accessor Members
	int hasAccount() const;
	int hasPortfolio() const;
	Account* accountLocation() const;
	Portfolio* portfolioLocation() const;
	std::string& socialSecurityNumber();
// Implementor Members
	double totalWorth(Date targetDate) const;
	double totalWorth() const;

	double retrieveBalance() const;

// Backbone Members
	Client& operator= (const Client& rhs);
	Client(const std::string& socialSecurityNumber);
	Client(const Client& anExistingClient);
	Client();
	~Client();
private:
	std::string ssn;
	Portfolio* pLoc;
	Account* acctLoc;
};
#endif // !CLIENT_H
