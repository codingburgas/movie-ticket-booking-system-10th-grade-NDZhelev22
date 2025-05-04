#include "cinema.h"
#include <iostream>

void displayCinemas(const std::vector<Cinema>& cinemas) {
    std::cout << "\nAvailable Cinemas:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i].name
            << " (" << cinemas[i].location << ")\n";
    }
}

void displayMovies(const Cinema& cinema) {
    std::cout << "\nMovies available at " << cinema.name << ":\n";
    for (size_t i = 0; i < cinema.movies.size(); ++i) {
        const auto& movie = cinema.movies[i];
        std::cout << i + 1 << ". " << movie.title
            << " (" << movie.genre << ")\n"
            << "   Director: " << movie.director << "\n"
            << "   Duration: " << movie.duration / 60 << "h "
            << movie.duration % 60 << "m\n"
            << "   Age restriction: " << movie.ageRestriction << "+\n"
            << "   Price: $" << movie.price << "\n";
    }
}
