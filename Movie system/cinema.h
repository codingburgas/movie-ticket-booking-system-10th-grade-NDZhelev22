#ifndef CINEMA_H
#define CINEMA_H

#include "movie.h"
#include <string>
#include <vector>

struct Cinema {
    std::string name;
    std::string location;
    std::vector<Movie> movies;
};

void displayCinemas(const std::vector<Cinema>& cinemas);
void displayMovies(const Cinema& cinema);

#endif
