#ifndef UTILS_H
#define UTILS_H

// Declarations only.
// The includes for these types are handled by precompiler.h when utils.cpp is compiled.
// For the header, we just need the declarations.

void clearScreen();
void clearInputBuffer();
int getValidInput(int maxChoice);
std::string toUpper(const std::string& s); // Declared here, defined in utils.cpp

std::string simpleHash(const std::string& input); // Declared here, defined in utils.cpp

void loadUsers(std::vector<User>& users); // Declared here, defined in utils.cpp
void saveUsers(const std::vector<User>& users); // Declared here, defined in utils.cpp

std::string getUserBookingsFilename(const std::string& username); // Declared here, defined in utils.cpp
void loadUserBookings(const std::string& username, std::vector<Booking>& userBookings); // Declared here, defined in utils.cpp
void saveUserBookings(const std::string& username, const std::vector<Booking>& userBookings); // Declared here, defined in utils.cpp

#endif // UTILS_H
