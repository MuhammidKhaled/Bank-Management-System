#include "except.h"

EmptyPackageException::EmptyPackageException(CDWrap* pWrap)
	: p(pWrap), msg("Error, This CDWrap has nothing in it."){}

void EmptyPackageException::print() {
	std::cout << std::endl << "********ERROR*********" << std::endl;
	std::cout << msg << std::endl;
}

void EmptyPackageException::setErrorMessage(std::string newMessage) {
	msg = newMessage;
}


