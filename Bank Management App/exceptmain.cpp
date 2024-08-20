#include "cdwrap.h"
#include "cd.h"
#include "iostream"
#include "except.h"

int main()
{
	CDWrap gifts[3];
	double amount, rate;
	int months;
	for (int i = 0; i < 3; i++) {
		std::cout << std::endl << "Enter amount, months, and rate ->";
		std::cin >> amount >> months >> rate;
		if (amount > 0 && months > 0 && rate < 1.00 && rate > 0.0) {
			CertificateOfDeposit* pCD;
			pCD = new CertificateOfDeposit(amount, months, rate);
			gifts[i] = *pCD;
		}
		else {
		}
	}
	// Embeding the code to be tested for exceptions in a try block
	try {
		for (int i = 0; i < 3; i++) {
			std::cout << std::endl << "Gift " << (i + 1) << " matures on "
				<< gifts[i].unWrap().maturity();
		}
	}
	catch (EmptyPackageException e) {
		e.print();
	}
	return 0;
}

