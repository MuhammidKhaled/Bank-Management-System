#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>

class Account {
public:
//Modifiers
	int withdraw(double withdrawalAmount);
	void deposit(double depositAmount);
	int transferFundsTo(Account& targetAccount, double transferAmount);
	void setPassword(std::string newPassword);
	/*Precondition: The newPassword cannot be empty.
	  Postcondition: The Account is given a password.
	*/
	void restoreCodedPassword(std::string cpw);
	/*Restores cpw as the account's already coded password
	  that had previously been retrieved by a previously been
	  retrieved by a previous RetrieveCodePassword() message.*/
//Accessors
	double retrieveBalance() const;
	int retrieveAccountNumber() const;
	int validatePassword(std::string trialPassword) const;
	/*Postcondition: If the trial password matches the Accoount's password,
	  then 1 is returned, else 0 is returned.*/
	std::string retrieveCodedPassword() const;
	double marketValue() const;

	Account(); 
	Account(double openingBalance);
	Account(int accountNumber, double openingBalance);
	~Account();
private:
	double balance;
	std::string codedPassword;
	/*The next private member function is used to code
	  the password since we don't want to store uncoded
	  password*/
	std::string codePassword(std::string password) const;
		//Postcondition: Returns the coded form of password.
	int identificationNumber; //Stores account's number
};
#endif // !ACCOUNT_H
