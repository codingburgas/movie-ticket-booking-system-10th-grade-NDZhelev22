#include "precompiler.h"

void displayBookingConfirmation(const Booking& booking) {
    std::cout << "\n=== Booking Confirmation ===\n";
    std::cout << "Cinema: " << booking.cinema << "\n";
    std::cout << "Movie: " << booking.movie << "\n";
    std::cout << "Showtime: " << booking.showtime << "\n";
    std::cout << "Tickets: " << booking.tickets << "\n";
    std::cout << "Seats: ";
    for (const std::string& seat : booking.selectedSeats) {
        std::cout << seat << " ";
    }
    std::cout << "\nTotal Price: $" << booking.totalPrice << "\n";
    std::cout << "Thank you for your booking!\n";
}