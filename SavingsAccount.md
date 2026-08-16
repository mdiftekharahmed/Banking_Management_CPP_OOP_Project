# Savings Account Subsystem

## SavingsAccount.h
This header file defines the `SavingsAccount` class, which is a **Derived Class** of `Account`.

**OOP Theorems Demonstrated:**
- **Inheritance**: It inherits the properties and base behaviors (like `deposit` and `withdraw`) from the `Account` class.
- **Polymorphism (Overriding)**: It provides a concrete implementation for the pure virtual function `viewAccountDetails()`, displaying its specific attributes like `interestRate`.

**Responsibilities:**
- Represent a specific type of account with an interest rate.
- Display its specific details when requested.
