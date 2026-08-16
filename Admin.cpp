#include "Admin.h"
#include <iostream>

Admin::Admin(Database& database, int userId, string uname, string pass)
    : User(database, userId, uname, pass, "ADMIN") {}

void Admin::viewCustomers() {
    string query = "SELECT id, username, role FROM users WHERE role = 'CUSTOMER';";
    pqxx::result R = db.executeSelectQuery(query);
    
    cout << "\n--- Customers List ---\n";
    for (auto row : R) {
        cout << "ID: " << row[0].as<int>() << " | Username: " << row[1].as<string>() << "\n";
    }
    cout << "----------------------\n";
}

void Admin::viewAccounts() {
    string query = "SELECT account_id, user_id, balance, status FROM accounts;";
    pqxx::result R = db.executeSelectQuery(query);
    
    cout << "\n--- Accounts List ---\n";
    for (auto row : R) {
        cout << "Acc ID: " << row[0].as<int>() << " | User ID: " << row[1].as<int>() << " | Balance: $" << row[2].as<double>() << " | Status: " << row[3].as<string>() << "\n";
    }
    cout << "---------------------\n";
}

void Admin::blockAccount() {
    int accId;
    cout << "Enter Account ID to block: ";
    cin >> accId;
    
    string query = "UPDATE accounts SET status = 'BLOCKED' WHERE account_id = " + to_string(accId) + ";";
    db.executeQuery(query);
    cout << "Account " << accId << " blocked successfully (if it existed).\n";
}

void Admin::unblockAccount() {
    int accId;
    cout << "Enter Account ID to unblock: ";
    cin >> accId;
    
    string query = "UPDATE accounts SET status = 'ACTIVE' WHERE account_id = " + to_string(accId) + ";";
    db.executeQuery(query);
    cout << "Account " << accId << " unblocked successfully (if it existed).\n";
}

void Admin::deleteUser() {
    // First show the list of customers so admin knows valid IDs
    viewCustomers();

    int userId;
    cout << "Enter User ID to delete: ";
    cin >> userId;

    // Safety: prevent deleting admin accounts
    string checkQuery = "SELECT role FROM users WHERE id = " + to_string(userId) + ";";
    pqxx::result R = db.executeSelectQuery(checkQuery);

    if (R.empty()) {
        cout << "User ID " << userId << " not found.\n";
        return;
    }
    if (R[0][0].as<string>() == "ADMIN") {
        cout << "Cannot delete an admin account!\n";
        return;
    }

    // Confirm before deleting
    char confirm;
    cout << "Are you sure you want to delete User ID " << userId
         << " and all their data? (y/n): ";
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion cancelled.\n";
        return;
    }

    // ON DELETE CASCADE in the schema handles accounts + transactions automatically
    string deleteQuery = "DELETE FROM users WHERE id = " + to_string(userId) + ";";
    db.executeQuery(deleteQuery);
    cout << "User ID " << userId << " and all associated data deleted successfully.\n";
}

void Admin::clearTransactionHistory() {
    // Show current accounts so admin can pick one, or clear all
    cout << "\n--- Clear Transaction History ---\n";
    cout << "1. Clear history for a specific account\n";
    cout << "2. Clear ALL transaction history\n";
    cout << "0. Cancel\n";
    cout << "Enter choice: ";
    int subChoice;
    cin >> subChoice;

    if (subChoice == 0) {
        cout << "Cancelled.\n";
        return;
    }

    char confirm;
    if (subChoice == 1) {
        viewAccounts();
        int accId;
        cout << "Enter Account ID to clear transactions for: ";
        cin >> accId;

        // Verify account exists
        string checkQuery = "SELECT account_id FROM accounts WHERE account_id = " + to_string(accId) + ";";
        pqxx::result R = db.executeSelectQuery(checkQuery);
        if (R.empty()) {
            cout << "Account ID " << accId << " not found.\n";
            return;
        }

        cout << "Are you sure you want to clear all transactions for Account ID "
             << accId << "? (y/n): ";
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "Cancelled.\n";
            return;
        }

        string deleteQuery = "DELETE FROM transactions WHERE account_id = " + to_string(accId) + ";";
        db.executeQuery(deleteQuery);
        cout << "Transaction history for Account ID " << accId << " cleared successfully.\n";

    } else if (subChoice == 2) {
        cout << "Are you sure you want to delete ALL transaction records? This cannot be undone! (y/n): ";
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "Cancelled.\n";
            return;
        }

        db.executeQuery("DELETE FROM transactions;");
        cout << "All transaction history cleared successfully.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

void Admin::displayMenu() {
    int choice;
    do {
        cout << "\n=== Admin Menu (" << username << ") ===\n";
        cout << "1. View Customers\n";
        cout << "2. View Accounts\n";
        cout << "3. Block Account\n";
        cout << "4. Unblock Account\n";
        cout << "5. Delete User\n";
        cout << "6. Clear Transaction History\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewCustomers(); break;
            case 2: viewAccounts(); break;
            case 3: blockAccount(); break;
            case 4: unblockAccount(); break;
            case 5: deleteUser(); break;
            case 6: clearTransactionHistory(); break;
            case 0: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}
