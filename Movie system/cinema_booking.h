#ifndef CINEMA_H
#define CINEMA_H

#include <iostream>
#include <string>
#include <vector>

struct Movie {
    std::string title;
    std::string genre;
};

struct Cinema {
    std::string name;
    std::vector<Movie> movies;
};

void displayCinemas(const std::vector<Cinema>& cinemas);
void displayMovies(const Cinema& cinema);

#endif