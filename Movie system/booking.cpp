#include "precompiler.h"

void displayBookingConfirmation(const Booking& booking) {
    std::cout << "\n--- Booking Confirmation ---\n";
    std::cout << "User ID: " << booking.userId << "\n";
    std::cout << "Cinema: " << booking.cinema << "\n";
    std::cout << "Movie: " << booking.movie << "\n";
    std::cout << "Showtime: " << booking.showtime << "\n";
    std::cout << "Tickets: " << booking.tickets << "\n";
    std::cout << "Seats: ";
    for (size_t i = 0; i < booking.selectedSeats.size(); ++i) {
        std::cout << booking.selectedSeats[i] << (i == booking.selectedSeats.size() - 1 ? "" : ", ");
    }
    std::cout << "\nTotal Price: $" << std::fixed << std::setprecision(2) << booking.totalPrice << "\n";
    std::cout << "----------------------------\n";
}
