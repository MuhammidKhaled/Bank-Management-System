#ifndef HIERACCOUNT_H
#define HIERACCOUNT_H

#include <iostream>
#include <typeinfo>
// Interfaces for Account Hierarchy

enum AccountType{GENERIC, SAVINGS, CHECKING, CHECKING_WITH_CREDIT, CD};
class RAccount {// Root class in the Account Hierarchy
public:
// Modifiers Members
	virtual void deposit(double depositAmount);
	virtual int withdraw(double withdrawalAmount)= 0;
	void setPassword(std::string newPassword);
	void restoreCodedPassword(std::string cpw);
	virtual int transferFundsTo(RAccount& targetAccount, double transferAmount);
// Accessor Mombers
	double retrieveBalance() const;
	int retrieveAccountNumber() const;
	std::string retrieveCodedPassword();
	AccountType Type() const;
	static double retrieveTotalFunds();
	static int retrieveNumberOfAccounts();
	int validatePassword(std::string trialPassword);
// Backbone Members
	RAccount();
	RAccount(double openingBalance);
	RAccount(int accountNumber, double openingBalance);
	virtual ~RAccount();
protected:
	double balance;
	int identificationNumber;
	std::string codedPassword;
	std::string codePassword(std::string password);
	AccountType type;
	static int numberOfAccounts;
	static double totalFunds;
};

class Savings :public RAccount { // Inherit RAccount features
public:
// Modifier Members
	virtual void deposit(double depositAmount);
	virtual int withdraw(double withdrawalAmount);
	virtual double compoundInterest();
	static void resetInterestRate(double newInterestRate);
		// The parameter is the yearly interest rate.
// Accessor Members
	static int retrieveNumberOfAccounts();
	static double retrieveInterestRate();
	int retrieveTransactionCount();
// Backbone Members
	Savings();
	Savings(double openingBalance);
	Savings(int accountNumber, double openingBalance);
	virtual ~Savings();
protected:
	int transactionCount; // Tracking the number of deposits/withdrawals
	static int numberOfSavingsAccounts;
	static double minimumBalance;
	static double interestRate;
};

class Checking :public RAccount { // Inherited RAccount features
public:
// Modifiers Members
	virtual int withdraw(double withdrawalAccountAmount);
// Accessor Members
	static int retrieveNumberOfAccounts();
	static double retrieveServiceChargeRate();// Returns the charge per withdrawal.
	double retrieveServiceCharge();
// Backbone Members
	Checking();
	Checking(double openingBalance);
	Checking(int accountNumber, double openingBalance);
	virtual ~Checking();
protected:
	double serviceCharge;
	static double serviceChargeRate;
	static int numberOfCheckingAccounts;
};

class CheckingWithCredit :public Checking { // Inherit Checking features
public:
// Accessor Members
	double retrieveCreditLimit() const;
// Backbone Members
	CheckingWithCredit();
	CheckingWithCredit(double openingBalance, double creditLimit);
	CheckingWithCredit(int accountNumber, double openingBalance, double creditLimit);
	virtual ~CheckingWithCredit();
protected:
	double creditLimit;
};
#endif // !HIERACCOUT_H
