#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "date.h"
#include "account.h"
#include "client.h"

enum TransactionType {T,DEPOSIT, WITHDRAWAL, TRANSFER};
class Transaction { // This is an absract class that is never instantiated.
public:
// Accessor Members
	Date& TransactionDate();
	long getSequenceNumber() const; // Each transaction has a unique sequence number
	TransactionType type();
	int status(); // Returns 1 if already posted, 0 otherwise.

	virtual int execute() = 0; // Each class must define its own execute() method

// Backbone Members
	Transaction();
	Transaction(Client& c);

	virtual ~Transaction();
protected:
	static long sequenceNumberGenerator;
	long sequenceNumber;
	Date d;
	TransactionType t;
	int posted;
};

class DepositTransaction : public Transaction {
public:
// Backbone Members
	DepositTransaction(double amount, Account* pAccount);
	DepositTransaction(double amount);
	DepositTransaction();

	virtual ~DepositTransaction();

	int execute() override; // Override for deposit execution

// Accessor Members
	double getDepositAmount() const; // Method to retrieve the deposited amount
	Account* getReceivingAccount() const; // Method to retrieve the account receiving the deposit

protected:
	double amount;  // Amount to be deposited
	Account* rAccount; // Account to receive the deposit
};

class WithdrawalTransaction : public Transaction {
public:
// Backbone Members
	WithdrawalTransaction(double amount, Account* sourceAccount);
	WithdrawalTransaction(double amount);
	WithdrawalTransaction();

	virtual ~WithdrawalTransaction();

	int execute() override; // Override for withdrawal execution

// Accessor Members
	double getWithdrawalAmount() const; // Method to retrieve the withdrawal amount
	Account* getSourceAccount() const; // Method to retrieve the source account for withdrawal

protected:
	double amount;  // Amount to be withdrawn
	Account* pAccount; // Account from which to withdraw funds
};

class TransferTransaction : public Transaction {
public:
	// The next 2 members permit the consumer to change the source and target accounts.
// Modifiers
	void attachSourceAccount(Account* psourceAccount);
	void attachTargetAccount(Account* ptargetAccount);
	void changeTransferAmount(double transferAmount);

	virtual int execute();

// Accessor Members
	Account* sourceAccount();
	Account* targetAccount();
	double transferAmount();

// Backbone Members
	TransferTransaction();
	TransferTransaction(double transferAmount);
	TransferTransaction(double amount, Account* psourceAccount, Account* ptargetAccount);

	virtual ~TransferTransaction();
protected:
	Account* pS, * pT;
	double tAmount;
};
#endif // !TRANSACTION_H
