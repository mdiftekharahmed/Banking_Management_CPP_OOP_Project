#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Database.h"
#include <iostream>

using namespace std;

// Abstract Base Class: Account
class Account {
protected:
    int accountId;
    int userId;
    double balance;
    string status;
    Database& db;

public:
    Account(Database& database, int accId, int uId, double bal, string stat)
        : db(database), accountId(accId), userId(uId), balance(bal), status(stat) {}
    
    virtual ~Account() = default;

    int getAccountId() const { return accountId; }
    int getUserId() const { return userId; }
    double getBalance() const { return balance; }
    string getStatus() const { return status; }

    // Pure Virtual Function representing Abstract method
    virtual void viewAccountDetails() const = 0;
    
    // Virtual functions that can be overridden by specific account types
    virtual bool withdraw(double amount) {
        if (status == "BLOCKED") {
            cout << "Account is blocked. Transaction denied.\n";
            return false;
        }
        if (amount <= 0) {
            cout << "Invalid amount.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        return true; // The actual DB update will be handled by the Transaction class
    }

    virtual bool deposit(double amount) {
        if (status == "BLOCKED") {
            cout << "Account is blocked. Transaction denied.\n";
            return false;
        }
        if (amount <= 0) {
            cout << "Invalid amount.\n";
            return false;
        }
        balance += amount;
        return true;
    }
};

#endif // ACCOUNT_H
