#include "mortgage.h"

const int Mortgage::DEFAULT_TERM = 30;
const double Mortgage::DEFAULT_LOAN = 250000.0;
const double Mortgage::DEFAULT_RATE = 0.045;

double Mortgage::rate() const {
	return monthlyInterestRate * 12;
}

double Mortgage::getOriginalLoan() const {
	return originalLoan;
}

double Mortgage::getRemainingPrincipal() const {
	return remainingPrincipal;
}

double Mortgage::getFixedMonthlyPayment() const {
	return fixedMonthlyPayment;
}

double Mortgage::monthlyInterest() const {
	return monthlyInterestRate * remainingPrincipal;
}

double Mortgage::interestPaidSoFar() const {
	return totalInterest;
}

int Mortgage::mortgageTerm() const {
	return term;
}

double Mortgage::marketValue() const {

	Date currentDate = Date();

	int currentYear = currentDate.getYear();
	int startYear = startDate().getYear();

	int years = currentYear - startYear;
	// Assuming that the annual appreciation is 5%
	double currentValue = originalLoan * (1 + 0.05 * years);

	return currentValue;
}

Date Mortgage::startDate() const {
	return startingDate;
}

void Mortgage::makeMonthlyPayment() {
	double interestDue = monthlyInterestRate * remainingPrincipal;
	totalInterest += interestDue;
	remainingPrincipal -= fixedMonthlyPayment - interestDue;
}

int Mortgage::makeMonthlyPayment(CreditCard& sourceCreditCard) {
	int ok;
	ok = sourceCreditCard.postCharge(monthlyPayment);
	if (ok == 1) {
		double interestDue;
		interestDue = monthlyInterestRate * remainingPrincipal;
		totalInterest += interestDue;
		remainingPrincipal = fixedMonthlyPayment - interestDue;
	}
	else {

	}
	return ok;
}

Mortgage::Mortgage(double principal, double yearlyInterestRate, int lengthOfTermInYears) {
	originalLoan = principal;
	remainingPrincipal = principal;
	monthlyInterestRate = yearlyInterestRate / 12;
	term = lengthOfTermInYears;
	fixedMonthlyPayment = this->computeMonthlyPayment();
	totalInterest = 0;
	return;
}

Mortgage::Mortgage() : Mortgage(DEFAULT_LOAN, DEFAULT_RATE, DEFAULT_TERM)
{
	fixedMonthlyPayment = this->computeMonthlyPayment();
	totalInterest = 0;
}

Mortgage::~Mortgage()
{
}

double Mortgage::computeMonthlyPayment() {
	double result;
	int n = term * 12; 
	result = (monthlyInterestRate * originalLoan) / (1 - pow(1 + monthlyInterestRate, -n));
	/*1 - pow(1 + monthlyInterestRate, -n) It calculates a factor that considers the time value
	of money and the effect of compounding interest over the loan term*/
	return result;
}

