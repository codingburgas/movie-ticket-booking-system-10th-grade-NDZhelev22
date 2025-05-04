#include <iostream>
#include <vector>
#include "cinema.h"
#include "movie.h"
#include "booking.h"
#include "utils.h"

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
