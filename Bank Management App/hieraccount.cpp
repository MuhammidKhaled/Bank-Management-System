#include "hieraccout.h"

int RAccount::numberOfAccounts = 0;
double RAccount::totalFunds = 0;
double Savings::interestRate = .02;
int Savings::numberOfSavingsAccounts = 0;
double Savings::minimumBalance = 500;
double Checking::serviceChargeRate = .05; // Charging five cents per withdrawal
int Checking::numberOfCheckingAccounts = 0;
const char KEY = '\x09'; //The bit pattern of MASK is 00001001
const std::string DEFAULT_PASSWORD = "MohamedKhaled";


// RAccount class
RAccount::RAccount(int accountNumber, double openingBalance) :
	balance(openingBalance), identificationNumber(accountNumber), type(GENERIC), codedPassword("") {
	numberOfAccounts++;
	totalFunds += balance;
}

RAccount::RAccount() {
	// Initializing member variables with default values
	balance = 0.0;
	identificationNumber = 0; 
	codedPassword = "";

	type = GENERIC;

	numberOfAccounts++;
}

RAccount::RAccount(double openingBalance) {
	balance = openingBalance;
	identificationNumber = 0;
	codedPassword = "";

	type = GENERIC;

	numberOfAccounts++;

	totalFunds += openingBalance;
}

RAccount::~RAccount() {
	totalFunds -= balance;
	numberOfAccounts--;
}

void RAccount::deposit(double depositAmount) {
	totalFunds += depositAmount;
	balance += depositAmount;
}

double RAccount::retrieveBalance() const {
	return balance;
}

int RAccount::retrieveAccountNumber() const {
	return identificationNumber;
}

std::string RAccount::retrieveCodedPassword() {
	return codedPassword;
}

int RAccount::validatePassword(std::string trialPassword) {
	std::string temp;
	temp = codePassword(trialPassword);
	if (temp == codedPassword) return 1;
	else return 0;
}

inline std::string RAccount::codePassword(std::string password) {//Set Account's codedPassword attribute to a coded form of password.
	std::string temp = password;
	size_t n = password.length();
	//Using the exclusive OR with KEY, codes the characters in temp,one charachter at a time.
	for (size_t i = 0; i < n; i++)
	{
		//Using binary exclusive or to code the ith character in password
		temp[i] = password[i] ^ KEY;
	}
	return temp;
}

void RAccount::setPassword(std::string newPassword) {
	codedPassword = codePassword(newPassword);
}

void RAccount::restoreCodedPassword(std::string cpw) {
	codedPassword = cpw;
}

AccountType RAccount::Type() const {
	return type; // Returning the internally stored type
}

int RAccount::transferFundsTo(RAccount& targetAccount, double transferAmount) {
	// Checking if the transfer amount is valid within the source account
	if (balance - transferAmount < 0) {
		return 0; // Insufficient funds
	}
	// Withdrawing from source account and deposit to target account
	this->withdraw(transferAmount);
	targetAccount.deposit(transferAmount);
	return 1; // Successful transfer
}

double RAccount::retrieveTotalFunds() {
	return totalFunds;
}

int RAccount::retrieveNumberOfAccounts() {
	return numberOfAccounts;
}

// Savings class
Savings::Savings(int accountNumber, double openingBalance) :
	RAccount(accountNumber, openingBalance), transactionCount(0) {
	type = SAVINGS;
	numberOfSavingsAccounts++;
}

Savings::Savings() : RAccount(0, 0) { // Default constructor for Savings
	type = SAVINGS;
	numberOfSavingsAccounts++;
	transactionCount = 0;
}

Savings::Savings(double openingBalance) : RAccount(0, (int)openingBalance) { // Savings constructor with opening balance
	type = SAVINGS;
	numberOfSavingsAccounts++;
	transactionCount = 0;
}

int Savings::withdraw(double withdrawalAmount) {
	if (balance - withdrawalAmount >= minimumBalance) {
		balance -= withdrawalAmount;
		totalFunds -= withdrawalAmount;
		transactionCount++;
		return 1;
	}
	else {
		return 0;
	}
}

void Savings::deposit(double depositAmount) { // Override inherited method
	totalFunds += depositAmount;
	balance += depositAmount;
	transactionCount++;
}

double Savings::compoundInterest() {
	double interestEarned = balance * interestRate;
	balance += interestEarned;
	totalFunds += interestEarned;
	return interestEarned;
}

int Savings::retrieveTransactionCount() {
	return transactionCount;
}

void Savings::resetInterestRate(double newInterestRate) {
	interestRate = newInterestRate;
}

int Savings::retrieveNumberOfAccounts() {
	return numberOfSavingsAccounts;
}

double Savings::retrieveInterestRate() {
	return interestRate;
}

Savings::~Savings() {
	numberOfSavingsAccounts--;
}

// Checking class
Checking::Checking(int accountNumber, double openingBalance) :
	RAccount(accountNumber, openingBalance), serviceCharge(0) {
	type = CHECKING;
	numberOfCheckingAccounts++;
}

Checking::Checking() : RAccount(0, 0), serviceCharge(0) {
	type = CHECKING;
	numberOfCheckingAccounts++;
}

Checking::Checking(double openingBalance) : RAccount(0, openingBalance), serviceCharge(0) {
	type = CHECKING;
	numberOfCheckingAccounts++;
}

Checking::~Checking() {
	numberOfCheckingAccounts--;
}

int Checking::withdraw(double withdrawalAmount) {
	if (balance - withdrawalAmount - serviceChargeRate >= 0) {
		balance -= (withdrawalAmount + serviceChargeRate);
		totalFunds -= (withdrawalAmount + serviceChargeRate);
		serviceCharge += serviceChargeRate;
		return 1;
	}
	else {
		return 0;
	}
}

double Checking::retrieveServiceCharge() {
	return serviceCharge;
}

int Checking::retrieveNumberOfAccounts() {
	return numberOfCheckingAccounts;
}

double Checking::retrieveServiceChargeRate() {
	return serviceChargeRate;
}

// CheckingWithCredit class
CheckingWithCredit::CheckingWithCredit(int accountNumber, double openingBalance, double creditLimit) :
	Checking(accountNumber, openingBalance), creditLimit(creditLimit) {
	type = CHECKING_WITH_CREDIT;
	numberOfCheckingAccounts++;
}

CheckingWithCredit::CheckingWithCredit() : Checking(), creditLimit(0.0) {
	type = CHECKING_WITH_CREDIT;
	numberOfCheckingAccounts++;
}

CheckingWithCredit::CheckingWithCredit(double openingBalance, double creditLimit) : Checking(openingBalance), creditLimit(creditLimit) {
	type = CHECKING_WITH_CREDIT;
	numberOfCheckingAccounts++;
}

CheckingWithCredit::~CheckingWithCredit() {
	numberOfCheckingAccounts--;
}

double CheckingWithCredit::retrieveCreditLimit() const {
	return creditLimit;
}