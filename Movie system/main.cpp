#include "cinema_booking.h"

void displayCinemas(const std::vector<Cinema>& cinemas) {
    std::cout << "\nAvailable Cinemas:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i].name
            << " (" << cinemas[i].location << ")\n";
    }
}

void displayMovies(const Cinema& cinema) {
    std::cout << "\nMovies available at " << cinema.name << ":\n";
    for (size_t i = 0; i < cinema.movies.size(); ++i) {
        const auto& movie = cinema.movies[i];
        std::cout << i + 1 << ". " << movie.title
            << " (" << movie.genre << ")\n"
            << "   Director: " << movie.director << "\n"
            << "   Duration: " << movie.duration / 60 << "h "
            << movie.duration % 60 << "m\n"
            << "   Age restriction: " << movie.ageRestriction << "+\n"
            << "   Price: $" << movie.price << "\n";
    }
}

void displayShowtimes(const Movie& movie) {
    std::cout << "\nAvailable showtimes for " << movie.title << ":\n";
    for (size_t i = 0; i < movie.showtimes.size(); ++i) {
        std::cout << i + 1 << ". " << movie.showtimes[i] << "\n";
    }
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getValidInput(int maxOption) {
    int choice;
    while (true) {
        std::cout << "Enter your choice (1-" << maxOption << "): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > maxOption) {
            std::cout << "Invalid input. Please try again.\n";
            clearInputBuffer();
        }
        else {
            clearInputBuffer();
            return choice;
        }
    }
}

void displayBookingConfirmation(const Booking& booking) {
    std::cout << "\n=== Booking Confirmation ===\n";
    std::cout << "Cinema: " << booking.cinema << "\n";
    std::cout << "Movie: " << booking.movie << "\n";
    std::cout << "Showtime: " << booking.showtime << "\n";
    std::cout << "Tickets: " << booking.tickets << "\n";
    std::cout << "Total Price: $" << booking.totalPrice << "\n";
    std::cout << "Thank you for your booking!\n";
}

int main() {
    std::vector<Cinema> cinemas = {
        {"CineGrand Burgas", "Mall Galleria", {
            {"Avatar: The Way of Water", "Sci-Fi", "James Cameron", 192,
             {"10:00", "14:30", "19:00"}, 12.50, 12},
            {"Titanic", "Romance", "James Cameron", 195,
             {"11:00", "15:30"}, 8.50, 12},
            {"Paw Patrol: The Mighty Movie", "Animation", "Cal Brunker", 88,
             {"09:30", "12:00", "14:15"}, 7.00, 0}
        }},
        {"CineMax Varna", "Mall Varna", {
            {"The Batman", "Action", "Matt Reeves", 176,
             {"10:30", "14:00", "18:30", "22:00"}, 11.00, 15},
            {"Inception", "Sci-Fi", "Christopher Nolan", 148,
             {"13:00", "16:30", "20:00"}, 9.50, 12},
            {"Barbie", "Comedy", "Greta Gerwig", 114,
             {"11:30", "14:45", "17:30"}, 10.50, 12}
        }},
        {"Cineplex Sofia", "The Paradise Center", {
            {"Frozen II", "Animation", "Chris Buck", 103,
             {"10:00", "12:30", "15:00"}, 8.00, 0},
            {"Joker", "Drama", "Todd Phillips", 122,
             {"13:30", "16:45", "20:15"}, 10.00, 18},
            {"Oppenheimer", "Biography", "Christopher Nolan", 180,
             {"11:00", "15:00", "19:30"}, 12.00, 16}
        }}
    };

    std::vector<Booking> bookings;

    while (true) {
        displayCinemas(cinemas);
        int cinemaChoice = getValidInput(cinemas.size());
        Cinema selectedCinema = cinemas[cinemaChoice - 1];

        displayMovies(selectedCinema);
        int movieChoice = getValidInput(selectedCinema.movies.size());
        Movie selectedMovie = selectedCinema.movies[movieChoice - 1];

        displayShowtimes(selectedMovie);
        int showtimeChoice = getValidInput(selectedMovie.showtimes.size());
        std::string selectedShowtime = selectedMovie.showtimes[showtimeChoice - 1];

        std::cout << "\nEnter number of tickets: ";
        int tickets;
        std::cin >> tickets;
        clearInputBuffer();

        double totalPrice = tickets * selectedMovie.price;

        Booking newBooking = {
            selectedCinema.name,
            selectedMovie.title,
            selectedShowtime,
            tickets,
            totalPrice
        };

        displayBookingConfirmation(newBooking);
        bookings.push_back(newBooking);

        std::cout << "\nWould you like to make another booking? (y/n): ";
        char another;
        std::cin >> another;
        clearInputBuffer();

        if (tolower(another) != 'y') {
            break;
        }
    }

    std::cout << "\n=== Your Bookings ===\n";
    for (const auto& booking : bookings) {
        displayBookingConfirmation(booking);
    }

    return 0;
}