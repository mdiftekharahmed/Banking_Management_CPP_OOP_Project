#include "Customer.h"
#include "SavingsAccount.h"
#include <iostream>

Customer::Customer(Database& database, int userId, string uname, string pass)
    : User(database, userId, uname, pass, "CUSTOMER") {
    loadAccount();
}

void Customer::loadAccount() {
    string query = "SELECT account_id, balance, status FROM accounts WHERE user_id = " + to_string(id) + ";";
    pqxx::result R = db.executeSelectQuery(query);
    
    if (!R.empty()) {
        int accId = R[0][0].as<int>();
        double bal = R[0][1].as<double>();
        string status = R[0][2].as<string>();
        
        // Using unique_ptr for memory management (Safety Guarantee Paradigm)
        account = make_unique<SavingsAccount>(db, accId, id, bal, status);
    } else {
        cout << "No account found for this customer. Please contact admin.\n";
    }
}

void Customer::viewAccount() {
    if (account) {
        account->viewAccountDetails();
    } else {
        cout << "No active account.\n";
    }
}

void Customer::checkBalance() {
    if (account) {
        cout << "Current Balance: $" << account->getBalance() << "\n";
    } else {
        cout << "No active account.\n";
    }
}

void Customer::depositMoney() {
    if (!account) return;
    
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    
    if (account->deposit(amount)) {
        string updateQuery = "UPDATE accounts SET balance = " + to_string(account->getBalance()) + " WHERE account_id = " + to_string(account->getAccountId()) + ";";
        db.executeQuery(updateQuery);
        
        string recordTxn = "INSERT INTO transactions (account_id, type, amount) VALUES (" + to_string(account->getAccountId()) + ", 'DEPOSIT', " + to_string(amount) + ");";
        db.executeQuery(recordTxn);
        
        cout << "Deposit successful!\n";
    }
}

void Customer::withdrawMoney() {
    if (!account) return;
    
    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    
    if (account->withdraw(amount)) {
        string updateQuery = "UPDATE accounts SET balance = " + to_string(account->getBalance()) + " WHERE account_id = " + to_string(account->getAccountId()) + ";";
        db.executeQuery(updateQuery);
        
        string recordTxn = "INSERT INTO transactions (account_id, type, amount) VALUES (" + to_string(account->getAccountId()) + ", 'WITHDRAWAL', " + to_string(amount) + ");";
        db.executeQuery(recordTxn);
        
        cout << "Withdrawal successful!\n";
    }
}

void Customer::sendMoney() {
    if (!account) return;
    
    int targetAccId;
    double amount;
    cout << "Enter target Account ID: ";
    cin >> targetAccId;
    cout << "Enter amount to send: ";
    cin >> amount;

    if (account->withdraw(amount)) {
        // Find target account
        string checkQuery = "SELECT balance FROM accounts WHERE account_id = " + to_string(targetAccId) + " AND status = 'ACTIVE';";
        pqxx::result R = db.executeSelectQuery(checkQuery);
        
        if (R.empty()) {
            cout << "Target account not found or blocked. Transaction cancelled.\n";
            account->deposit(amount); // Revert withdrawal
            return;
        }

        double targetBal = R[0][0].as<double>();
        targetBal += amount;

        // Update both accounts
        string updateSelf = "UPDATE accounts SET balance = " + to_string(account->getBalance()) + " WHERE account_id = " + to_string(account->getAccountId()) + ";";
        string updateTarget = "UPDATE accounts SET balance = " + to_string(targetBal) + " WHERE account_id = " + to_string(targetAccId) + ";";
        
        db.executeQuery(updateSelf);
        db.executeQuery(updateTarget);

        // Record Transactions
        string recordSelfTxn = "INSERT INTO transactions (account_id, type, amount, target_account_id) VALUES (" + to_string(account->getAccountId()) + ", 'TRANSFER_OUT', " + to_string(amount) + ", " + to_string(targetAccId) + ");";
        string recordTargetTxn = "INSERT INTO transactions (account_id, type, amount, target_account_id) VALUES (" + to_string(targetAccId) + ", 'TRANSFER_IN', " + to_string(amount) + ", " + to_string(account->getAccountId()) + ");";
        
        db.executeQuery(recordSelfTxn);
        db.executeQuery(recordTargetTxn);

        cout << "Money transferred successfully!\n";
    }
}

void Customer::transactionHistory() {
    if (!account) return;
    
    string query = "SELECT txn_id, type, amount, target_account_id, timestamp FROM transactions WHERE account_id = " + to_string(account->getAccountId()) + " ORDER BY timestamp DESC LIMIT 10;";
    pqxx::result R = db.executeSelectQuery(query);
    
    cout << "\n--- Recent Transactions ---\n";
    for (auto row : R) {
        cout << "Txn ID: " << row[0].as<int>() << " | Type: " << row[1].as<string>() << " | Amount: $" << row[2].as<double>() << " | Target: " << (row[3].is_null() ? "N/A" : row[3].c_str()) << " | Date: " << row[4].c_str() << "\n";
    }
    cout << "---------------------------\n";
}

void Customer::displayMenu() {
    int choice;
    do {
        cout << "\n=== Customer Menu (" << username << ") ===\n";
        cout << "1. View Account Details\n";
        cout << "2. Check Balance\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Send Money\n";
        cout << "6. Transaction History\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewAccount(); break;
            case 2: checkBalance(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: sendMoney(); break;
            case 6: transactionHistory(); break;
            case 0: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}
