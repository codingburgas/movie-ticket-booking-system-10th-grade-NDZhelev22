#ifndef USER_H
#define USER_H

#include "booking.h"

extern class User currentLoggedInUser;

class User {
public:
    std::string username;
    std::string hashedPassword;

    std::vector<Booking> userBookings;

    User(std::string username, std::string hashedPassword)
        : username(std::move(username)), hashedPassword(std::move(hashedPassword)) {
    }

    User() {}
};

#endif
