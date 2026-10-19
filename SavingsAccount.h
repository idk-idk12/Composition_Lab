#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "BankAccount.h"
#include <string>
using namespace std;

class SavingsAccount : public BankAccount {
public:
    // constructors
    SavingsAccount();
    SavingsAccount(string accountNumber, string accountHolderName, double balance, double interestRate);
    ~SavingsAccount() override;
    // setters
    void setInterestRate(double interestRate);
    // getters
    double getInterestRate() const;
    // other
    void calculateInterest() override;
    void print() override;
private:
    double interestRate;
};

#endif
