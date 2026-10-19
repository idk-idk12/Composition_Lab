#include "BankAccount.h"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;


/**
 * Constructs a bank account with the given account number, holder name,
 * and starting balance. The transaction history starts empty.
 *
 * @param accountNumber the unique identifier for the account
 * @param accountHolderName the name of the account's owner
 * @param balance the starting balance of the account
 */
BankAccount::BankAccount(string accountNumber, string accountHolderName, double balance) {
    this->accountNumber = accountNumber;
    this->accountHolderName = accountHolderName;
    this->balance = balance;
}

/**
 * Copy constructor. Creates a new account with the same account number,
 * holder name, and balance as another account.
 *
 * @param other the account to copy from
 */
BankAccount::BankAccount(const BankAccount& other) {
    this->accountNumber = other.accountNumber;
    this->accountHolderName = other.accountHolderName;
    this->balance = other.balance;
}

/**
 * Copy assignment operator. Overwrites this account's account number,
 * holder name, and balance with those of another account.
 *
 * @param other the account to copy from
 * @return a reference to this account
 */
BankAccount& BankAccount::operator=(const BankAccount& other) {
    this->accountNumber = other.accountNumber;
    this->accountHolderName = other.accountHolderName;
    this->balance = other.balance;
    return *this;  // returns the current object instance
}

/**
 * Destructor. Declared virtual in the header so that deleting a derived
 * account through a BankAccount pointer calls the correct destructor.
 */
BankAccount::~BankAccount() {}

/**
 * Sets the name of the account holder.
 *
 * @param accountHolderName the new name of the account's owner
 */
void BankAccount::setAccountNumberName(string accountHolderName) {
    this->accountHolderName = accountHolderName;
}

/**
 * Returns the account number.
 *
 * @return the account's unique identifier
 */
string BankAccount::getAccountNumber() const {
    return accountNumber;
}

/**
 * Returns the name of the account holder.
 *
 * @return the name of the account's owner
 */
string BankAccount::getAccountNumberName() const {
    return accountHolderName;
}

/**
 * Returns the current balance.
 *
 * @return the account's current balance
 */
double BankAccount::getBalance() const {
    return balance;
}

/**
 * Adds the given amount to the account's balance. Performs no
 * validation and does not record a transaction.
 *
 * @param amount the amount to add to the balance
 * @return a reference to this account
 */
BankAccount& BankAccount::operator+=(double amount) {
    this->balance += amount;
    return *this;
}

/**
 * Subtracts the given amount from the account's balance. Performs no
 * validation and does not record a transaction.
 *
 * @param amount the amount to subtract from the balance
 * @return a reference to this account
 */
BankAccount& BankAccount::operator-=(double amount) {
    this->balance -= amount;
    return *this;
}

/**
 * Checks whether two accounts are the same by comparing account numbers.
 *
 * @param other the account to compare against
 * @return true if both accounts have the same account number, false otherwise
 */
bool BankAccount::operator==(const BankAccount& other) const {
    return this->accountNumber == other.accountNumber;
}

/**
 * Checks whether this account has a lower balance than another account.
 *
 * @param other the account to compare against
 * @return true if this account's balance is less than the other's, false otherwise
 */
bool BankAccount::operator<(const BankAccount& other) const {
    return this->balance < other.balance;
}

/**
 * Checks whether this account has a higher balance than another account.
 *
 * @param other the account to compare against
 * @return true if this account's balance is greater than the other's, false otherwise
 */
bool BankAccount::operator>(const BankAccount& other) const {
    return this->balance > other.balance;
}

/**
 * Prints the account number, holder name, and balance. Derived classes
 * call this from their own print() to include the shared details.
 */
void BankAccount::print() {
    cout << "Account number: " << this->getAccountNumber() << endl;
    cout << "Account name: " << this->getAccountNumberName() << endl;
    cout << "Account balance: $" << this->getBalance() << endl;
}

/**
 * Withdraws the given amount from the account and records the transaction.
 * Prints an error message if the amount is negative or exceeds the balance.
 *
 * @param amount the amount to withdraw
 */
void BankAccount::withdraw(double amount) {
    if (amount < 0) {
	cout << "Amount specified must be more than zero!" << endl;
    }
    else if (amount > this->balance) {
	cout << "Insufficient funds!" << endl;
    }
    else {
	*this -= amount;
	cout << "Successfully withdrew $" << amount << endl;
	this->addTransaction("Withdraw", amount);
    }
}

/**
 * Deposits the given amount into the account and records the transaction.
 * Prints an error message if the amount is negative.
 *
 * @param amount the amount to deposit
 */
void BankAccount::deposit(double amount) {
    if (amount < 0) {
	cout << "Amount specified must be more than zero!" << endl;
    }
    else {
	*this += amount;
	cout << "Successfully deposited $" << amount << " into account!" << endl;
	this->addTransaction("Deposit", amount);
    }
}

/**
 * Returns the current local date and time as a formatted string.
 *
 * @return the current time in the format "YYYY-MM-DD HH:MM:SS"
 */
string BankAccount::getTimeStamp() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

/**
 * Creates a transaction with the given type and amount, stamps it with
 * the current time, and appends it to the account's transaction history.
 *
 * @param type a label describing the transaction (e.g. "Deposit" or "Withdraw")
 * @param amount the amount of money involved in the transaction
 */
void BankAccount::addTransaction(string type, double amount) {
    Transaction transaction;
    transaction.type = type;
    transaction.amount = amount;
    transaction.timestamp = this->getTimeStamp();
    this->transactionHistory.push_back(transaction);
}

/**
 * Prints every recorded transaction for this account, showing its type,
 * amount, and timestamp, in the order the transactions occurred.
 */
void BankAccount::printHistory() {
    for (auto transaction : this->transactionHistory) {
	cout << transaction.type << "   $" << transaction.amount << "  " << transaction.timestamp << endl;
    }
}
