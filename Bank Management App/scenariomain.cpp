/*// This file is for implementing scenario class
#include "scenario.h"

#include <iostream>
//Family Finance Project

void startUp();
void coolDown();

void startUp() {
	std::cout << "\n\n**************** STARTING TRIALS ****************";
	std::cout << std::endl;
}

void coolDown() {
	std::cout << "\n\n************ TRIALS COMPLETED ******************";
}

int main()
{
	startUp();
	Scenario trial1;
	trial1.run();
	std::cout << "Enter data for second trial run\n";

	double wifeOB, husbandOB;

	do {
		std::cout << "Enter wife's opening balance(Numbers): ";
		std::cin >> wifeOB;

		std::cout << "Enter husband's opening balance(Numbers): ";
		std::cin >> husbandOB;

		if (wifeOB < 0 || husbandOB < 0) {
			std::cout << "Invalid input. Opening balances must be positive.\n";
			break;
		}
	} while (wifeOB < 0 || husbandOB < 0);

	double limit;
	do {
		std::cout << "Enter the limit(Numbers): ";
		std::cin >> limit;

		if (limit < 0) {
			std::cout << "Invalid input. The limit must be positive.\n";
			break;
		}
	} while (limit < 0);

	double principal, interestRate;
	int term;
	do {
		std::cout << "Enter the principal(Numbers): ";
		std::cin >> principal;

		std::cout << "Enter the term (in years): ";
		std::cin >> term;

		std::cout << "Enter the interest rate (as a decimal): ";
		std::cin >> interestRate;

		if (principal <= 0 || term <= 0 || interestRate >= 0.99 || interestRate <= 0.0) {
			std::cout << "Invalid input. Principal must be positive, term must be positive, and interest rate must be between 0 and 0.99.\n";
			break;
		}
	} while (principal <= 0 || term <= 0 || interestRate >= .99 || interestRate <= 0.00);
	std::cin.ignore(80, '\n');

	Scenario trial2(wifeOB, husbandOB, principal, term, interestRate, limit);

	trial2.run();

	coolDown();

	return 0;
}
*/