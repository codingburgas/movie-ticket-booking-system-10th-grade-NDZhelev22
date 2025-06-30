#include "../include/precompiler.h"

void displayCinemas(const std::vector<Cinema>& cinemas) {
    std::cout << "\n=== Available Cinemas ===\n";
    if (cinemas.empty()) {
        std::cout << "No cinemas available.\n";
        return;
    }
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << (i + 1) << ". " << cinemas[i].name
            << " (" << cinemas[i].location << ")\n";
    }
    std::cout << "Enter your choice: ";
}

void displayMovies(const Cinema& cinema) {
    std::cout << "\n=== Movies available at " << cinema.name << " ===\n";
    if (cinema.movies.empty()) {
        std::cout << "No movies available at this cinema.\n";
        return;
    }
    for (size_t i = 0; i < cinema.movies.size(); ++i) {
        const Movie& movie = cinema.movies[i];
        std::cout << (i + 1) << ". " << movie.title
            << " (" << movie.genre << ")\n"
            << "    Director: " << movie.director << "\n"
            << "    Duration: " << movie.duration / 60 << "h "
            << movie.duration % 60 << "m\n"
            << "    Age restriction: " << (movie.ageRestriction == 0 ? "All" : std::to_string(movie.ageRestriction) + "+") << "\n"
            << "    Price: $" << std::fixed << std::setprecision(2) << movie.price << "\n";
    }
    std::cout << "Enter your choice: ";
}
