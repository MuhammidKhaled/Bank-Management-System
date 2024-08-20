#include "client.h"

int Client::openAccount(double openingBalance) {
	if (acctLoc != 0) 
		return 0;
	else {
		acctLoc = new Account(openingBalance);
		if (acctLoc == 0)
			return 0;
		else
			return 1;
	}
}

double Client::closeAccount() {
	double amount;
	if (acctLoc == 0)
		amount = 0; // There's no account component
	else {
		// Retrieving the account's balance before destroying it.
		amount = acctLoc->retrieveBalance();
		delete acctLoc;
		acctLoc = 0;
	}
	return amount;
}

int Client::attachPortfolio(Portfolio& aPortfolio) {
	if (pLoc == 0) {
		pLoc = &aPortfolio;
		return 1;
	}
	else {
		return 0;
	}
}

void Client::detachPortfolio() {
	// The Client class is not responsible for destroying its Portfolio component.
	pLoc = 0;
}

int Client::hasAccount() const {
	return acctLoc != 0;
}

int Client::hasPortfolio() const {
	return pLoc != 0;
}

Account* Client::accountLocation() const {
	return acctLoc;
}

Portfolio* Client::portfolioLocation() const {
	return pLoc;
}

std::string& Client::socialSecurityNumber() {
	return ssn;
}

double Client::totalWorth(Date targetDate) const {
	if (!hasAccount() && !hasPortfolio()) {
		return 0;
	}

	double total = 0;
	if (hasAccount()) {
		total += acctLoc->retrieveBalance(); 
	}
	if (hasPortfolio()) {
		total += pLoc->totalWorth(targetDate);
	}
	return total;
}

double Client::totalWorth() const {
	Date today = Date();
	return totalWorth(today);
}

double Client::retrieveBalance() const {
	if (acctLoc != nullptr) {
		return acctLoc->retrieveBalance();
	}
	else {
		return 0.0;
	}
}

Client& Client::operator= (const Client& rhs) {
	if (this == &rhs) {
		return *this;
	}

	std::string* newSsn = new std::string(rhs.ssn);
	Account* newAcct = nullptr;
	Portfolio* newPortfolio = nullptr;

	if (rhs.hasAccount()) {
		newAcct = new Account(*rhs.acctLoc);
	}

	if (rhs.hasPortfolio()) {
		newPortfolio = new Portfolio(*rhs.pLoc);
	}

	detachPortfolio();
	if (acctLoc != nullptr) {
		delete acctLoc;
		acctLoc = nullptr;
	}

	ssn = *newSsn;
	acctLoc = newAcct;
	pLoc = newPortfolio;

	delete newSsn;
	if (newAcct == nullptr) {
		delete newAcct;
	}
	if (newPortfolio == nullptr) {
		delete newPortfolio;
	}

	return *this; 
}

Client::Client(const std::string& socialSecurityNumber) : ssn(socialSecurityNumber), pLoc(0), acctLoc(0) {}

Client::Client(const Client& anExistingClient) {
	ssn = std::string(anExistingClient.ssn);
	acctLoc = nullptr;
	pLoc = nullptr;

	if (anExistingClient.hasAccount()) {
		acctLoc = new Account(*anExistingClient.acctLoc);
	}

	if (anExistingClient.hasPortfolio()) {
		pLoc = new Portfolio(*anExistingClient.pLoc);
	}
}

Client::Client() : ssn("000-00-0000"), pLoc(0), acctLoc(0) {}

Client::~Client() {
	detachPortfolio();

	if (acctLoc != nullptr) {
		delete acctLoc;
		acctLoc = nullptr;
	}
}





