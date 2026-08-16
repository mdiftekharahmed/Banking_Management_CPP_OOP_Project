# Database Subsystem

## Database.h
This header file defines the `Database` class, which handles the connection to the PostgreSQL database using the `libpqxx` library. It acts as an interface between the C++ application and the PostgreSQL server.

**Responsibilities:**
- Manage database connection strings (Host, Port, User, Password, DB Name).
- Declare connection and disconnection methods.
- Declare the `initializeTables()` method to setup the required schema if it doesn't exist.
- Declare helper methods for executing SQL queries (`executeQuery`, `executeSelectQuery`).

## Database.cpp
This source file implements the methods declared in `Database.h`.

**Key Implementations:**
- **connect() / disconnect()**: Handles the lifecycle of `pqxx::connection`.
- **initializeTables()**: Executes raw SQL queries to create `users`, `accounts`, and `transactions` tables. Also inserts a default admin user.
- **executeQuery()**: Uses `pqxx::work` to execute `INSERT`, `UPDATE`, or `DELETE` queries safely within a transaction.
- **executeSelectQuery()**: Uses `pqxx::nontransaction` to perform `SELECT` queries and return the result set.

## Live Database Monitoring
Included in this subsystem is a utility script `watch_db.ps1`. This is a PowerShell script that continuously polls the PostgreSQL database to display live changes to the `users`, `accounts`, and `transactions` tables.

**Responsibilities of `watch_db.ps1`:**
- Connect to PostgreSQL securely without prompting for a password (using `$env:PGPASSWORD`).
- Automatically clear the screen and refresh the data every 2 seconds.
- Provide a real-time view of the database state as the C++ CLI application operates.
