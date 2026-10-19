// Jonathan Contreras-Jimenez
// 10/19/2026
// Bank account manager

#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;


void myCin(int &x) {
    // this handles non-int inputs
    if (!(cin >> x)) {
	// these two lines clears the buffer and ensures that the user can input again.
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool myCin(double &x) {
    // this handles non-int inputs
    if (!(cin >> x)) {
	// these two lines clears the buffer and ensures that the user can input again.
	cout << "Amount must be a number." << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return false;
    }
    return true;
}


/**
 * Checks whether any accounts exist, printing a message if there are none.
 *
 * @param accounts the vector of all bank accounts to check
 * @return true if at least one account exists, false otherwise
 */
bool is_accounts_nonemtpy(vector<BankAccount*>& accounts) {
    if (accounts.empty()) {
	cout << "No accounts have been made." << endl;
	return false;
    }
    return true;
}


/**
 * Prints the main menu options and reads the user's menu choice.
 *
 * @param userChoice the variable to store the user's selected option in
 */
void display_menu(int& userChoice) {
    cout << "1. Create Account" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. View Account Details" << endl;
    cout << "5. View All Accounts" << endl;
    cout << "6. Get Richest Account" << endl;
    cout << "7. Get Poorest Account" << endl;
    cout << "8. Print Sorted Accounts" << endl;
    cout << "9. Add interest (Savings only)" << endl;
    cout << "10. View history" << endl;
    cout << "11. Quit" << endl;
    myCin(userChoice);
}

/**
 * Prompts the user for an account number and searches the list of accounts for a match.
 * If no account matches, an error message is printed.
 *
 * @param accounts the vector of all bank accounts to search through
 * @return the index of the matching account in the vector, or -1 if no account
 *         with the entered account number exists
 */
int getAccount(const vector<BankAccount*>& accounts) {
    string accountNum;
    cin >> accountNum;
    for (int i = 0; i < accounts.size(); ++i) {
	if (accounts.at(i)->getAccountNumber() == accountNum) {
	    return i;
	}
    }
    cout << "Account '" << accountNum << "' not found" << endl;
    return -1;
}


/**
 * Prompts the user for an account type (checking or savings) and the details
 * for that type.
 *
 * @return a pointer to the newly created account, or nullptr if the user
 *         chose an invalid account type
 */
BankAccount* getCandidateAccount() {
    cout << "What kind of account?:" << endl;
    cout << "1. Checking" << endl;
    cout << "2. Savings" << endl;
    int userChoice;
    cin >> userChoice;
    if (userChoice <= 0 || userChoice > 2) {
	cout << "Invalid account choice!";
	return nullptr;
    }

    string accountId;
    string accountName;
    double initialBalance;
    cout << "Account number: ";
    cin >> accountId;
    cout << "Account name: ";
    cin >> accountName;
    cout << "Initial balance: ";
    cin >> initialBalance;

    if (userChoice == 1) {
	double transactionFee;
	cout << "Transaction fee: ";
	cin >> transactionFee;
	CheckingAccount* accountPtr = new CheckingAccount(accountId, accountName, initialBalance, transactionFee);
	return accountPtr;
    }
    else if (userChoice == 2) {
	double interestRate;
	cout << "Interest rate: ";
	cin >> interestRate;
	SavingsAccount* accountPtr = new SavingsAccount(accountId, accountName, initialBalance, interestRate);
	return accountPtr;
    }
}


/**
 * Creates a new account from user input and adds it to the list of accounts.
 * If an account with the same account number already exists, an error message
 * is printed and the new account is not added.
 *
 * @param accounts the vector of all bank accounts; the new account is appended to it
 *                 if its account number is unique
 */
void addAccount(vector<BankAccount*>& accounts) {
    BankAccount* candAccount = getCandidateAccount();  // candAccount = candidate account
    if (candAccount == nullptr) {
	return;
    }
    for (const BankAccount* account : accounts) {
	if (candAccount->getAccountNumber() == account->getAccountNumber()) {
	    cout << "Account with account number '" << candAccount->getAccountNumber() << "' already exists." << endl;
	    delete candAccount;
	    return;
	}
    }
    accounts.push_back(candAccount);
}

/**
 * Prompts the user for an account number and a deposit amount, then adds the
 * amount to that account's balance. Prints an error message if the amount is
 * invalid (non-numeric or negative). Does nothing further if the account is not found.
 *
 * @param accounts the vector of all bank accounts; the selected account's balance
 *                 is modified in place
 */
void deposit(vector<BankAccount*>& accounts) {
    if (is_accounts_nonemtpy(accounts)) {
	cout << "Account number: ";
	int accountIdx = getAccount(accounts);
	if (accountIdx != -1) {
	    BankAccount* account = accounts.at(accountIdx);
	    double amount;
	    cout << "Deposit amount: $";
	    if (myCin(amount)) {
		account->deposit(amount);
	    }
	    else {
		cout << "Invalid amount" << endl;
	    }
	}
	else {
	    cout << "Account doesn't exist" << endl;
	}
    }
}

/**
 * Prompts the user for an account number and a withdrawal amount, then subtracts
 * the amount from that account's balance. Prints an error message if the amount
 * is invalid (non-numeric or negative) or if the account has insufficient funds.
 * Does nothing further if the account is not found.
 *
 * @param accounts the vector of all bank accounts; the selected account's balance
 *                 is modified in place
 */
void withdraw(vector<BankAccount*>& accounts) {
    if (is_accounts_nonemtpy(accounts)) {
	cout << "Account number: ";
	int accountIdx = getAccount(accounts);
	if (accountIdx != -1) {
	    BankAccount* account = accounts.at(accountIdx);
	    double amount;
	    cout << "Withdraw amount: $";
	    if (myCin(amount)) {
		account->withdraw(amount);
	    }
	    else {
		cout << "Invalid amount" << endl;
	    }
	}
	else {
	    cout << "Account doesn't exist" << endl;
	}
    }
}


/**
 * Prompts the user for an account number and prints the details of that account.
 * Does nothing further if the account is not found.
 *
 * @param accounts the vector of all bank accounts to search through
 */
void getAccountDetails(vector<BankAccount*>& accounts) {
    if (is_accounts_nonemtpy(accounts)) {
	cout << "Account number: ";
	int accountIdx = getAccount(accounts);
	if (accountIdx != -1) {
	    BankAccount* account = accounts.at(accountIdx);
	    account->print();
	}
	else {
	    cout << "Account doesn't exist" << endl;
	}
    }
}


/**
 * Prints the details of every account in the list.
 * Does nothing if the list of accounts is empty.
 *
 * @param accounts the vector of all bank accounts to display
 */
void getAllAccountDetails(vector<BankAccount*>& accounts) {
    if (is_accounts_nonemtpy(accounts)) {
	for (BankAccount* account : accounts) {
	    cout << "" << endl;
	    account->print();
	}
    }
}


/**
 * Finds the account with the highest balance and prints its details.
 * If multiple accounts share the highest balance, the one that appears
 * first in the vector is reported. Does nothing if the list is empty.
 *
 * @param accounts the vector of all bank accounts to search through
 */
void getRichestAccount(vector<BankAccount*>& accounts) {
    if (is_accounts_nonemtpy(accounts)) {
	BankAccount* richestAccount = accounts.at(0);
	for (BankAccount* account : accounts) {
	    if (account->getBalance() > richestAccount->getBalance()) {
		richestAccount = account;
	    }
	}
	cout << "Richest Account details:" << endl;
	richestAccount->print();
    }
}


/**
 * Finds the account with the lowest balance and prints its details.
 * If multiple accounts share the lowest balance, the one that appears
 * first in the vector is reported. Does nothing if the list is empty.
 *
 * @param accounts the vector of all bank accounts to search through
 */
void getPoorestAccount(vector<BankAccount*>& accounts) {
    if (is_accounts_nonemtpy(accounts)) {
	BankAccount* poorestAccount = accounts.at(0);
	for (BankAccount* account : accounts) {
	    if (account->getBalance() < poorestAccount->getBalance()) {
		poorestAccount = account;
	    }
	}
	cout << "Poorest Account details:" << endl;
	poorestAccount->print();
    }
}


/**
 * Sorts the accounts using the overloaded < operator, then prints the details
 * of every account in sorted order. Note that this reorders the vector
 * permanently, so the accounts will stay in sorted order for all later
 * operations. Does nothing if the list is empty.
 *
 * @param accounts the vector of all bank accounts; sorted in place
 */
void printSortedAccounts(vector<BankAccount*>& accounts) {
    if (is_accounts_nonemtpy(accounts)) {
	// I had to pass a lambda function and in it dereference the object pointers (i.e. get the object from which the pointer is pointing at) and manually compare the objects.
	sort(accounts.begin(), accounts.end(), [](const BankAccount* a, const BankAccount* b) {return a->getBalance() < b->getBalance();});
	getAllAccountDetails(accounts);
    }
}


/**
 * Prompts the user for an account number and adds interest to that account.
 * Only savings accounts calculate interest; other account types print a
 * message saying interest is not supported. Does nothing further if the
 * account is not found.
 *
 * @param accounts the vector of all bank accounts; the selected account's
 *                 balance is modified in place
 */
void addInterest(vector<BankAccount*>& accounts) {
    if (is_accounts_nonemtpy(accounts)) {
	cout << "Account number: ";
	int accountIdx = getAccount(accounts);
	if (accountIdx != -1) {
	    BankAccount* account = accounts.at(accountIdx);
	    account->calculateInterest();
	}
	else {
	    cout << "Account doesn't exist" << endl;
	}
    }
}


/**
 * Prompts the user for an account number and prints that account's
 * transaction history. Does nothing further if the account is not found.
 *
 * @param accounts the vector of all bank accounts to search through
 */
void printTransactionHistory(vector<BankAccount*>& accounts) {
    if (is_accounts_nonemtpy(accounts)) {
	cout << "Account number: ";
	int accountIdx = getAccount(accounts);
	if (accountIdx != -1) {
	    BankAccount* account = accounts.at(accountIdx);
	    account->printHistory();
	}
	else {
	    cout << "Account doesn't exist" << endl;
	}
    }
}


void demonstrateTransactionHistory() {
    vector<BankAccount*> accounts;
    CheckingAccount* checkingAccount = new CheckingAccount("1", "NoName", 400, 4);
    checkingAccount->deposit(400);
    checkingAccount->withdraw(100);
    SavingsAccount* savingsAccount = new SavingsAccount("2", "NoName", 400, 0.4);
    savingsAccount->deposit(50);
    savingsAccount->withdraw(200);
    accounts.push_back(checkingAccount);
    accounts.push_back(savingsAccount);
    for (BankAccount* account : accounts) {
	cout << endl;
	account->printHistory();
	delete account;
    }
}


int main() {
    demonstrateTransactionHistory();
    int userChoice;
    vector<BankAccount*> accounts;
    cout << endl;
    do {
	display_menu(userChoice);
	switch (userChoice) {
	    case 1:
		addAccount(accounts);
		break;
	    case 2:
		deposit(accounts);
		break;
	    case 3:
		withdraw(accounts);
		break;
	    case 4:
		getAccountDetails(accounts);
		break;
	    case 5:
		getAllAccountDetails(accounts);
		break;
	    case 6:
		getRichestAccount(accounts);
		break;
	    case 7:
		getPoorestAccount(accounts);
		break;
	    case 8:
		printSortedAccounts(accounts);
		break;
	    case 9:
		addInterest(accounts);
		break;
	    case 10:
		printTransactionHistory(accounts);
		break;
	    case 11:
		break;
	    default:
		cout << "Only 1-11 options are avaliable." << endl;
		break;
	}
	cout << endl;
    }
    while (userChoice != 11);
    // to prevent memory leak
    for (BankAccount* account : accounts) {
	delete account;
    }
    return 0;
}
