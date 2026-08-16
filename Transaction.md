# Transaction Subsystem

## Transaction.h
This header file defines the `Transaction` class, which is an **Abstract Base Class** representing a financial transaction.

**OOP Theorems Demonstrated:**
- **Abstraction**: Uses a pure virtual function `virtual bool execute() = 0;`, forcing all transaction types (deposit, withdrawal, transfer) to define how they are executed.
- **Encapsulation**: Protected properties (`accountId`, `amount`, `type`) keep transaction data safe from arbitrary modification.
- **Polymorphism**: The `execute()` function allows the system to process any transaction polymorphically, similar to the `processPayment(const Payment& payment)` function seen in your original `paymentprocess.cpp`.

**Responsibilities:**
- Hold generic transaction data.
- Enforce the implementation of an `execute()` method for derived transaction types.
