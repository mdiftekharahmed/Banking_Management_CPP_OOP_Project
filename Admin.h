#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
private:
    void viewCustomers();
    void viewAccounts();
    void blockAccount();
    void unblockAccount();
    void deleteUser();
    void clearTransactionHistory();

public:
    Admin(Database& database, int userId, string uname, string pass);
    
    // Override the abstract method
    void displayMenu() override;
};

#endif // ADMIN_H
