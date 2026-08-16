# User Subsystem

## User.h
This header file defines the `User` class, which is an **Abstract Base Class** representing a generic user of the banking system. It demonstrates the OOP paradigm of **Abstraction** and **Encapsulation**.

**Responsibilities:**
- Encapsulate common user properties: `id`, `username`, `password`, `role`.
- Hold a reference to the `Database` object to allow users to perform DB operations.
- Provide getter methods for the encapsulated properties.
- Declare a **pure virtual function** `displayMenu() = 0;`, enforcing polymorphism. Any class inheriting from `User` (like `Customer` or `Admin`) MUST implement this method to provide their specific interface.
