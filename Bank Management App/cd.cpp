#include "cd.h"

CertificateOfDeposit::CertificateOfDeposit(double initialInvestment, int termInMonths, double rate) {
	Date todaysDate;
	value = initialInvestment;
	dayOfPurchase = todaysDate;
	fixedInterestRate = rate;
	months = termInMonths;
}

CertificateOfDeposit::CertificateOfDeposit(Account& sourceAccount,double initialInvestment,int termInMonths, double rate) {
	Date todaysDate;
	int ok = sourceAccount.withdraw(initialInvestment);
	if (ok == 1) {
		value = initialInvestment;
	}
	else {
		std::cout << "There are not enough funds in your account to create a certificate of deposit." << "\n";
		value = 0;
	}
	dayOfPurchase = todaysDate;
	fixedInterestRate = rate;
	months = termInMonths;
}

CertificateOfDeposit::~CertificateOfDeposit(){}

Date CertificateOfDeposit::purchaseDate() {
	return dayOfPurchase;
}

Date CertificateOfDeposit::maturity() {
	Date maturityDate = dayOfPurchase;
	maturityDate.addMonths(months); 
	return maturityDate;
}

double CertificateOfDeposit::investment() {
	return value;
}

double CertificateOfDeposit::interestRate() {
	return fixedInterestRate;
}

int CertificateOfDeposit::findOwner(const Account& acc) {
	// Finding the owner by the account number 
	int id = acc.retrieveAccountNumber();
	return id;
}

int CertificateOfDeposit::numberOfDaysHeld() {
	Date currentDate;
	int daysHeld = currentDate - dayOfPurchase;
	return daysHeld;
}

double CertificateOfDeposit::marketValue(int numberOfMonthsHeld) {
	double monthlyRate = fixedInterestRate / 12.0;

	return value * pow(1 + monthlyRate, numberOfMonthsHeld);
}

double CertificateOfDeposit::marketValue(Date targetDate)  {
	int yearsDiff = targetDate.getYear() - dayOfPurchase.getYear();
	int monthsDiff = targetDate.getMonth() - dayOfPurchase.getMonth() + 1;

	if (targetDate.getYear() == dayOfPurchase.getYear() && targetDate.getDay() < dayOfPurchase.getDay()) {
		monthsDiff--;
	}

	int monthsHeld = yearsDiff * 12 + monthsDiff;

	if (targetDate == dayOfPurchase) {
		return value;
	}
	else {
		double monthlyRate = fixedInterestRate / 12.0;
		return value * pow(1 + monthlyRate, monthsHeld);
	}
}

double CertificateOfDeposit::calculateEarlyWithdrawalPenalty() {
	int totalMonths = months;
	int monthsHeld = numberOfDaysHeld() / 30;
	int remainingMonths = totalMonths - monthsHeld; // Months remaining if withdrawn early

	// Handling for negative interest earned (assuming fees)
	double interestEarned = std::max(0.0, value * fixedInterestRate * monthsHeld / 12.0);

	// Penalty calculation
	double penaltyRate;

	// Tiered penalty based on remaining term
	if (remainingMonths > totalMonths / 2) {
		penaltyRate = 0.10; // Lower penalty for early withdrawal.
	}
	else if (remainingMonths > totalMonths / 4) {
		penaltyRate = 0.20; // Mid-tier penalty for withdrawal in the middle of the term (20%)
	}
	else if (remainingMonths > 0) {
		penaltyRate = 0.30; // Higher penalty for withdrawal closer to maturity (30%)
	}
	else {
		penaltyRate = 0;
	}

	return interestEarned * penaltyRate; // Penalize a portion of interest
}

bool CertificateOfDeposit::isEarlyWithdrawal() {
	Date withdrawalDate = dayOfPurchase + numberOfDaysHeld();
	return withdrawalDate < maturity();
}

double CertificateOfDeposit::finalWorth() {
	if (isEarlyWithdrawal()) {
		return marketValue(months) - calculateEarlyWithdrawalPenalty();
	}
	else {
		return marketValue(months);
	}
}
