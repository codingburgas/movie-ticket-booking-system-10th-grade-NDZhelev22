#ifndef BOOKING_H
#define BOOKING_H

struct Booking {
    std::string userId;
    std::string cinema;
    std::string movie;
    std::string showtime;
    int tickets;
    double totalPrice;
    std::vector<std::string> selectedSeats;

    Booking() : tickets(0), totalPrice(0.0) {}

    Booking(std::string userId, std::string cinema, std::string movie,
        std::string showtime, int tickets, double totalPrice,
        std::vector<std::string> selectedSeats)
        : userId(std::move(userId)),
        cinema(std::move(cinema)),
        movie(std::move(movie)),
        showtime(std::move(showtime)),
        tickets(tickets),
        totalPrice(totalPrice),
        selectedSeats(std::move(selectedSeats)) {
    }
};

void displayBookingConfirmation(const Booking& booking);

#endif
