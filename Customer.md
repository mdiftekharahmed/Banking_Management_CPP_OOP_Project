# Customer Subsystem

## Customer.h & Customer.cpp
These files implement the `Customer` class, inheriting from the base `User` class.

**OOP Theorems Demonstrated:**
- **Inheritance**: Extends the `User` class to provide customer-specific behavior.
- **Polymorphism**: Overrides `displayMenu()` to show the Customer Interface (View Account, Check Balance, Deposit, Withdraw, Transfer, History).
- **Encapsulation**: Private helper methods (`depositMoney`, `withdrawMoney`, etc.) encapsulate the specific business logic for the CLI, hiding it from the outside world.
- **Composition & Smart Pointers (Safety Guarantee)**: Uses `std::unique_ptr<Account>` to manage the customer's account lifecycle, preventing memory leaks (an important paradigm in modern C++).

**Responsibilities:**
- Handle all CLI interactions for a logged-in customer.
- Perform deposits, withdrawals, and transfers by calling methods on the `Account` object and syncing the results back to the PostgreSQL database.
