#include "BankAccount.h"
#include "CheckingAccount.h"
#include <iostream>
#include <string>

using namespace std;


/**
 * Constructs a checking account with the given account number, holder name,
 * starting balance, and per-withdrawal transaction fee.
 *
 * @param accountNumber the unique identifier for the account
 * @param accountHolderName the name of the account's owner
 * @param balance the starting balance of the account
 * @param transactionFee the fee charged on every withdrawal
 */
CheckingAccount::CheckingAccount(string accountNumber, string accountHolderName, double balance, double transactionFee) : BankAccount(accountNumber, accountHolderName, balance), transactionFee(transactionFee) {}

/**
 * Destructor. Overrides BankAccount's virtual destructor.
 */
CheckingAccount::~CheckingAccount() {}

/**
 * Sets the fee charged on every withdrawal. Prints an error message and
 * leaves the fee unchanged if the new fee is negative.
 *
 * @param transactionFee the new withdrawal fee
 */
void CheckingAccount::setTransactionFee(double transactionFee) {
    if (transactionFee < 0) {
	cout << "Transaction fee must be more than zero!" << endl;
    }
    else {
	this->transactionFee = transactionFee;
    }
}

/**
 * Returns the fee charged on every withdrawal.
 *
 * @return the account's transaction fee
 */
double CheckingAccount::getTransactionFee() const {
    return this->transactionFee;
}

/**
 * Prints the account type, the shared account details from BankAccount,
 * and the transaction fee.
 */
void CheckingAccount::print() {
    cout << "Account type: Checking" << endl;
    BankAccount::print();
    cout << "Transaction fee: " << this->transactionFee << endl;
}

/**
 * Withdraws the given amount plus the transaction fee from the account and
 * records the transaction. Prints an error message if the amount is negative
 * or if the amount plus the fee exceeds the balance.
 *
 * @param amount the amount to withdraw, not including the transaction fee
 */
void CheckingAccount::withdraw(double amount) {
    if (amount < 0) {
	cout << "Amount specified must be more than zero!" << endl;
	return;
    }
    // I added transaction fee here in order to ensure we correctly check whether input amount is positive or negative (e.g. if amount = -1 and transactionFee = 2, then amount would be 1, thus passing that check)
    amount = amount + this->transactionFee;
    if (amount > this->balance) {
	cout << "Insufficient funds!" << endl;
    }
    else {
	*this -= amount;
	cout << "Successfully withdrew $" << amount << endl;
	this->addTransaction("Withdraw", amount);
    }
}


