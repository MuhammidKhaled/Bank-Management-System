#ifndef EXCEPT_H
#define EXCEPT_H

#include "cdwrap.h"

class EmptyPackageException {
public:
	void print(); // Displays error message.
	void setErrorMessage(std::string newMessage); 
	EmptyPackageException(CDWrap* pWrap); // Constructs an error object for a CDWrap object
	// containing no CertificateOfDeposit object.
private:
	CDWrap* p; // points to the CDWrap object containing only air.
	std::string msg; // Error message string
};
#endif // !EXCEPT_H
