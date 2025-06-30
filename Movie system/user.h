#ifndef USER_H
#define USER_H

#include "booking.h"

extern class User currentLoggedInUser;

class User {
public:
    std::string username;
    std::string hashedPassword;
    int loyaltyPoints;

    std::vector<Booking> userBookings;

    User(std::string username, std::string hashedPassword)
        : username(std::move(username)), hashedPassword(std::move(hashedPassword)), loyaltyPoints(0) {
    }

    User() : loyaltyPoints(0) {}
};

#endif
