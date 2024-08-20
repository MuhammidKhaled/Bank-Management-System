#include "creditcard.h"

double CreditCard::interestRate = 0.015;
Date CreditCard::lastInterestDate; 


// The helper function to calculate late fees
double calculateLateFee(double lateFeePercent, double balance) {
    double minimumLateFee = 10.0;
    double calculatedLateFee = balance * lateFeePercent / 100.0;
    return std::max(calculatedLateFee, minimumLateFee);
}

int CreditCard::postCharge(double chargeAmount) {
	Date today;
    int accepted;
	if (chargeAmount < 0) {
		throw std::invalid_argument("Charge amount cannot be negative.");
	}

    double av = this->availableCredit();
    if ((av > chargeAmount) && (expirationDate > today)) {
        if (this->isOverdue() == 1) {
            overdueBalance += chargeAmount;
        }
        else {
            balance += chargeAmount;
        }
        accepted = 1;
    }
    else {
        accepted = 0;
    }
    return accepted;
}

void CreditCard::makePayment(double paymentAmount) {
    const int gracePeriod = 21;
    const double minimumPaymentPercentage = 0.05;
    const double lateFeePercent = 0.035;

    if (paymentAmount > 0) {
        balance -= paymentAmount; 

        // Handling the overpayment
        if (balance < 0) {
            double overpayment = std::abs(balance);
            balance = 0.0;  // Ensuring that the balance is non-negative
        }

        Date today = Date();
        
        // Grace period 
        double minimumPayment = balance * minimumPaymentPercentage; // The description of the 
        // logic of the minimum payment system after the end of this method.
        if (paymentAmount >= minimumPayment && today - lastInterestDate <= gracePeriod) {
            overdue = false;
            overdueBalance = 0.0;
        }
        else {
            overdue = true;
            overdueBalance = std::max(0.0, balance); 
            lastInterestDate = today; 

            bool lateFeePolicy = true;
            if (lateFeePolicy) {
                double lateFee = calculateLateFee(lateFeePercent, balance);
                balance += lateFee;
            }
        }

        int daysOverdue = today - lastInterestDate;
        double dailyInterestRate = interestRate / 365.0;
        double interestPerDay = balance * dailyInterestRate;
        double interestDue = interestPerDay * daysOverdue;

    }
    else {
        std::cerr << "Invalid payment amount: " << paymentAmount << ". Payment must be greater than zero.\n";
    }
}
// Minimum payment system :

// This logic handles how payments are applied when a credit card account is overdue. 
// Even with an overdue balance, minimum payments can still be made. The minimum payment 
// is a small percentage (typically around 5%) of the outstanding balance. 

// When a payment is made:
//  - Any amount paid is applied towards the overdue balance first. 
//  - Once the overdue balance is zero, any remaining payment is applied to the current balance.

// It's important to note that:
//  - Making only minimum payments can take a long time to pay off the entire balance due to 
//    ongoing interest charges.
//  - Late fees may still apply if the minimum payment for the previous billing cycle wasn't made.
//  - Interest continues to accrue on the entire outstanding balance (including both overdue 
//    and current balances) daily until the balance is paid in full.

// Therefore, while minimum payments can help avoid additional late fees for the current cycle 
// and eventually move the account out of overdue status, it's generally recommended to make 
// payments exceeding the minimum amount whenever possible to pay off the balance faster and 
// minimize interest charges.

void CreditCard::chargeInterest() {
    if (overdue) {
        Date today;
        int daysOverdue = today - lastInterestDate;
        double dailyInterestRate = interestRate / 365.0;

        double interest = overdueBalance * dailyInterestRate * daysOverdue;
        overdueBalance += interest;

        interestDue += interest;
        lastInterestDate = today;
    }
}

void CreditCard::modifyLimit(double newLimit) {
	creditLimit = newLimit;
}

void CreditCard::modifyRate(double newRate) {
	interestRate = newRate;
}

void CreditCard::overDue() {
	overdue = 1;
}

double CreditCard::currentBalance() const {
	return balance + interestDue;
}

double CreditCard::marketValue() const {
	return balance + overdueBalance;
}

double CreditCard::financeCharge() const {
	return overdueBalance + interestDue;
}

double CreditCard::availableCredit() const {
	return creditLimit - (balance + interestDue);
}

int CreditCard::isExpired() const {
	Date today;
	return expirationDate < today;
}

int CreditCard::isOverdue() const {
	if (overdue) {
		return 1;
	}
	else {
		return 0;
	}
}

CreditCard::CreditCard(double limit) : balance(0.0), interestDue(0.0), overdue(false), overdueBalance(0.0), creditLimit(limit) {
	Date today;
	expirationDate = today + 365;
	lastInterestDate = today;
}

CreditCard::CreditCard() : interestDue(0.0), overdue(false), overdueBalance(0.0), creditLimit(3000.00), balance(0.0)  {
	Date today;
	expirationDate = today + 365;
	lastInterestDate = today;
}

CreditCard::~CreditCard(){}

