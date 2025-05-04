#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>

struct Movie {
    std::string title;
    std::string genre;
    std::string director;
    int duration;
    std::vector<std::string> showtimes;
    double price;
    int ageRestriction;
};

void displayShowtimes(const Movie& movie);

#endif
