# Withdrawal Subsystem

## Withdrawal.h
This file defines the `Withdrawal` class, inheriting from `Transaction`.

**OOP Theorems Demonstrated:**
- **Inheritance**: Inherits common transaction properties.
- **Polymorphism**: Overrides `execute()` to decrement the account balance, provided there are sufficient funds.
- **Exception Handling & Validation**: It validates the transaction rules (balance >= amount) before allowing the database update, throwing and catching database exceptions if queries fail.

**Responsibilities:**
- Encapsulate the specific logic for performing a withdrawal safely.
