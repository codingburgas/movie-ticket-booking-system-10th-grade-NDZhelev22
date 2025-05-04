#ifndef CINEMA_H
#define CINEMA_H

#include <iostream>
#include <string>
#include <vector>

struct Movie {
    std::string title;
    std::string genre;
    std::string director;
    int duration; // in minutes
    std::vector<std::string> showtimes;
    double price;
    int ageRestriction;
};

struct Cinema {
    std::string name;
    std::string location;
    std::vector<Movie> movies;
};

struct Booking {
    std::string cinema;
    std::string movie;
    std::string showtime;
    int tickets;
    double totalPrice;
};

void displayCinemas(const std::vector<Cinema>& cinemas);
void displayMovies(const Cinema& cinema);

#endif