#include "account.h"
#include <iostream>

const char KEY = '\x09'; //The bit pattern of MASK is 00001001
const std::string DEFAULT_PASSWORD = "MohamedKhaled";
const int DUMMY_ID = 123456;

int Account::withdraw(double withdrawalAmount)
{
	double temp;
	int flag;
	temp = balance - withdrawalAmount;
	if (temp >= 0) 
	{
		flag = 1;
		balance = temp;
	}
	else
	{
		flag = 0;
	}
	return flag;
}

void Account::deposit(double depositAmount)
{
	balance += depositAmount;
}

int Account::transferFundsTo(Account& targetAccount, double transferAmount)
{
	int flag;
	flag = this->withdraw(transferAmount);
	if (flag == 1)
	{
		targetAccount.deposit(transferAmount);
	}
	else
	{
	}
	return flag;
}

void Account::setPassword(std::string newPassword)
{//Setting the account's password to the newPassword
	codedPassword = codePassword(newPassword);
}

void Account::restoreCodedPassword(std::string cpw) {
	// Assuming cpw is the already coded password retrieved previously
	codedPassword = cpw; // Setting cpw as the account's coded password
	std::cout << "Coded password restored successfully: " << codedPassword << "\n";
}

double Account::retrieveBalance() const
{
	return balance;
}

int Account::retrieveAccountNumber() const
{
	return identificationNumber;
}

int Account::validatePassword(std::string trialPassword) const
{
	std::string temp;
	temp = codePassword(trialPassword);
	if (temp == codedPassword) return 1;
	else return 0;
}

std::string Account::retrieveCodedPassword() const
{
	return codedPassword;
}

double Account::marketValue() const
{
	return balance;
}

Account::Account()
{
	identificationNumber = DUMMY_ID;
	balance = 0.0;
	this->setPassword(DEFAULT_PASSWORD);
}

Account::Account(double openingBalance)
{
	identificationNumber = DUMMY_ID;
	balance = openingBalance;
	this->setPassword(DEFAULT_PASSWORD);
}
Account::Account(int accountNumber, double openingBalance)
{
	identificationNumber = accountNumber;
	balance = openingBalance;
	this->setPassword(DEFAULT_PASSWORD);
}

Account::~Account(){}

std::string Account::codePassword(std::string password) const
{//Setting Account's codedPassword attribute to a coded form of password.
	std::string temp = password;
	size_t n = password.length();
	//Using the exclusive OR with KEY, codes the characters in temp,one charachter at a time.
	for (size_t i = 0; i < n; i++)
	{
	//Using binary exclusive or to code the ith character in password
		temp[i] = password[i] ^ KEY;
	}//endfor
	return temp;
}
