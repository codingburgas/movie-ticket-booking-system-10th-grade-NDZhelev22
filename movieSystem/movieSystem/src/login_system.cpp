#include "../include/precompiler.h"

void registerUser(std::vector<User>& users) {
    clearScreen();
    std::cout << "\n=== Register New Account ===\n";
    std::string username, password;

    while (true) {
        std::cout << "Enter desired username: ";
        std::getline(std::cin, username);

        if (username.empty() || username.length() > 20 || username.find('|') != std::string::npos || username.find(',') != std::string::npos || username.find(' ') != std::string::npos) {
            std::cout << "Username cannot be empty, longer than 20 characters, or contain spaces, '|', or ',' characters. Please try again.\n";
            continue;
        }

        bool usernameExists = false;
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

    while (true) {
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        if (password.empty() || password.length() < 4 || password.length() > 30 || password.find('|') != std::string::npos) {
            std::cout << "Password cannot be empty, shorter than 4 or longer than 30 characters, or contain '|' characters. Please try again.\n";
        }
        else {
            break;
        }
    }

    std::string hashedPassword = simpleHash(password);
    users.emplace_back(username, hashedPassword); // Constructor handles setting the private hashedPassword
    saveUsers(users);

    std::cout << "\nAccount registered successfully!\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
}

bool loginUser(std::vector<User>& users) {
    clearScreen();
    std::cout << "\n=== Login ===\n";
    std::string username, password;

    std::cout << "Enter username: ";
    std::getline(std::cin, username);

    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    std::string hashedPasswordInput = simpleHash(password); // Hash the input password for comparison

    for (auto& user : users) {
        if (user.username == username) {
            // Use the public getter method to access the private hashedPassword for comparison
            if (user.getHashedPassword() == hashedPasswordInput) {
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

void logoutUser() {
    if (!currentLoggedInUser.username.empty()) {
        saveUserBookings(currentLoggedInUser.username, currentLoggedInUser.userBookings);
        // To ensure loyalty points are saved on logout, we need to update the allUsers vector
        std::vector<User> allUsers;
        loadUsers(allUsers); // Load all users
        for (auto& user : allUsers) {
            if (user.username == currentLoggedInUser.username) {
                user.loyaltyPoints = currentLoggedInUser.loyaltyPoints; // Update points for the logged out user
                break;
            }
        }
        saveUsers(allUsers); // Save all users with updated points

        currentLoggedInUser = User(); // Reset the global logged-in user object
        std::cout << "\nLogged out successfully.\n";
    }
    else {
        std::cout << "\nNo user is currently logged in.\n";
    }
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
}
