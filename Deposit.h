#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "Transaction.h"
#include <iostream>

class Deposit : public Transaction {
public:
    Deposit(Database& database, int accId, double amt)
        : Transaction(database, accId, amt, "DEPOSIT") {}

    bool execute() override {
        try {
            // Check current balance
            string selectQuery = "SELECT balance, status FROM accounts WHERE account_id = " + to_string(accountId) + ";";
            pqxx::result R = db.executeSelectQuery(selectQuery);

            if (R.empty() || R[0][1].as<string>() == "BLOCKED") {
                cout << "Account not found or blocked.\n";
                return false;
            }

            double balance = R[0][0].as<double>();
            balance += amount;

            // Update balance
            string updateQuery = "UPDATE accounts SET balance = " + to_string(balance) + " WHERE account_id = " + to_string(accountId) + ";";
            db.executeQuery(updateQuery);

            // Record transaction
            string recordTxn = "INSERT INTO transactions (account_id, type, amount) VALUES (" + to_string(accountId) + ", 'DEPOSIT', " + to_string(amount) + ");";
            db.executeQuery(recordTxn);
            
            return true;
        } catch (const exception& e) {
            cerr << "Deposit Error: " << e.what() << endl;
            return false;
        }
    }
};

#endif // DEPOSIT_H
