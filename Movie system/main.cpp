#include "cinema_booking.h"

void displayCinemas(const std::vector<Cinema>& cinemas) {
    std::cout << "Select a cinema:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i].name << "\n";
    }
}

void displayMovies(const Cinema& cinema) {
    std::cout << "Movies available at " << cinema.name << ":\n";
    for (const auto& movie : cinema.movies) {
        std::cout << "- " << movie.title << " (" << movie.genre << ")\n";
    }
}

int main() {
    std::vector<Cinema> cinemas = {
        {"Burgas", {{"Avatar", "Sci-Fi"}, {"Titanic", "Romance"}}},
        {"Varna", {{"The Batman", "Action"}, {"Inception", "Sci-Fi"}}},
        {"Sofia", {{"Frozen II", "Animation"}, {"Joker", "Drama"}}},
        {"Plovdiv", {{"Spider-Man: No Way Home", "Action"}, {"Dune", "Sci-Fi"}}},
        {"Stara Zagora", {{"Black Widow", "Action"}, {"Soul", "Animation"}}}
    };

    displayCinemas(cinemas);

    int choice;
    std::cout << "Enter the number of the cinema you want to choose: ";
    std::cin >> choice;

    if (choice > 0 && choice <= cinemas.size()) {
        displayMovies(cinemas[choice - 1]);
    }
    else {
        std::cout << "Invalid choice. Please restart the program.\n";
    }
}