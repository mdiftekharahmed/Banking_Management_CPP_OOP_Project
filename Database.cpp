#include "Database.h"

Database::Database() : conn(nullptr) {
    connectionString = "dbname=" + DB_NAME + " user=" + DB_USER + " password=" + DB_PASS + " host=" + DB_HOST + " port=" + DB_PORT;
}

Database::~Database() {
    disconnect();
}

void Database::connect() {
    try {
        conn = new pqxx::connection(connectionString);
        if (!conn->is_open()) {
            throw runtime_error("Can't open database");
        }
    } catch (const exception &e) {
        cerr << "Database connection error: " << e.what() << endl;
        conn = nullptr; // Ensure conn is null if connection failed
    }
}

void Database::disconnect() {
    if (conn != nullptr) {
        delete conn;
        conn = nullptr;
    }
}

void Database::initializeTables() {
    if (conn == nullptr || !conn->is_open()) return;

    try {
        pqxx::work W(*conn);
        
        // Users Table (Customers and Admins)
        string sqlUsers = 
            "CREATE TABLE IF NOT EXISTS users ("
            "id SERIAL PRIMARY KEY, "
            "username VARCHAR(50) UNIQUE NOT NULL, "
            "password VARCHAR(50) NOT NULL, "
            "role VARCHAR(20) NOT NULL"
            ");";
        
        // Accounts Table
        string sqlAccounts = 
            "CREATE TABLE IF NOT EXISTS accounts ("
            "account_id SERIAL PRIMARY KEY, "
            "user_id INT REFERENCES users(id) ON DELETE CASCADE, "
            "balance DECIMAL(15, 2) DEFAULT 0.00, "
            "status VARCHAR(20) DEFAULT 'ACTIVE'"
            ");";

        // Transactions Table
        string sqlTransactions = 
            "CREATE TABLE IF NOT EXISTS transactions ("
            "txn_id SERIAL PRIMARY KEY, "
            "account_id INT REFERENCES accounts(account_id) ON DELETE CASCADE, "
            "type VARCHAR(20) NOT NULL, "
            "amount DECIMAL(15, 2) NOT NULL, "
            "target_account_id INT, " // For transfers
            "timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
            ");";

        W.exec(sqlUsers);
        W.exec(sqlAccounts);
        W.exec(sqlTransactions);
        
        // Insert a default admin if not exists
        string sqlAdmin = "INSERT INTO users (username, password, role) "
                          "SELECT 'admin', 'admin123', 'ADMIN' "
                          "WHERE NOT EXISTS (SELECT 1 FROM users WHERE username = 'admin');";
        W.exec(sqlAdmin);

        W.commit();
        cout << "Database tables initialized successfully.\n";
    } catch (const exception &e) {
        cerr << "Error initializing tables: " << e.what() << endl;
    }
}

void Database::executeQuery(const string& query) {
    if (conn == nullptr || !conn->is_open()) return;
    try {
        pqxx::work W(*conn);
        W.exec(query);
        W.commit();
    } catch (const exception &e) {
        cerr << "Query execution error: " << e.what() << endl;
    }
}

pqxx::result Database::executeSelectQuery(const string& query) {
    if (conn == nullptr || !conn->is_open()) return pqxx::result();
    try {
        pqxx::nontransaction N(*conn);
        return N.exec(query);
    } catch (const exception &e) {
        cerr << "Select query execution error: " << e.what() << endl;
        return pqxx::result();
    }
}

pqxx::connection* Database::getConnection() {
    return conn;
}
