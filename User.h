#ifndef USER_H
#define USER_H

#include <string>
#include "Database.h"

using namespace std;

// Abstract Base Class: User
class User {
protected:
    int id;
    string username;
    string password;
    string role;
    Database& db;

public:
    User(Database& database, int userId, string uname, string pass, string r) 
        : db(database), id(userId), username(uname), password(pass), role(r) {}
    
    virtual ~User() = default;

    // Getters
    int getId() const { return id; }
    string getUsername() const { return username; }
    string getRole() const { return role; }

    // Pure Virtual Function representing Abstract method
    virtual void displayMenu() = 0;
};

#endif // USER_H
