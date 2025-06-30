#include "precompiler.h" // This will pull in all necessary headers for definitions

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

const std::string USERS_FILE = "users.txt";

void loadUsers(std::vector<User>& users) {
    users.clear();
    std::ifstream file(USERS_FILE);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string username, hashedPassword;
            if (std::getline(ss, username, '|') && std::getline(ss, hashedPassword)) {
                users.emplace_back(username, hashedPassword);
            }
        }
        file.close();
    }
}

void saveUsers(const std::vector<User>& users) {
    std::ofstream file(USERS_FILE);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.username << "|" << user.hashedPassword << "\n";
        }
        file.close();
    }
    else {
        std::cerr << "Error: Could not open users file for writing.\n";
    }
}

std::string getUserBookingsFilename(const std::string& username) {
    std::string safeUsername = username;
    for (char& c : safeUsername) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_') {
            c = '_';
        }
    }
    return "bookings_" + safeUsername + ".txt";
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
        std::cerr << "Error: Could not open booking file for " << username << " for writing.\n";
    }
}
