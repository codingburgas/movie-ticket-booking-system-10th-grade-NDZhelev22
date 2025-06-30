#include "precompiler.h"

void displayShowtimes(const Movie& movie) {
    std::cout << "\n=== Available showtimes for " << movie.title << " ===\n";
    if (movie.showtimes.empty()) {
        std::cout << "No showtimes available for this movie.\n";
        return;
    }
    for (size_t i = 0; i < movie.showtimes.size(); ++i) {
        std::cout << (i + 1) << ". " << movie.showtimes[i] << "\n";
    }
    std::cout << "Enter your choice: ";
}
