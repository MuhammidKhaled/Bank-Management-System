#ifndef CD_H
#define CD_H

#include "date.h"
#include "account.h"

class CertificateOfDeposit {
public:
	Date purchaseDate();
	Date maturity();
	double investment();
	double interestRate();
	int findOwner(const Account& acc);
	double marketValue(int numberOfMonthsHeld);
	double marketValue(Date targetDate);
	double finalWorth();

	double calculateEarlyWithdrawalPenalty();
	bool isEarlyWithdrawal();

	int numberOfDaysHeld();
	CertificateOfDeposit(double initialInvestment, int termInMonths, double rate);
	CertificateOfDeposit(Account& sourceAccount, double initialInvestment,int termInMonths, double rate);
	~CertificateOfDeposit();
private:
	double value; // Original cost of the investment
	Date dayOfPurchase;
	double fixedInterestRate;
	int months;
};
#endif // !CD_H
