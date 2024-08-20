#include "scenario.h"

const double DEFAULT_CERDIT_LIMIT = 1000;
const double DEFAULT_MORTGAGE = 10000;
const double DEFAULT_RATE = 0.01;
const int DEFAULT_TERM = 10;

Scenario::Scenario(double wOB, double hOB, double loan, int term, double rate, double cl) :
	wAccount(wOB), hAccount(hOB), jointCard(cl), homeMortgage(loan, rate, term)
{}

Scenario::Scenario() : wAccount(0.0), hAccount(0.0), jointCard(DEFAULT_CERDIT_LIMIT),
homeMortgage(DEFAULT_MORTGAGE, DEFAULT_RATE, DEFAULT_TERM) {}

Scenario::~Scenario() {}

void Scenario::run() {
	std::string input;
	char choice;
	do {
		displayMenu();
		std::cin >> input;
		choice = input[0];
		switch (choice) {
			case 'C': case 'c': cardTransaction(); break;
			case 'A': case 'a': accountTransaction(); break;
			case 'M': case 'm': mortgageTransaction(); break;
			case 'D': case 'd': displayFinances(); break;
			case 'Q': case 'q': break;
			default :
				std::cout << "\nInvalid input. Please try again." << "\n";
				break;
		}
	} while ((choice != 'q') && (choice != 'Q'));
	return;
}

void Scenario::displayMenu() {
	std::cout << "\n********** MENU OF CHOICES **********\n";
	std::cout << "\n C\tCredit Card Transaction";
	std::cout << "\n A\tAccount Transaction";
	std::cout << "\n M\tMortgage Transaction";
	std::cout << "\n D\tDisplay the finances";
	std::cout << "\n Q\tQuit";
	std::cout << "\n\n*************************************";
	std::cout << "\n\n\nEnter your choice and hit the enter key ->";
}

void Scenario::cardTransaction() {
	std::cout << "********** MENU OF CREDIT CARD CHOICES **********\n";
	std::cout << "\n C\tCredit Card Charge";
	std::cout << "\n P\tCredit Card Payment";
	std::cout << "\n Q\tQuit";
	std::cout << "\n\n*************************************";
	std::cout << "\n\n\nEnter your choice and hit the enter key ->";
	std::string input;
	std::cin >> input;
	char choice;
	choice = input[0];
	switch (choice) {
		case 'c': case 'C':
			int flag;
			double amount;
			std::cout << "\n\n\nEnter the amount the enter key ->";
			std::cin >> amount;
			if (amount < 0) {
				flag = 0;
			}
			else {
				flag = jointCard.postCharge(amount);
			}
			if (flag == 1) {
				std::cout << "\nCharge accepted";
			}
			else {
				std::cout << "\nCharge refused";
			}
			break;
		case 'P': case 'p':
			double paymentAmount;
			std::cout << "Enter the payment amount: ";
			std::cin >> paymentAmount;
			if (paymentAmount) {
				jointCard.makePayment(paymentAmount);
				std::cout << "\nPayment accepted";
			}
			break;
		case'q':case'Q':break;
		default:
			std::cout << "\nInvalid input. Please try again.";
			break;
	}
	std::cout << "\n\n";
}

void Scenario::displayFinances() {
	std::cout << "\n\n******** FINANCIAL STATEMENT ****************\n";
	std::cout  << std::fixed;
	std::cout.precision(2);
	std::cout << "Credit Card Current Balance: " << jointCard.currentBalance() << "\n";
	std::cout << "Available Credit: " << jointCard.availableCredit() << "\n";
	std::cout << "Credit Card Market Value: " << jointCard.marketValue() << "\n";
}

void Scenario::accountTransaction() {
	std::cout << "\nEnter 1 for transfer FROM wife To husband.";
	std::cout << "\nEnter 2 for transfer FROM husband TO wife.\n";
	int code;
	std::cin >> code;
	std::cout << "\nEnter the amount of being transferred ->$";
	double amount;
	std::cin >> amount;
	std::cin.ignore(80, '\n');
	int flag;
	std::string pw;
	switch (code)
	{
	case 1:
		// Transfer from wife's account to husband's account
		std::cout << "\nEnter wife's password -> ";
		std::cin >> pw;
		if (!wAccount.validatePassword(pw)) {
			std::cout << "\nINVAILD PASSWORD";
			flag = 0;
		}
		else {
			flag = wAccount.transferFundsTo(hAccount, amount);
		}
		if (flag == 1) {
			std::cout << "\nSuccessful tranfer to funds";
		}
		else {
			std::cout << "\nTransfer of funds rejected.";
		}
		break;
	case 2:
		// Transfer from husband's account to wife's account
		std::cout << "\nEnter husband's password -> ";
		std::cin >> pw;
		if (!hAccount.validatePassword(pw)) {
			std::cout << "\nINVAILD PASSWORD";
			flag = 0;
		}
		else {
			flag = hAccount.transferFundsTo(wAccount, amount);
		}
		if (flag == 1) {
			std::cout << "\nSuccessful tranfer to funds";
		}
		else {
			std::cout << "\nTransfer of funds rejected.";
		}
		break;
	default:
		std::cout << "\nInvalid input. Please try again.";
		break;
	}
	return;
}

void displayMortgageSchedule(Mortgage m);
void Scenario::mortgageTransaction() {
	std::cout << "\n********** MENU OF MORTGAGE CHOICES ******\n";
	std::cout << "\n D\tDisplay Mortgage Schedule";
	std::cout << "\n P\tMake Mortgage Payment";
	std::cout << "\n Q\tQuit";
	std::cout << "\n\n********************************************";
	std::cout << "\n\n\nEnter your choice and hit the enter key ->";
	std::string input;
	std::cin >> input;
	char choice;
	choice = input[0];
	switch (choice)
	{
		case 'd':case 'D':
			displayMortgageSchedule(homeMortgage);
			break;
		case 'p':case 'P':
			int paymentCode;
			std::cout << "\nEnter 1 for cash payment" << " and 2 for credit card payment->";
			std::cin >> paymentCode;
			if (paymentCode == 1) {
				homeMortgage.makeMonthlyPayment();
			}
			else if(paymentCode == 2){
				int flag;
				flag = homeMortgage.makeMonthlyPayment(jointCard);
				if (flag == 0) {
					std::cout << "\nCredit Card doesn't not accept charge";
				}
				else {
					std::cout << "\nCredit Card accepts mortgage payment";
				}
			}
			else {
				std::cout << "\nInvaild choice";
			}
			break;
		case 'q':case 'Q': break;
		default: 
			std::cout << "\nInvalid input. Please try again.";
			break;
	}
	return;
}

void displayMortgageSchedule(Mortgage m) {
	double loan = m.getOriginalLoan();
	double yInterestRate = m.rate();
	int term = m.mortgageTerm();

	Mortgage copy(loan, yInterestRate, term);

	std::cout << "********** MONTHLY PAYMENT SCHEDULE *******";
	std::cout << "\n\nMonth" << "\tRemaining" << "\tInterest";
	std::cout << "\n" << "\tPrincipal" << "\t\t Paid";
	std::cout << "\n_______" << "\t______" << "\t\t______";
	std::cout << "\n";

	int n = 12 * copy.mortgageTerm();
	int month;
	for (month = 1 ; month < n ; month++) {
		std::cout << month;
		m.makeMonthlyPayment();
		std::cout << "\t" << copy.getRemainingPrincipal();
		std::cout << "\t\t" << m.monthlyInterest() << "\n";
	}
	std::cout << "\n\n";
	std::cout << "\n Total Interest Payment is -> $" << m.interestPaidSoFar();
	return;
}