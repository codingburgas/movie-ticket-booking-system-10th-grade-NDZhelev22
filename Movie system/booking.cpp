#include "booking.h"
#include <iostream>

void displayBookingConfirmation(const Booking& booking) {
    std::cout << "\n=== Booking Confirmation ===\n";
    std::cout << "Cinema: " << booking.cinema << "\n";
    std::cout << "Movie: " << booking.movie << "\n";
    std::cout << "Showtime: " << booking.showtime << "\n";
    std::cout << "Tickets: " << booking.tickets << "\n";
    std::cout << "Total Price: $" << booking.totalPrice << "\n";
    std::cout << "Thank you for your booking!\n";
}
