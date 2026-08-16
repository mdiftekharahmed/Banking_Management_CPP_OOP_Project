# Main Application Subsystem

## main.cpp
This is the entry point of the CLI Bank Management System application.

**OOP Theorems Demonstrated:**
- **Polymorphism (Runtime)**: In the `login()` function, a `unique_ptr<User>` is returned. Depending on the user's role (ADMIN or CUSTOMER), it instantiates the corresponding derived class. When `loggedInUser->displayMenu();` is called, C++ uses runtime polymorphism to execute the correct menu (either Customer's or Admin's).
- **Safety Guarantee**: Smart pointers (`std::unique_ptr`) are used to automatically manage the memory of the `User` object, guaranteeing that it gets cleanly destroyed when it goes out of scope (e.g., when they log out).
- **Exception Handling**: Surrounding database initialization and authentication queries with try-catch blocks ensures the program doesn't crash on invalid input or connection drops.

**Responsibilities:**
- Initialize the Database connection.
- Serve as the main router for registering new users and logging into the system.
