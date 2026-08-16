# Deposit Subsystem

## Deposit.h
This file defines the `Deposit` class, which inherits from `Transaction`.

**OOP Theorems Demonstrated:**
- **Inheritance**: Inherits base transaction properties.
- **Polymorphism**: Overrides the `execute()` method specifically for depositing money, increasing the account balance.
- **Exception Handling**: Uses a `try-catch` block around the database operations to handle SQL errors safely, a paradigm seen in your `Exception` directory.

**Responsibilities:**
- Encapsulate the specific database logic for performing a deposit transaction safely.
