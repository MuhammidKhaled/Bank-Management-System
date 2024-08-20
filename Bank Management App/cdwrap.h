#ifndef CDWRAP_H
#define CDWRAP_H

#include "hieraccout.h"
#include "cd.h"

class CDWrap :public RAccount {
public:
// Conversion constructor to construct a wrapped object from an unwrapped one.
	CDWrap(CertificateOfDeposit& aCD);
	CDWrap();
// Method to retrieve the object that has been wrapped
	CertificateOfDeposit& unWrap();
// Overriding methods inherited from Account
	virtual void deposit(double depositAmount);
	virtual int withdraw(double withdrawal);
	double retrieveBalance();
protected:
	CertificateOfDeposit* pCD; // points to the object being wrapped
};
#endif // !CDWRAP_H
