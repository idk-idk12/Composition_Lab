#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Transaction {
    string type;
    double amount;
    string timestamp;
};


class BankAccount {
public:
    BankAccount();
    BankAccount(string accountNumber, string accountHolderName, double balance);
    BankAccount(const BankAccount& other);
    BankAccount& operator=(const BankAccount& other);
    virtual ~BankAccount();
    // setters
    void setAccountNumberName(string accountNumberName);
    // getters
    // added const to the getters
    string getAccountNumber() const;
    string getAccountNumberName() const;
    double getBalance() const;
    // overloaded operators
    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);
    bool operator==(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;
    // other
    virtual void print();
    virtual void withdraw(double amount);
    virtual void deposit(double amount);
    virtual void calculateInterest() {
	cout << "Can't calculate interest. Not implemented." << endl;
    };
    void printHistory();
    void addTransaction(string type, double amount);
protected:
    string accountNumber;
    string accountHolderName;
    double balance = 0.0;
    vector<Transaction> transactionHistory;
private:
    string getTimeStamp();
};


#endif
