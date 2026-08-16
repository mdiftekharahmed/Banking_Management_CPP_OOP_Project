# Account Subsystem

## Account.h
This header file defines the `Account` class, which is an **Abstract Base Class** for all types of bank accounts.

**OOP Theorems Demonstrated:**
- **Abstraction**: It has a pure virtual function `viewAccountDetails() = 0`, forcing derived classes to implement it.
- **Encapsulation**: Details like `accountId`, `balance`, and `status` are protected, meaning only derived classes and the class itself can directly modify them.
- **Polymorphism**: The `withdraw()` and `deposit()` methods are virtual, meaning they can be overridden by specific account types if they have unique logic (e.g., overdraft limits).

**Responsibilities:**
- Hold the account's state (ID, balance, status).
- Perform basic validation for deposits and withdrawals (e.g., checking if the account is blocked, or if there is sufficient balance).
