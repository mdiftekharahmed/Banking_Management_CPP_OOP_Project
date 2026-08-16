#ifndef TRANSFER_H
#define TRANSFER_H

#include "Transaction.h"
#include <iostream>

class Transfer : public Transaction {
private:
    int targetAccountId;

public:
    Transfer(Database& database, int accId, double amt, int targetAccId)
        : Transaction(database, accId, amt, "TRANSFER"), targetAccountId(targetAccId) {}

    bool execute() override {
        try {
            // We use a transaction block (pqxx::work) in Database class, 
            // but for simplicity here we manually handle the sequence.
            
            // 1. Check Sender
            string senderQuery = "SELECT balance, status FROM accounts WHERE account_id = " + to_string(accountId) + ";";
            pqxx::result RSender = db.executeSelectQuery(senderQuery);

            if (RSender.empty() || RSender[0][1].as<string>() == "BLOCKED") {
                cout << "Sender account not found or blocked.\n";
                return false;
            }

            double senderBal = RSender[0][0].as<double>();
            if (senderBal < amount) {
                cout << "Insufficient Balance to transfer!\n";
                return false;
            }

            // 2. Check Receiver
            string receiverQuery = "SELECT balance, status FROM accounts WHERE account_id = " + to_string(targetAccountId) + ";";
            pqxx::result RReceiver = db.executeSelectQuery(receiverQuery);

            if (RReceiver.empty() || RReceiver[0][1].as<string>() == "BLOCKED") {
                cout << "Receiver account not found or blocked.\n";
                return false;
            }

            double receiverBal = RReceiver[0][0].as<double>();

            // 3. Execute updates
            senderBal -= amount;
            receiverBal += amount;

            string updateSender = "UPDATE accounts SET balance = " + to_string(senderBal) + " WHERE account_id = " + to_string(accountId) + ";";
            string updateReceiver = "UPDATE accounts SET balance = " + to_string(receiverBal) + " WHERE account_id = " + to_string(targetAccountId) + ";";
            
            db.executeQuery(updateSender);
            db.executeQuery(updateReceiver);

            // 4. Record transactions
            string recordTxnOut = "INSERT INTO transactions (account_id, type, amount, target_account_id) VALUES (" + to_string(accountId) + ", 'TRANSFER_OUT', " + to_string(amount) + ", " + to_string(targetAccountId) + ");";
            string recordTxnIn = "INSERT INTO transactions (account_id, type, amount, target_account_id) VALUES (" + to_string(targetAccountId) + ", 'TRANSFER_IN', " + to_string(amount) + ", " + to_string(accountId) + ");";
            
            db.executeQuery(recordTxnOut);
            db.executeQuery(recordTxnIn);
            
            return true;
        } catch (const exception& e) {
            cerr << "Transfer Error: " << e.what() << endl;
            return false;
        }
    }
};

#endif // TRANSFER_H
