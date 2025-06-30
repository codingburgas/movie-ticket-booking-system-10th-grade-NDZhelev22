#include "../include/precompiler.h"

// Function definition
void registerUser(std::vector<User>& users) {
    clearScreen();
    std::cout << "\n=== Register New Account ===\n";
    std::string username, password;

    // Input loop with validation checks
    while (true) {
        std::cout << "Enter desired username: ";
        std::getline(std::cin, username);

        // Conditional checks on string properties
        if (username.empty() || username.length() > 20 ||
            username.find('|') != std::string::npos ||
            username.find(',') != std::string::npos ||
            username.find(' ') != std::string::npos) {
            std::cout << "Username cannot be empty, longer than 20 characters, or contain spaces, '|', or ',' characters. Please try again.\n";
            continue;
        }

        bool usernameExists = false;

        // Range-based for loop with member access
        for (const auto& user : users) {
            if (user.username == username) {
                usernameExists = true;
                break;
            }
        }

        if (usernameExists) {
            std::cout << "Username '" << username << "' already taken. Please choose a different one.\n";
        }
        else {
            break;
        }
    }

    // Input loop with validation for password
    while (true) {
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        if (password.empty() || password.length() < 4 || password.length() > 30 ||
            password.find('|') != std::string::npos) {
            std::cout << "Password cannot be empty, shorter than 4 or longer than 30 characters, or contain '|' characters. Please try again.\n";
        }
        else {
            break;
        }
    }

    // Function call to hashing utility
    std::string hashedPassword = simpleHash(password);

    // Use of emplace_back constructor in vector
    users.emplace_back(username, hashedPassword);

    saveUsers(users);

    std::cout << "\nAccount registered successfully!\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
}

// Function definition returning boolean
bool loginUser(std::vector<User>& users) {
    clearScreen();
    std::cout << "\n=== Login ===\n";
    std::string username, password;

    std::cout << "Enter username: ";
    std::getline(std::cin, username);

    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    // Function call to hashing utility
    std::string hashedPassword = simpleHash(password);

    // Range-based for loop with conditionals
    for (auto& user : users) {
        if (user.username == username) {
            if (user.hashedPassword == hashedPassword) {
                // Assignment of global or external variable
                currentLoggedInUser = user;

                loadUserBookings(currentLoggedInUser.username, currentLoggedInUser.userBookings);

                std::cout << "\nLogin successful! Welcome, " << currentLoggedInUser.username << "!\n";
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                clearScreen();
                return true;
            }
            else {
                std::cout << "\nIncorrect password.\n";
                std::cout << "\nPress Enter to return to the main menu...";
                std::cin.get();
                clearScreen();
                return false;
            }
        }
    }

    std::cout << "\nUsername not found.\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
    return false;
}

// Function definition
void logoutUser() {
    // Conditional check on member variable
    if (!currentLoggedInUser.username.empty()) {
        saveUserBookings(currentLoggedInUser.username, currentLoggedInUser.userBookings);

        // Object reinitialization via default constructor
        currentLoggedInUser = User();

        std::cout << "\nLogged out successfully.\n";
    }
    else {
        std::cout << "\nNo user is currently logged in.\n";
    }
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
}
