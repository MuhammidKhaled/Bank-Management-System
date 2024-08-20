#include "transaction.h"

long Transaction::sequenceNumberGenerator = 0;

// Transaction Class:
Transaction::Transaction(Client& c) : sequenceNumber(++sequenceNumberGenerator), posted(0),t(T) {}

Transaction::Transaction() : sequenceNumber(++sequenceNumberGenerator), posted(0),t(T) {}

Transaction::~Transaction() {}

Date& Transaction::TransactionDate() {
	return d;
}

long Transaction::getSequenceNumber() const {
	return sequenceNumber;
}

TransactionType Transaction::type() {
	return t;
}

int Transaction::status() {
	return posted;
}

// DepostiTransaction 
DepositTransaction::DepositTransaction(double amount, Account* rAccount) 
	: amount(amount), rAccount(rAccount) {
	t = DEPOSIT;
}

DepositTransaction::DepositTransaction(double amount) : amount(amount),rAccount(NULL) {
	t = DEPOSIT;
}

DepositTransaction::DepositTransaction() : rAccount(NULL), amount(0.0) {
	t = DEPOSIT;
}

DepositTransaction::~DepositTransaction() {}

int DepositTransaction::execute() {
	if (posted == 1) // Transaction has already been posted
		return 0;
	else if (rAccount == nullptr) // Nonexistent account
		return 0;
	else {
		rAccount->deposit(amount);
		posted = 1;
		return 1; // Deposit successful
	}
}

double DepositTransaction::getDepositAmount() const {
	return amount;
}

Account* DepositTransaction::getReceivingAccount() const {
	return rAccount;
}
// WithdrawalTransaction
WithdrawalTransaction::WithdrawalTransaction(double amount, Account* sourceAccount)
	: amount(amount), pAccount(sourceAccount) {
	t = WITHDRAWAL;
}

WithdrawalTransaction::WithdrawalTransaction(double amount) : amount(amount),pAccount(NULL) {
	t = WITHDRAWAL;
}

WithdrawalTransaction::WithdrawalTransaction() : pAccount(NULL),amount(0.0) {
	t = WITHDRAWAL;
}

WithdrawalTransaction::~WithdrawalTransaction(){}

int WithdrawalTransaction::execute() {
	if (posted == 1) // Transaction has already been posted
		return 0;
	else if (pAccount == nullptr) // Nonexistent account
		return 0;
	else {
		int flag = pAccount->withdraw(amount);
		if (flag == 1) // Withdrawal successful
			posted = 1;
		return flag;
	}
}

double WithdrawalTransaction::getWithdrawalAmount() const {
	return amount;
}

Account* WithdrawalTransaction::getSourceAccount() const {
	return pAccount;
}
// TransferTransaction Class:
TransferTransaction::TransferTransaction(double amount, Account* psourceAccount, Account* ptargetAccount) :
	pS(psourceAccount), pT(ptargetAccount), tAmount(amount) {
	t = TRANSFER;
}

TransferTransaction::TransferTransaction(double transferAmount)
	: pS(nullptr), pT(nullptr), tAmount(transferAmount) {
	t = TRANSFER;
}

TransferTransaction::TransferTransaction() : pS(nullptr), pT(nullptr), tAmount(0.0) {
	t = TRANSFER;
}

void TransferTransaction::attachSourceAccount(Account* psourceAccount) {
	pS = psourceAccount;
}

void TransferTransaction::attachTargetAccount(Account* ptargetAccount) {
	pT = ptargetAccount;
}

void TransferTransaction::changeTransferAmount(double transferAmount) {
	tAmount = transferAmount;
}

TransferTransaction::~TransferTransaction() {}

int TransferTransaction::execute() {
	if (posted == 1) // Transaction has already been posted
		return 0;
	else if (pS == nullptr || pT == nullptr) // Nonexistent accounts
		return 0;
	else {
		int flag = pS->transferFundsTo(*pT, tAmount);
		posted = 1;
		return flag;
	}
}

Account* TransferTransaction::sourceAccount() {
	return pS;
}

Account* TransferTransaction::targetAccount() {
	return pT;
}

double TransferTransaction::transferAmount() {
	return tAmount;
}





