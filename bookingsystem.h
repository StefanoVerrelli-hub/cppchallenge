#ifndef BOOKINGSERVICE_H
#define BOOKINGSERVICE_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>

class Seat {
public:
    int seatNumber;
    bool isBooked;

    Seat(int number) : seatNumber(number), isBooked(false) {}
};

class Theater {
public:
    int theaterNumber;
    std::string name;
    std::vector<Seat> seats;

    Theater(int number, const std::string& tName, int numSeats) : theaterNumber(number), name(tName) {
        for (int i = 1; i <= numSeats; ++i) {
            seats.push_back(Seat(i));
        }
    }
};

class Movie {
public:
    int index;
    std::string title;
    std::vector<Theater> theaters;

    Movie(int idx, const std::string& t) : index(idx), title(t) {}
};

class BookingService {
public:
    std::vector<Movie> movies;
    std::mutex dataMutex; // Mutex for protecting access to shared data

    std::string viewAllMovies();
    std::string selectMovie(const int movieIndex);
    std::string showTheatersForSelectedMovie();
    std::string selectTheater(int theaterNumber);
    std::string showAvailableSeats();
    std::string bookSeats(const std::vector<int>& seatNumbers);

    static thread_local Movie* selectedMovie; // Thread-local storage for selected movie
    static thread_local Theater* selectedTheater; // Thread-local storage for selected theater
};

#endif
