#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector> 

struct Booking {
    std::string cinema;
    std::string movie;
    std::string showtime;
    int tickets;
    double totalPrice;
    std::vector<std::string> selectedSeats;
};
void displayBookingConfirmation(const Booking& booking);

#endif
