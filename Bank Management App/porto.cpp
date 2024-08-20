#include "porto.h"

const double Portfolio::AWARD_CARD_Amount = 10000;
const double Portfolio::CREDIT_LIMIT = 5000;

Portfolio::Portfolio() : id("000-00-0000"), cdLoc(0), bondLoc(0), complimentaryCardLoc(0)
{
}

Portfolio::Portfolio(const Portfolio& existingPortfolio) {
	id = existingPortfolio.id;
	cdLoc = existingPortfolio.cdLoc;
	bondLoc = existingPortfolio.bondLoc;
	if (existingPortfolio.complimentaryCardLoc == 0)
		complimentaryCardLoc = 0;
	else {
		CreditCard* pCC;
		pCC = new CreditCard(*(existingPortfolio.complimentaryCardLoc));
		complimentaryCardLoc = pCC;
	}
}

Portfolio::Portfolio(const std::string& ssn) : id(ssn), cdLoc(0), bondLoc(0), complimentaryCardLoc(0) {}

Portfolio& Portfolio::operator= (const Portfolio& rhs) {
	if (this == &rhs)
		return *this;
	cdLoc = rhs.cdLoc;
	bondLoc = rhs.bondLoc;
	delete complimentaryCardLoc;
	if (rhs.complimentaryCardLoc != 0) {
		CreditCard* pCC;
		pCC = new CreditCard(*(rhs.complimentaryCardLoc));
		complimentaryCardLoc = pCC;
	}
	else
		complimentaryCardLoc = 0;
	return *this;
}

Bond* Portfolio::bondLocation() const {
	return bondLoc;
}

CertificateOfDeposit* Portfolio::cDLocation() const {
	return cdLoc;
}

CreditCard* Portfolio::cardLocation() const{
	return complimentaryCardLoc;
}

int Portfolio::attachBond(Bond* locationOfExistingBond) {
	if (bondLoc != 0)
		return 0;
	else
		bondLoc = locationOfExistingBond;

	if (totalWorth() >= AWARD_CARD_Amount && !complimentaryCardLoc)
		complimentaryCardLoc = new CreditCard(CREDIT_LIMIT);
	return 1;
}

int Portfolio::attachCD(CertificateOfDeposit* locationOfExistingCD) {
	if (cdLoc != 0) {
		return 0; 
	}

	cdLoc = locationOfExistingCD;

	if (totalWorth() >= AWARD_CARD_Amount && !complimentaryCardLoc) {
		complimentaryCardLoc = new CreditCard(CREDIT_LIMIT);
	}

	return 1;
}

void Portfolio::detachBond() {
	bondLoc = 0;
}

void Portfolio::detachCd() {
	cdLoc = 0;
}

std::string& Portfolio::socialSecurityNumber() {
	return id;
}

Portfolio::~Portfolio() {
	detachCd();
	detachBond();
	delete complimentaryCardLoc;
}

int Portfolio::hasCD() const {
	return cdLoc ? 1 : 0;
}

int Portfolio::hasBond() const {
	return bondLoc ? 1 : 0;
}

int Portfolio::hasCreditCard() const {
	return complimentaryCardLoc ? 1 : 0;
}

double Portfolio::totalWorth(Date targetDate) const {
	double worth = 0;
	if (cdLoc != 0)
		worth += cdLoc->marketValue(targetDate);
	if (bondLoc != 0)
		worth += bondLoc->marketValue(targetDate);
	if (complimentaryCardLoc != 0)
		worth -= complimentaryCardLoc->currentBalance();
	return worth;
}

double Portfolio::totalWorth() const {
	Date today = Date(); 
	return totalWorth(today);
}