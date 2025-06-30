#ifndef MOVIE_H
#define MOVIE_H

class Movie {
public:
    std::string title;
    std::string genre;
    std::string director;
    int duration;
    std::vector<std::string> showtimes;
    std::map<std::string, std::vector<std::vector<bool>>> seatMaps;
    double price;
    int ageRestriction;

    Movie(std::string title, std::string genre, std::string director, int duration,
        std::vector<std::string> showtimes, double price, int ageRestriction)
        : title(std::move(title)),
        genre(std::move(genre)),
        director(std::move(director)),
        duration(duration),
        showtimes(std::move(showtimes)),
        price(price),
        ageRestriction(ageRestriction)
    {
        for (const auto& time : this->showtimes) {
            seatMaps[time] = std::vector<std::vector<bool>>(10, std::vector<bool>(10, false));
        }
    }

    Movie() : duration(0), price(0.0), ageRestriction(0) {}
};

void displayShowtimes(const Movie& movie);

#endif
