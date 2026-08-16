#include <iostream>
#include <string>
#include <memory>
#include "Database.h"
#include "User.h"
#include "Customer.h"
#include "Admin.h"

using namespace std;

void registerCustomer(Database& db) {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;

    try {
        // Check if username exists
        string checkQuery = "SELECT id FROM users WHERE username = '" + username + "';";
        pqxx::result R = db.executeSelectQuery(checkQuery);
        if (!R.empty()) {
            cout << "Username already exists!\n";
            return;
        }

        // Insert User
        string insertUser = "INSERT INTO users (username, password, role) VALUES ('" + username + "', '" + password + "', 'CUSTOMER') RETURNING id;";
        pqxx::result res = db.executeSelectQuery(insertUser);
        
        if (!res.empty()) {
            int userId = res[0][0].as<int>();
            
            // Create Account for the user
            string createAccount = "INSERT INTO accounts (user_id, balance, status) VALUES (" + to_string(userId) + ", 0.00, 'ACTIVE');";
            db.executeQuery(createAccount);
            
            cout << "Registration successful! You can now login.\n";
        }
    } catch (const exception& e) {
        cerr << "Registration Error: " << e.what() << endl;
    }
}

unique_ptr<User> login(Database& db) {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    try {
        string query = "SELECT id, role FROM users WHERE username = '" + username + "' AND password = '" + password + "';";
        pqxx::result R = db.executeSelectQuery(query);

        if (R.empty()) {
            cout << "Invalid username or password!\n";
            return nullptr;
        }

        int userId = R[0][0].as<int>();
        string role = R[0][1].as<string>();

        if (role == "ADMIN") {
            return make_unique<Admin>(db, userId, username, password);
        } else if (role == "CUSTOMER") {
            return make_unique<Customer>(db, userId, username, password);
        }

    } catch (const exception& e) {
        cerr << "Login Error: " << e.what() << endl;
    }
    return nullptr;
}

int main() {
    Database db;
    db.connect();
    
    // Check if connected
    if (db.getConnection() == nullptr) {
        cout << "Failed to connect to the database. Exiting...\n";
        return 1;
    }

    // Initialize tables if they don't exist
    db.initializeTables();

    int choice;
    do {
        cout << "\n=== CLI BANK MANAGEMENT SYSTEM ===\n";
        cout << "1. Register (Customer)\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerCustomer(db);
                break;
            case 2: {
                unique_ptr<User> loggedInUser = login(db);
                if (loggedInUser) {
                    // Polymorphic Call: Calls either Customer::displayMenu() or Admin::displayMenu()
                    loggedInUser->displayMenu();
                }
                break;
            }
            case 0:
                cout << "Thank you for using the Banking System!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    db.disconnect();
    return 0;
}
