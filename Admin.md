# Admin Subsystem

## Admin.h & Admin.cpp
These files implement the `Admin` class, inheriting from the base `User` class.

**OOP Theorems Demonstrated:**
- **Inheritance**: Extends the `User` class to provide admin-specific behavior.
- **Polymorphism**: Overrides `displayMenu()` to show the Admin Interface (View Customers, View Accounts, Block/Unblock).
- **Encapsulation**: Private helper methods hide the database querying logic for administrative tasks.

**Responsibilities:**
- Handle all CLI interactions for a logged-in administrator.
- Manage accounts (blocking and unblocking).
- Delete customer users along with their accounts and transaction history (via `ON DELETE CASCADE`).
- Clear transaction history — either for a specific account or the entire database — with a confirmation prompt to prevent accidental deletion.
- View global data (all customers, all accounts).
