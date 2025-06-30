#include "../include/precompiler.h"

// Function definition
void displayCinemas(const std::vector<Cinema>& cinemas) {
    std::cout << "\n=== Available Cinemas ===\n";

    // Conditional statement
    if (cinemas.empty()) {
        std::cout << "No cinemas available.\n";
        return;
    }

    // Indexed for loop
    for (size_t i = 0; i < cinemas.size(); ++i) {
        // Member access and stream output
        std::cout << (i + 1) << ". " << cinemas[i].name
            << " (" << cinemas[i].location << ")\n";
    }

    std::cout << "Enter your choice: ";
}

// Function definition
void displayMovies(const Cinema& cinema) {
    std::cout << "\n=== Movies available at " << cinema.name << " ===\n";

    // Conditional statement
    if (cinema.movies.empty()) {
        std::cout << "No movies available at this cinema.\n";
        return;
    }

    // Indexed for loop
    for (size_t i = 0; i < cinema.movies.size(); ++i) {
        // Reference to const object
        const Movie& movie = cinema.movies[i];

        // Stream output, member access, arithmetic, and ternary operator
        std::cout << (i + 1) << ". " << movie.title
            << " (" << movie.genre << ")\n"
            << "    Director: " << movie.director << "\n"
            << "    Duration: " << movie.duration / 60 << "h "
            << movie.duration % 60 << "m\n"
            << "    Age restriction: "
            << (movie.ageRestriction == 0 ? "All" : std::to_string(movie.ageRestriction) + "+") << "\n"
            << "    Price: $" << std::fixed << std::setprecision(2) << movie.price << "\n";
    }

    std::cout << "Enter your choice: ";
}
