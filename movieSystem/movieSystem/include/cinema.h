#ifndef CINEMA_H
#define CINEMA_H

class Movie;

class Cinema {
public:
    std::string name;
    std::string location;
    std::vector<Movie> movies;

    Cinema(std::string name, std::string location, std::vector<Movie> movies)
        : name(std::move(name)),
        location(std::move(location)),
        movies(std::move(movies))
    {
    }

    Cinema() {}
};

void displayCinemas(const std::vector<Cinema>& cinemas);
void displayMovies(const Cinema& cinema);

#endif
