# CLI Bank Management System

A command-line banking application built in C++ using Object-Oriented Programming principles, connected to a live PostgreSQL database.

---

## Table of Contents

- [Features](#features)
- [OOP Concepts Used](#oop-concepts-used)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Database Setup](#database-setup)
- [Compilation](#compilation)
- [Running the Application](#running-the-application)
- [Live Database Monitor](#live-database-monitor)
- [Default Credentials](#default-credentials)
- [Admin Panel](#admin-panel)
- [Customer Panel](#customer-panel)

---

## Features

### Customer
- Register a new account
- Login / Logout
- View account details
- Check balance
- Deposit money
- Withdraw money
- Send money (transfer)
- View transaction history

### Admin
- Login / Logout
- View all customers
- View all accounts
- Block an account
- Unblock an account
- Delete a user (cascades to account and transactions)
- Clear transaction history (per account or all)

---

## OOP Concepts Used

| Concept | Where Applied |
|---|---|
| **Encapsulation** | Private data members in `User`, `Account`, `Transaction` |
| **Abstraction** | Pure virtual functions `displayMenu()`, `execute()`, `viewAccountDetails()` |
| **Inheritance** | `Customer`, `Admin` from `User`; `SavingsAccount` from `Account`; `Deposit`, `Withdrawal`, `Transfer` from `Transaction` |
| **Polymorphism** | `unique_ptr<User>` at login dispatches to correct derived menu at runtime |
| **Smart Pointers** | `unique_ptr<Account>` in `Customer` ensures safe memory management |
| **Exception Handling** | `try-catch` blocks around all database operations |

---

## Project Structure

```
Banking_System/
|
|- main.cpp               # Entry point, main menu, login/register
|- main.md                # Documentation for main.cpp
|
|- Database.h/.cpp        # PostgreSQL connection and query helpers
|- Database.md            # Documentation for database layer
|
|- User.h                 # Abstract base class for all users
|- User.md
|
|- Customer.h/.cpp        # Derived: Customer with banking operations
|- Customer.md
|
|- Admin.h/.cpp           # Derived: Admin with management operations
|- Admin.md
|
|- Account.h              # Abstract base class for accounts
|- Account.md
|
|- SavingsAccount.h       # Derived: Savings account with interest rate
|- SavingsAccount.md
|
|- Transaction.h          # Abstract base class for transactions
|- Transaction.md
|
|- Deposit.h              # Derived: Deposit transaction
|- Deposit.md
|
|- Withdrawal.h           # Derived: Withdrawal transaction
|- Withdrawal.md
|
|- Transfer.h             # Derived: Transfer transaction
|- Transfer.md
|
|- watch_db.ps1           # Live PostgreSQL database monitor (PowerShell)
|- run.ps1                # Helper script to run the app with correct PATH
|- README.md              # This file
```

---

## Prerequisites

| Requirement | Details |
|---|---|
| **OS** | Windows 10/11 |
| **PostgreSQL** | Version 14 or higher — [postgresql.org](https://www.postgresql.org/download/windows/) |
| **MSYS2** | Modern GCC compiler — [msys2.org](https://www.msys2.org/) |
| **libpqxx** | C++ PostgreSQL client library (installed via MSYS2 pacman) |

---

## Database Setup

**Step 1** — Make sure PostgreSQL is installed and the service is running.

**Step 2** — Open a PowerShell window and create the database:
```powershell
& "C:\Program Files\PostgreSQL\18\bin\psql.exe" -U postgres -c "CREATE DATABASE banking_system;"
```

The application will automatically create the required tables (`users`, `accounts`, `transactions`) and a default admin user the **first time it runs**.

---

## Compilation

**Step 1** — Install MSYS2 from [msys2.org](https://www.msys2.org/).

**Step 2** — Open a PowerShell window and install the required packages:
```powershell
C:\msys64\usr\bin\pacman.exe -S --noconfirm mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-libpqxx
```

**Step 3** — Navigate to the `Banking_System` directory and compile:
```powershell
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
g++ main.cpp Database.cpp Customer.cpp Admin.cpp -o banking_app.exe -lpqxx -lpq
```

> Note: All required runtime DLLs (libpqxx.dll, libstdc++-6.dll, etc.) are already copied into the project directory so the .exe runs standalone.

---

## Running the Application

```powershell
.\banking_app.exe
```

You will be greeted with the main menu:
```
=== CLI BANK MANAGEMENT SYSTEM ===
1. Register (Customer)
2. Login
0. Exit
Enter choice:
```

---

## Live Database Monitor

To watch the database update in real-time as you use the application, open a **second PowerShell window** in the same directory and run:

```powershell
powershell -ExecutionPolicy Bypass -File .\watch_db.ps1
```

This will refresh and display the `users`, `accounts`, and `transactions` tables every 2 seconds. Press `Ctrl+C` to stop.

---

## Default Credentials

| Role | Username | Password |
|---|---|---|
| Admin | `admin` | `admin123` |

Customer accounts are created by registering through the main menu (Option 1).

---

## Admin Panel

```
=== Admin Menu (admin) ===
1. View Customers
2. View Accounts
3. Block Account
4. Unblock Account
5. Delete User
6. Clear Transaction History
0. Logout
```

- **Block/Unblock Account** — Prevents or restores a customer's ability to deposit, withdraw, or transfer.
- **Delete User** — Permanently removes a customer and all their associated account and transaction data. Cannot be used on admin accounts.
- **Clear Transaction History** — Sub-menu to clear transactions for a specific account or wipe all records entirely. Requires confirmation before executing.

---

## Customer Panel

```
=== Customer Menu (username) ===
1. View Account Details
2. Check Balance
3. Deposit Money
4. Withdraw Money
5. Send Money
6. Transaction History
0. Logout
```

- **Send Money** — Requires the target Account ID. Both accounts must be active. The system records a `TRANSFER_OUT` on the sender's history and a `TRANSFER_IN` on the receiver's history.
- **Transaction History** — Shows the 10 most recent transactions for the logged-in customer.
