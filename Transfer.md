# Transfer Subsystem

## Transfer.h
This file defines the `Transfer` class, inheriting from `Transaction`.

**OOP Theorems Demonstrated:**
- **Inheritance & Encapsulation**: Inherits base properties and adds an extra property `targetAccountId` to keep track of where the money is going.
- **Polymorphism**: Overrides `execute()` to handle complex, multi-account interactions.
- **Safety Guarantee**: By verifying both the sender's and receiver's accounts before performing any database updates, we guarantee atomicity (as close as possible without explicit SQL transaction blocks, although they could be added).

**Responsibilities:**
- Encapsulate the logic required to deduct funds from one account and add them to another, logging the transaction for both parties.
