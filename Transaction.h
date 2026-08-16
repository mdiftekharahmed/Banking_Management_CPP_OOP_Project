#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Database.h"
#include <string>

using namespace std;

// Abstract Base Class: Transaction
class Transaction {
protected:
    int accountId;
    double amount;
    Database& db;
    string type;

public:
    Transaction(Database& database, int accId, double amt, string txType)
        : db(database), accountId(accId), amount(amt), type(txType) {}
    
    virtual ~Transaction() = default;

    // Pure Virtual Function representing Abstract method
    virtual bool execute() = 0;
};

#endif // TRANSACTION_H
