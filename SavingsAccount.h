#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

// Derived Class: SavingsAccount
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(Database& database, int accId, int uId, double bal, string stat, double rate = 0.05)
        : Account(database, accId, uId, bal, stat), interestRate(rate) {}

    // Overriding the pure virtual function
    void viewAccountDetails() const override {
        cout << "\n--- Savings Account Details ---\n";
        cout << "Account ID: " << accountId << "\n";
        cout << "Balance: $" << balance << "\n";
        cout << "Status: " << status << "\n";
        cout << "Interest Rate: " << (interestRate * 100) << "%\n";
        cout << "-------------------------------\n";
    }

    // Savings accounts might have specific withdrawal rules, but we'll use the base one for now
    // We could override withdraw() if there was a minimum balance requirement
};

#endif // SAVINGSACCOUNT_H
