#include "precompiler.h"

User currentLoggedInUser;

void displayLogo();
void displaySeatMap(const std::vector<std::vector<bool>>& seats);
bool isValidSeatCode(const std::string& code);
std::pair<int, int> decodeSeat(const std::string& code);

void bookTicket(std::vector<Cinema>& cinemas);
void cancelBooking(std::vector<Cinema>& cinemas);
void displayMyBookings();
void supportPage();
void displayUserProfile(); // New: Declaration for the user profile display function

void displayLogo() {
    std::cout << R"(
   ____ ___ _  _ _____  ___ __  __    _    ____
  / ___|_ _| \ | |_  _||_ _|  \/  |  / \  |  _ \
 | |    | ||  \| | | |  | || |\/| | / _ \ | | | |
 | |___ | || |\  | | |  | || |  | |/ ___ \| |_| |
  \____|___|_| \_| |_| |___|_|  |_/_/   \_\____/
    )" << "\n";
}

void displaySeatMap(const std::vector<std::vector<bool>>& seats) {
    std::cout << "\n    ";
    for (char c = 'A'; c < 'A' + 10; ++c) std::cout << " " << c;
    std::cout << "\n";

    for (size_t row = 0; row < 10; ++row) {
        if (row + 1 < 10) std::cout << " " << row + 1 << " ";
        else std::cout << row + 1 << " ";
        for (size_t col = 0; col < 10; ++col) {
            std::cout << (seats[row][col] ? " X" : " _");
        }
        std::cout << "\n";
    }
}

bool isValidSeatCode(const std::string& code) {
    if (code.length() < 2 || code.length() > 3) return false;
    try {
        size_t lastCharPos = code.length() - 1;
        int row = std::stoi(code.substr(0, lastCharPos));
        char col = toupper(static_cast<unsigned char>(code.back()));
        return row >= 1 && row <= 10 && col >= 'A' && col <= 'J';
    }
    catch (...) {
        return false;
    }
}

std::pair<int, int> decodeSeat(const std::string& code) {
    size_t lastCharPos = code.length() - 1;
    int row = std::stoi(code.substr(0, lastCharPos)) - 1;
    int col = toupper(static_cast<unsigned char>(code.back())) - 'A';
    return { row, col };
}

void bookTicket(std::vector<Cinema>& cinemas) {
    if (currentLoggedInUser.username.empty()) {
        std::cout << "\nPlease log in to book tickets.\n";
        std::cout << "\nPress Enter to return to the main menu...";
        std::cin.get();
        clearScreen();
        return;
    }

    clearScreen();
    displayCinemas(cinemas);
    int cinemaChoice = getValidInput(static_cast<int>(cinemas.size()));
    Cinema& selectedCinema = cinemas[static_cast<size_t>(cinemaChoice) - 1];

    clearScreen();
    displayMovies(selectedCinema);
    int movieChoice = getValidInput(static_cast<int>(selectedCinema.movies.size()));
    Movie& selectedMovie = selectedCinema.movies[static_cast<size_t>(movieChoice) - 1];

    clearScreen();
    displayShowtimes(selectedMovie);
    int showtimeChoice = getValidInput(static_cast<int>(selectedMovie.showtimes.size()));
    std::string selectedShowtime = selectedMovie.showtimes[static_cast<size_t>(showtimeChoice) - 1];

    std::vector<std::vector<bool>>& seats = selectedMovie.seatMaps[selectedShowtime];

    std::cout << "\nEnter number of tickets: ";
    int tickets;
    while (!(std::cin >> tickets) || tickets <= 0 || tickets > (10 * 10)) {
        std::cout << "Invalid number of tickets. Please enter a positive number up to " << (10 * 10) << ": ";
        std::cin.clear();
        clearInputBuffer();
    }
    clearInputBuffer();

    std::vector<std::string> selectedSeats;
    std::vector<std::pair<int, int>> selectedSeatPositions;

    for (int i = 0; i < tickets; ++i) {
        while (true) {
            clearScreen();
            std::cout << "\nSelect seat for ticket #" << (i + 1) << " for movie " << selectedMovie.title
                << " at " << selectedShowtime << " in " << selectedCinema.name << ":\n";
            displaySeatMap(seats);
            std::cout << "Enter seat (e.g., 3C): ";
            std::string seatCode;
            std::getline(std::cin, seatCode);
            seatCode = toUpper(seatCode);

            if (!isValidSeatCode(seatCode)) {
                std::cout << "Invalid seat format. Try again.\n";
                std::cin.get();
                continue;
            }

            std::pair<int, int> seatPos = decodeSeat(seatCode);
            int row = seatPos.first;
            int col = seatPos.second;

            if (row < 0 || row >= 10 || col < 0 || col >= 10) {
                std::cout << "Internal error: Decoded seat out of expected bounds. Please report this.\n";
                std::cin.get();
                continue;
            }

            if (seats[static_cast<size_t>(row)][static_cast<size_t>(col)]) {
                std::cout << "Seat " << seatCode << " is already taken. Choose another.\n";
                std::cin.get();
                continue;
            }

            bool alreadySelectedInSession = false;
            for (const auto& s : selectedSeats) {
                if (s == seatCode) {
                    alreadySelectedInSession = true;
                    break;
                }
            }
            if (alreadySelectedInSession) {
                std::cout << "You have already selected seat " << seatCode << " for this booking. Choose another.\n";
                std::cin.get();
                continue;
            }

            seats[static_cast<size_t>(row)][static_cast<size_t>(col)] = true;
            selectedSeats.push_back(seatCode);
            selectedSeatPositions.push_back(seatPos);
            break;
        }
    }

    double totalPrice = tickets * selectedMovie.price;

    clearScreen();
    std::cout << "\n--- Booking Summary ---\n";
    std::cout << "Movie: " << selectedMovie.title << "\n";
    std::cout << "Showtime: " << selectedShowtime << "\n";
    std::cout << "Seats: ";
    for (size_t i = 0; i < selectedSeats.size(); ++i) {
        std::cout << selectedSeats[i] << (i == selectedSeats.size() - 1 ? "" : ", ");
    }
    std::cout << "\nTotal amount: $" << std::fixed << std::setprecision(2) << totalPrice << "\n";
    std::cout << "Your current loyalty points: " << currentLoggedInUser.loyaltyPoints << "\n";
    std::cout << "-----------------------\n";

    // Loyalty points redemption
    if (currentLoggedInUser.loyaltyPoints >= 100) { // Example: 100 points for a discount
        std::cout << "\nWould you like to redeem 100 loyalty points for a $5 discount? (Y/N): ";
        std::string redeemChoice;
        std::getline(std::cin, redeemChoice);
        redeemChoice = toUpper(redeemChoice);

        if (redeemChoice == "Y") {
            totalPrice -= 5.00; // Apply discount
            currentLoggedInUser.loyaltyPoints -= 100; // Deduct points
            std::cout << "Discount applied! New total: $" << std::fixed << std::setprecision(2) << totalPrice << "\n";
            std::cout << "Remaining loyalty points: " << currentLoggedInUser.loyaltyPoints << "\n";
        }
    }

    std::cout << "\nSelect payment method:\n";
    std::cout << "1. Online with card\n";
    std::cout << "2. On-site with ticket agent\n";
    int paymentMethodChoice = getValidInput(2);

    bool paymentSuccessful = false;
    if (paymentMethodChoice == 1) {
        std::string cardNumber;
        while (true) {
            std::cout << "Enter 12-digit card number: ";
            std::getline(std::cin, cardNumber);
            if (cardNumber.length() == 12 && std::all_of(cardNumber.begin(), cardNumber.end(), ::isdigit)) {
                std::cout << "\nProcessing card payment...\n";
                paymentSuccessful = true;
                break;
            }
            else {
                std::cout << "Invalid card number. Please enter 12 digits.\n";
            }
        }
    }
    else if (paymentMethodChoice == 2) {
        std::cout << "\nPlease pay $" << std::fixed << std::setprecision(2) << totalPrice << " to the ticket agent.\n";
        std::cout << "Press Enter once payment is made: ";
        std::cin.get();
        paymentSuccessful = true;
    }

    if (paymentSuccessful) {
        std::cout << "Payment successful!\n";
        // Award loyalty points (e.g., 1 point per $1 spent)
        currentLoggedInUser.loyaltyPoints += static_cast<int>(totalPrice);
        notifyUser("New booking confirmed for " + currentLoggedInUser.username + " for movie '" + selectedMovie.title + "'. You earned " + std::to_string(static_cast<int>(totalPrice)) + " loyalty points!");

        Booking newBooking = {
            currentLoggedInUser.username,
            selectedCinema.name,
            selectedMovie.title,
            selectedShowtime,
            tickets,
            totalPrice,
            selectedSeats
        };

        currentLoggedInUser.userBookings.push_back(newBooking);
        saveUserBookings(currentLoggedInUser.username, currentLoggedInUser.userBookings);
        // Save all users to update loyalty points
        std::vector<User> allUsers;
        loadUsers(allUsers); // Reload all users to find and update the current user's points
        for (auto& user : allUsers) {
            if (user.username == currentLoggedInUser.username) {
                user.loyaltyPoints = currentLoggedInUser.loyaltyPoints;
                break;
            }
        }
        saveUsers(allUsers); // Save all users with updated points

        saveSeatMaps(cinemas);

        clearScreen();
        displayBookingConfirmation(newBooking);
        std::cout << "\nYour booking has been successfully recorded!\n";
        std::cout << "Current loyalty points: " << currentLoggedInUser.loyaltyPoints << "\n";

    }
    else {
        std::cout << "\nPayment canceled. Booking not completed.\n";
        for (const auto& pos : selectedSeatPositions) {
            seats[static_cast<size_t>(pos.first)][static_cast<size_t>(pos.second)] = false;
        }
        notifyUser("Booking process for " + currentLoggedInUser.username + " was canceled.");
    }

    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
}

void cancelBooking(std::vector<Cinema>& cinemas) {
    clearScreen();
    if (currentLoggedInUser.username.empty()) {
        std::cout << "\nPlease log in to cancel bookings.\n";
        std::cout << "\nPress Enter to return to the main menu...";
        std::cin.get();
        clearScreen();
        return;
    }

    if (currentLoggedInUser.userBookings.empty()) {
        std::cout << "\nYou have no bookings to cancel.\n";
        std::cout << "\nPress Enter to return to the main menu...";
        std::cin.get();
        clearScreen();
        return;
    }

    std::cout << "\n=== Your Bookings (" << currentLoggedInUser.username << ") ===\n";
    for (size_t i = 0; i < currentLoggedInUser.userBookings.size(); ++i) {
        const auto& booking = currentLoggedInUser.userBookings[i];
        std::cout << (i + 1) << ". Movie: " << booking.movie
            << ", Cinema: " << booking.cinema
            << ", Showtime: " << booking.showtime
            << ", Seats: ";
        for (size_t j = 0; j < booking.selectedSeats.size(); ++j) {
            std::cout << booking.selectedSeats[j] << (j == booking.selectedSeats.size() - 1 ? "" : ", ");
        }
        std::cout << "\n";
    }

    std::cout << "\nEnter the number of the booking to cancel (or 0 to go back): ";
    int bookingChoice = getValidInput(static_cast<int>(currentLoggedInUser.userBookings.size()));

    if (bookingChoice == 0) {
        clearScreen();
        return;
    }

    Booking bookingToCancel = currentLoggedInUser.userBookings[static_cast<size_t>(bookingChoice) - 1];

    bool seatsReverted = false;
    for (auto& cinema : cinemas) {
        if (cinema.name == bookingToCancel.cinema) {
            for (auto& movie : cinema.movies) {
                if (movie.title == bookingToCancel.movie) {
                    if (movie.seatMaps.count(bookingToCancel.showtime)) {
                        std::vector<std::vector<bool>>& seats = movie.seatMaps[bookingToCancel.showtime];
                        for (const auto& seatCode : bookingToCancel.selectedSeats) {
                            std::pair<int, int> seatPos = decodeSeat(seatCode);
                            seats[static_cast<size_t>(seatPos.first)][static_cast<size_t>(seatPos.second)] = false;
                        }
                        seatsReverted = true;
                        break;
                    }
                }
            }
            if (seatsReverted) break;
        }
    }

    currentLoggedInUser.userBookings.erase(currentLoggedInUser.userBookings.begin() + (bookingChoice - 1));
    saveUserBookings(currentLoggedInUser.username, currentLoggedInUser.userBookings);
    saveSeatMaps(cinemas);

    notifyUser("Booking for movie '" + bookingToCancel.movie + "' at " + bookingToCancel.showtime + " has been canceled.");
    std::cout << "\nBooking successfully canceled!\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
}


void displayMyBookings() {
    clearScreen();
    if (currentLoggedInUser.username.empty()) {
        std::cout << "\nPlease log in to view your bookings.\n";
        std::cout << "\nPress Enter to return to the main menu...";
        std::cin.get();
        clearScreen();
        return;
    }

    std::cout << "\n=== Your Bookings (" << currentLoggedInUser.username << ") ===\n";
    if (currentLoggedInUser.userBookings.empty()) {
        std::cout << "You have no bookings yet.\n";
    }
    else {
        for (const auto& booking : currentLoggedInUser.userBookings) {
            displayBookingConfirmation(booking);
            std::cout << "\n";
        }
    }
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
}

void supportPage() {
    clearScreen();
    std::string complaint;
    std::cout << "\n=== Support / File a Complaint ===\n";
    std::cout << "Please enter your complaint or feedback:\n> ";
    std::getline(std::cin, complaint);
    std::cout << "\nThank you! Your complaint has been recorded.\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
}

// New: Function to display user profile statistics
void displayUserProfile() {
    clearScreen();
    if (currentLoggedInUser.username.empty()) {
        std::cout << "\nPlease log in to view your profile.\n";
        std::cout << "\nPress Enter to return to the main menu...";
        std::cin.get();
        clearScreen();
        return;
    }

    std::cout << "\n=== User Profile: " << currentLoggedInUser.username << " ===\n";
    std::cout << "Loyalty Points: " << currentLoggedInUser.loyaltyPoints << "\n";
    std::cout << "Total Bookings Made: " << currentLoggedInUser.userBookings.size() << "\n";
    // Add more statistics here if desired, e.g., total money spent, favorite genre, etc.
    std::cout << "-----------------------------------\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
    clearScreen();
}


int main() {
    std::vector<Cinema> cinemas = {
        Cinema("CineGrand Burgas", "Mall Galleria", {
            Movie("Avatar: The Way of Water", "Sci-Fi", "James Cameron", 192,
                 {"10:00", "14:30", "19:00", "22:30"}, 12.50, 12),
            Movie("Titanic", "Romance", "James Cameron", 195,
                 {"11:00", "15:30", "20:00"}, 8.50, 12),
            Movie("Paw Patrol: The Mighty Movie", "Animation", "Cal Brunker", 88,
                 {"09:30", "12:00", "14:15", "16:30"}, 7.00, 0),
            Movie("Dune: Part Two", "Sci-Fi", "Denis Villeneuve", 166,
                 {"10:15", "13:45", "17:15", "20:45"}, 14.00, 12)
        }),
        Cinema("CineMax Varna", "Mall Varna", {
            Movie("The Batman", "Action", "Matt Reeves", 176,
                 {"10:30", "14:00", "18:30", "22:00"}, 11.00, 15),
            Movie("Inception", "Sci-Fi", "Christopher Nolan", 148,
                 {"13:00", "16:30", "20:00", "23:00"}, 9.50, 12),
            Movie("Barbie", "Comedy", "Greta Gerwig", 114,
                 {"11:30", "14:45", "17:30", "20:15"}, 10.50, 12),
            Movie("Oppenheimer", "Biography", "Christopher Nolan", 180,
                 {"11:00", "15:00", "19:30"}, 12.00, 16)
        }),
        Cinema("Cineplex Sofia", "The Paradise Center", {
            Movie("Frozen II", "Animation", "Chris Buck", 103,
                 {"10:00", "12:30", "15:00", "17:30"}, 8.00, 0),
            Movie("Joker", "Drama", "Todd Phillips", 122,
                 {"13:30", "16:45", "20:15", "22:45"}, 10.00, 18),
            Movie("Spider-Man: Across the Spider-Verse", "Animation", "Joaquim Dos Santos", 140,
                 {"10:45", "13:30", "16:15", "19:00"}, 11.50, 6)
        }),
        Cinema("Arena Plovdiv", "Mall Plovdiv", {
            Movie("Guardians of the Galaxy Vol. 3", "Sci-Fi", "James Gunn", 150,
                 {"10:00", "13:00", "16:00", "19:00", "22:00"}, 13.00, 12),
            Movie("The Super Mario Bros. Movie", "Animation", "Aaron Horvath", 92,
                 {"09:00", "11:00", "13:00", "15:00"}, 7.50, 0),
            Movie("Mission: Impossible - Dead Reckoning Part One", "Action", "Christopher McQuarrie", 163,
                 {"11:30", "15:00", "18:30", "21:45"}, 13.50, 12)
        })
    };

    loadSeatMaps(cinemas);

    std::vector<User> allUsers;
    loadUsers(allUsers);

    while (true) {
        clearScreen();
        displayLogo();
        std::cout << "\nWelcome to the CINEMA Booking System!\n\n";

        if (currentLoggedInUser.username.empty()) {
            std::cout << "1. Register\n";
            std::cout << "2. Login\n";
            std::cout << "3. Exit\n\n";
            int choice = getValidInput(3);

            if (choice == 1) {
                registerUser(allUsers);
            }
            else if (choice == 2) {
                loginUser(allUsers);
            }
            else if (choice == 3) {
                saveSeatMaps(cinemas);
                break;
            }
        }
        else {
            std::cout << "Logged in as: " << currentLoggedInUser.username << "\n\n";
            std::cout << "1. Book a Ticket\n";
            std::cout << "2. My Bookings\n";
            std::cout << "3. Cancel Booking\n";
            std::cout << "4. User Profile\n"; // New: User Profile option
            std::cout << "5. Support / File a Complaint\n";
            std::cout << "6. Logout\n";
            std::cout << "7. Exit System\n\n"; // Max choice updated to 7
            int choice = getValidInput(7);

            if (choice == 1) {
                bookTicket(cinemas);
            }
            else if (choice == 2) {
                displayMyBookings();
            }
            else if (choice == 3) {
                cancelBooking(cinemas);
            }
            else if (choice == 4) {
                displayUserProfile();
            }
            else if (choice == 5) {
                supportPage();
            }
            else if (choice == 6) {
                logoutUser();
            }
            else if (choice == 7) {
                saveSeatMaps(cinemas);
                std::vector<User> tempUsers;
                loadUsers(tempUsers);
                for (auto& user : tempUsers) {
                    if (user.username == currentLoggedInUser.username) {
                        user.loyaltyPoints = currentLoggedInUser.loyaltyPoints;
                        break;
                    }
                }
                saveUsers(tempUsers);

                if (!currentLoggedInUser.username.empty()) {
                    saveUserBookings(currentLoggedInUser.username, currentLoggedInUser.userBookings);
                }
                break;
            }
        }
    }

    clearScreen();
    std::cout << "\nThank you for using the CINEMA Booking System!\n";
}
