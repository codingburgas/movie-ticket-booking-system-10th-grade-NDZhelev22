#ifndef BOOKING_H
#define BOOKING_H

#include <string>

struct Booking {
    std::string cinema;
    std::string movie;
    std::string showtime;
    int tickets;
    double totalPrice;
};

void displayBookingConfirmation(const Booking& booking);

#endif
