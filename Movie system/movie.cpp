#include "precompiler.h"

void displayShowtimes(const Movie& movie) {
    std::cout << "\nAvailable showtimes for " << movie.title << ":\n";
    for (size_t i = 0; i < movie.showtimes.size(); ++i) {
        std::cout << i + 1 << ". " << movie.showtimes[i] << "\n";
    }
}
