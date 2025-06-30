#ifndef UTILS_H
#define UTILS_H

class Cinema;
class Movie;
class User;
struct Booking;

void clearScreen();
void clearInputBuffer();
int getValidInput(int maxChoice);
std::string toUpper(const std::string& s);

std::string simpleHash(const std::string& input);
void loadUsers(std::vector<User>& users);
void saveUsers(const std::vector<User>& users);
std::string getUserBookingsFilename(const std::string& username);
void loadUserBookings(const std::string& username, std::vector<Booking>& userBookings);
void saveUserBookings(const std::string& username, const std::vector<Booking>& userBookings);

void notifyUser(const std::string& message);

// New declarations for seat map persistence
void saveSeatMaps(const std::vector<Cinema>& cinemas);
void loadSeatMaps(std::vector<Cinema>& cinemas);

#endif
