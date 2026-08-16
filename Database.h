#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

// Assuming pqxx is available for PostgreSQL integration
#include <pqxx/pqxx>

using namespace std;

// Database Configuration
const string DB_HOST = "localhost";
const string DB_PORT = "5432";
const string DB_USER = "postgres"; // default user
const string DB_PASS = "postgres"; // default pass, change as needed
const string DB_NAME = "banking_system"; // user must create this database

class Database {
private:
    string connectionString;
    pqxx::connection* conn;

public:
    Database();
    ~Database();

    void connect();
    void disconnect();
    void initializeTables();

    // Helper functions for common operations
    void executeQuery(const string& query);
    pqxx::result executeSelectQuery(const string& query);

    // Provide access to the connection
    pqxx::connection* getConnection();
};

#endif // DATABASE_H
