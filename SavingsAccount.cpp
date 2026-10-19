#include "BankAccount.h"
#include "SavingsAccount.h"
#include <iostream>
#include <string>

using namespace std;


/**
 * Constructs a savings account with the given account number, holder name,
 * starting balance, and interest rate.
 *
 * @param accountNumber the unique identifier for the account
 * @param accountHolderName the name of the account's owner
 * @param balance the starting balance of the account
 * @param interestRate the interest rate as a decimal between 0 and 1 (e.g. 0.05 for 5%)
 */
SavingsAccount::SavingsAccount(string accountNumber, string accountHolderName, double balance, double interestRate) : BankAccount(accountNumber, accountHolderName, balance), interestRate(interestRate) {}

/**
 * Destructor. Overrides BankAccount's virtual destructor.
 */
SavingsAccount::~SavingsAccount() {}

/**
 * Sets the interest rate. Prints an error message and leaves the rate
 * unchanged if the new rate is not between 0 and 1.
 *
 * @param interestRate the new interest rate as a decimal between 0 and 1
 */
void SavingsAccount::setInterestRate(double interestRate) {
    if (interestRate < 0 || interestRate > 1) {
	cout << "Interest rate must be between 0-1!" << endl;
    }
    else {
	this->interestRate = interestRate;
    }
}

/**
 * Returns the interest rate.
 *
 * @return the account's interest rate as a decimal
 */
double SavingsAccount::getInterestRate() const {
    return this->interestRate;
}

/**
 * Calculates interest on the current balance using the interest rate and
 * adds it to the balance, then prints the amount of interest added.
 */
void SavingsAccount::calculateInterest() {
    double interest = this->balance * this->interestRate;
    this->balance += interest;
    cout << "Successfully added $" << interest << " of interest to account" << endl;
}

/**
 * Prints the account type, the shared account details from BankAccount,
 * and the interest rate.
 */
void SavingsAccount::print() {
    cout << "Account type: Savings" << endl;
    BankAccount::print();
    cout << "Interest rate: " << this->interestRate << endl;
}

