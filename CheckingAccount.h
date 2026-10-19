#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "BankAccount.h"
#include <string>
using namespace std;

class CheckingAccount : public BankAccount {
public:
    // constructors
    CheckingAccount();
    CheckingAccount(string accountNumber, string accountHolderName, double balance, double transactionFee);
    ~CheckingAccount() override;
    // setters
    void setTransactionFee(double transactionFee);
    // getters
    double getTransactionFee() const;
    // other
    void withdraw(double amount) override;
    void print() override;
private:
    double transactionFee;
};

#endif
