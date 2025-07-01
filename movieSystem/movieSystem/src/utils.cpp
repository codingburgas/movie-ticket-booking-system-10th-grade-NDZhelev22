#include "../include/precompiler.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getValidInput(int maxChoice) {
    int choice;
    while (true) {
        std::cout << "Enter your choice (1-" << maxChoice << "): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > maxChoice) {
            std::cout << "Invalid input. Please try again.\n";
            std::cin.clear();
            clearInputBuffer();
        }
        else {
            clearInputBuffer();
            return choice;
        }
    }
}

std::string toUpper(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return result;
}

std::string simpleHash(const std::string& input) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(input));
}

const std::string USERS_FILE = "../Databases/users.txt";
const std::string SEAT_DATA_FILE = "../Databases/seat_data.txt";


void loadUsers(std::vector<User>& users) {
    users.clear();
    std::ifstream file(USERS_FILE);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string username, hashedPassword, loyaltyPointsStr;
            // Updated parsing to include loyaltyPoints
            if (std::getline(ss, username, '|') &&
                std::getline(ss, hashedPassword, '|') &&
                std::getline(ss, loyaltyPointsStr)) {
                User newUser(username, hashedPassword); // Pass hashedPassword to constructor
                newUser.loyaltyPoints = std::stoi(loyaltyPointsStr);
                users.push_back(newUser);
            }
        }
        file.close();
    }
}

void saveUsers(const std::vector<User>& users) {
    std::ofstream file(USERS_FILE);
    if (file.is_open()) {
        for (const auto& user : users) {
            // Use getHashedPassword() to access the private member
            file << user.username << "|" << user.getHashedPassword() << "|" << user.loyaltyPoints << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Error: Could not open users file for writing.\n";
    }
}

std::string getUserBookingsFilename(const std::string& username) {
    std::string safeUsername = username;
    for (char& c : safeUsername) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_') {
            c = '_';
        }
    }
    return "../Databases/bookings_" + safeUsername + ".txt";
}

void loadUserBookings(const std::string& username, std::vector<Booking>& userBookings) {
    userBookings.clear();
    std::string filename = getUserBookingsFilename(username);
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string userId, cinemaName, movieTitle, showtimeStr, ticketsStr, totalPriceStr, seatsStr;

            if (std::getline(ss, userId, '|') &&
                std::getline(ss, cinemaName, '|') &&
                std::getline(ss, movieTitle, '|') &&
                std::getline(ss, showtimeStr, '|') &&
                std::getline(ss, ticketsStr, '|') &&
                std::getline(ss, totalPriceStr, '|') &&
                std::getline(ss, seatsStr))
            {
                Booking b;
                b.userId = userId;
                b.cinema = cinemaName;
                b.movie = movieTitle;
                b.showtime = showtimeStr;
                b.tickets = std::stoi(ticketsStr);
                b.totalPrice = std::stod(totalPriceStr);

                std::stringstream seatSs(seatsStr);
                std::string seat;
                while (std::getline(seatSs, seat, ',')) {
                    if (!seat.empty()) {
                        b.selectedSeats.push_back(seat);
                    }
                }
                userBookings.push_back(b);
            }
        }
        file.close();
    }
}

void saveUserBookings(const std::string& username, const std::vector<Booking>& userBookings) {
    std::string filename = getUserBookingsFilename(username);
    std::ofstream file(filename, std::ios::trunc);

    if (file.is_open()) {
        for (const auto& booking : userBookings) {
            file << booking.userId << "|"
                << booking.cinema << "|"
                << booking.movie << "|"
                << booking.showtime << "|"
                << booking.tickets << "|"
                << std::fixed << std::setprecision(2) << booking.totalPrice << "|";

            for (size_t i = 0; i < booking.selectedSeats.size(); ++i) {
                file << booking.selectedSeats[i] << (i == booking.selectedSeats.size() - 1 ? "" : ",");
            }
            file << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Error: Could not open booking file for " << username << " for writing.\n";
    }
}

void notifyUser(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTimeStruct;
    if (localtime_s(&localTimeStruct, &currentTime) == 0) {
        std::cout << "\n--- Notification [" << std::put_time(&localTimeStruct, "%Y-%m-%d %H:%M:%S") << "] ---\n";
    }
    else {
        std::cout << "\n--- Notification [Timestamp Error] ---\n";
    }
    std::cout << message << "\n";
    std::cout << "-------------------------------------\n";
}

void saveSeatMaps(const std::vector<Cinema>& cinemas) {
    std::ofstream file(SEAT_DATA_FILE, std::ios::trunc);
    if (!file.is_open()) {
        std::cout << "Error: Could not open seat data file for writing.\n";
        return;
    }

    for (const auto& cinema : cinemas) {
        for (const auto& movie : cinema.movies) {
            for (const auto& showtimePair : movie.seatMaps) {
                const std::string& showtime = showtimePair.first;
                const std::vector<std::vector<bool>>& seats = showtimePair.second;

                std::string seatMapString;
                for (const auto& row : seats) {
                    for (bool seatStatus : row) {
                        seatMapString += (seatStatus ? '1' : '0');
                    }
                }
                file << cinema.name << "|" << movie.title << "|" << showtime << "|" << seatMapString << "\n";
            }
        }
    }
    file.close();
}

void loadSeatMaps(std::vector<Cinema>& cinemas) {
    std::ifstream file(SEAT_DATA_FILE);
    if (!file.is_open()) {
        // If file doesn't exist or can't be opened, it means no saved data,
        // so the default seat maps (all false) will be used.
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cinemaName, movieTitle, showtime, seatMapString;

        if (std::getline(ss, cinemaName, '|') &&
            std::getline(ss, movieTitle, '|') &&
            std::getline(ss, showtime, '|') &&
            std::getline(ss, seatMapString))
        {
            // Find the corresponding movie and showtime in the in-memory data
            for (auto& cinema : cinemas) {
                if (cinema.name == cinemaName) {
                    for (auto& movie : cinema.movies) {
                        if (movie.title == movieTitle) {
                            if (movie.seatMaps.count(showtime)) {
                                std::vector<std::vector<bool>>& seats = movie.seatMaps[showtime];
                                int charIndex = 0;
                                for (size_t r = 0; r < 10; ++r) {
                                    for (size_t c = 0; c < 10; ++c) {
                                        if (charIndex < seatMapString.length()) {
                                            seats[r][c] = (seatMapString[charIndex] == '1');
                                            charIndex++;
                                        }
                                    }
                                }
                            }
                            break; // Movie found
                        }
                    }
                    break; // Cinema found
                }
            }
        }
    }
    file.close();
}
