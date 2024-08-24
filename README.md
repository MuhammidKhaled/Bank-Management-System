# Bank Management System

A comprehensive C++-based application for managing bank accounts, transactions, and customer information.

This system provides functionalities for creating various account types (savings, checking), handling deposits, withdrawals, and transfers, generating account statements, and maintaining customer information. It incorporates robust error handling and security measures to ensure data integrity and protection.

## Features
- Account creation and management
- Deposit and withdrawal transactions
- Account balance inquiries
- Transaction history
- Interest calculations (for savings accounts)
- User authentication and authorization
- Data security and privacy
- Credit card services
- Debit card services
- Certificate of deposit (CD) services
- Bond services
- Mortgage services

## Technologies Used
- C++ programming language

## Project Structure
- ### Core Financial Services:
  - **Account Class**: This class represents a generic bank account and provides fundamental account operations.
  - **Credit Card Class**: Represents credit cards, including credit limits, interest rates, and billing.
  - **Mortgage Class**: Represents mortgage loans, including loan terms, payments, and interest calculations.
  - **Certificate of Deposit Class**: Represents certificates of deposit, including maturity dates and interest rates.
  - **Bond Class**: Represents bonds, including maturity dates, and interest payments.
  - **Debit Card Class**: Represents debit cards, including ATM access and point-of-sale transactions.
- ### Data Structures and Utilities:
  - **Money Class**: Handles monetary values and calculations.
  - **Portfolio Class**: Represents a collection of financial instruments (Bond,Certificate of Deposit).
  - **List Class**: A generic list implementation for storing and managing data.
  - **Client List Class**: A specialized list for managing client information.
  - **Client Statistics Class**: Calculates statistics related to client accounts.
- ### System Components:
  - **Scenario Class**: Represents different scenarios or use cases within the system.
  - **Account Hierarchy Class**: The base class for all account types providing common methods or properties.
  - **Transaction Class**: Represents financial transactions (deposits, withdrawals, transfers).
  - **CDWrap Class**: Provides an interface or wrapper for CertificateOfDeposit objects.
  - **Exception Class**: This class for handling exceptions within the system.

## Contributing

I welcome contributions from the community to enhance this Bank Management System. If you find bugs, have suggestions for improvements, or would like to add new features, please feel free to open an issue or submit a pull request.

## License

This project is licensed under the **[MIT License](https://github.com/MuhammidKhaled/Bank-Management-System/blob/master/LICENSE)**.

## Author

This project was created by *[MuhammidKhaled](https://github.com/MuhammidKhaled)*.
