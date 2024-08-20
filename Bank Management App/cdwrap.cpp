#include "cdwrap.h"
#include "except.h"

CDWrap::CDWrap(CertificateOfDeposit& aCD) : RAccount() , pCD(&aCD) {
	type = CD;
}

CDWrap::CDWrap() : RAccount(), pCD(nullptr) {}

CertificateOfDeposit& CDWrap::unWrap() {
	if(pCD == 0){
		throw(EmptyPackageException(this));
	}
	return *pCD; // return the object that was wrapped
}

double CDWrap::retrieveBalance() {
	return pCD->investment();
}

void CDWrap::deposit(double depositAmount) { return;}

int CDWrap::withdraw(double withdrawalAmount) { return 0;}

