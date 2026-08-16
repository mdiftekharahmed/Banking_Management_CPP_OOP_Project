#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Account.h"
#include <memory>

class Customer : public User {
private:
    unique_ptr<Account> account;

    void viewAccount();
    void checkBalance();
    void depositMoney();
    void withdrawMoney();
    void sendMoney();
    void transactionHistory();

public:
    Customer(Database& database, int userId, string uname, string pass);
    
    // Override the abstract method
    void displayMenu() override;
    
    // Fetches account details from DB and initializes the account object
    void loadAccount();
};

#endif // CUSTOMER_H
