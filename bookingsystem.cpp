#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <sstream>
#include "bookingsystem.h"

thread_local Movie* BookingService::selectedMovie = nullptr;
thread_local Theater* BookingService::selectedTheater = nullptr;


std::string BookingService::viewAllMovies() {
    std::ostringstream oss;
    for (const auto& movie : movies) {
        std::cout <<"index "<< movie.index <<" title "<< movie.title << std::endl;
        oss <<"index "<< movie.index <<" title "<< movie.title << std::endl;
    }
    return oss.str();
}
std::string BookingService::selectMovie(int movieIndex) {
    std::ostringstream oss;
    //std::lock_guard<std::mutex> lock(dataMutex); // Lock the mutex
    selectedMovie = nullptr;
    selectedTheater = nullptr;
    for (auto& movie : movies) {
        if (movie.index == movieIndex) {
            selectedMovie = &movie;
            //userSelectedMovies[std::this_thread::get_id()] = selectedMovie;
            std::cout << "selectedMovie title: " << selectedMovie->title << std::endl;
            oss << "selected Movie title: " << selectedMovie->title << std::endl;
            return oss.str();
        }
    }
    std::cout << "Movie not found." << movieIndex << std::endl;
    oss << "Movie not found." << movieIndex << std::endl;
    return oss.str();
}

std::string BookingService::showTheatersForSelectedMovie() {
    std::ostringstream oss;
    if (selectedMovie) {
        for (const auto& theater : selectedMovie->theaters) {
            std::cout <<"number: "<< theater.theaterNumber <<" name: "<< theater.name << std::endl;
            oss <<"number: "<< theater.theaterNumber <<" name: "<< theater.name << std::endl; 
                                           
        } 
    }else{
        std::cout << "No movie selected." << std::endl;
        oss << "No movie selected." << std::endl;
    }
    return oss.str();
}

std::string BookingService::selectTheater(int theaterNumber) {
    std::ostringstream oss;
    //std::lock_guard<std::mutex> lock(dataMutex); // Lock the mutex
    selectedTheater = nullptr;
    if (selectedMovie) {
        for (auto& theater : selectedMovie->theaters) {
            if (theater.theaterNumber == theaterNumber) {
                selectedTheater = &theater;
                //userSelectedTheaters[std::this_thread::get_id()] = selectedTheater;
                break;
            }
        }
        if (selectedTheater == nullptr) {
            std::cout << "Theater not found for the selected movie." << std::endl;
            oss << "Theater not found for the selected movie." << std::endl;
        }else {
            std::cout << "Selected Theater: index "<< selectedTheater->theaterNumber << " name "<< selectedTheater->name << std::endl;
            oss << "Selected Theater: index "<< selectedTheater->theaterNumber << " name "<< selectedTheater->name << std::endl;
        }
    } else {
        std::cout << "No movie selected." << std::endl;
        std::cout << "To look for a Theater, You first needs to select a movie." << std::endl;
        oss << "No movie selected." << std::endl;
        oss << "To look for a Theater, You first needs to select a movie." << std::endl;
    } 
    return oss.str();
}

std::string BookingService::showAvailableSeats() {
    std::ostringstream oss;
    int freeCounter = 0;
    if (selectedTheater) {
        //std::lock_guard<std::mutex> lock(selectedTheater->theaterMutex);
        std::lock_guard<std::mutex> lock(dataMutex); // Lock the mutex 
        std::cout << "Theater \""<< selectedTheater->name << "\"contains " << selectedTheater->seats.size() << " seats."<< std::endl;
        oss << "Theater \""<< selectedTheater->name << "\"contains " << selectedTheater->seats.size() << " seats."<< std::endl;
        for (const auto& seat : selectedTheater->seats) {
            if (!seat.isBooked) {
                std::cout << "Seat " << seat.seatNumber << " is available." << std::endl;
                oss << "Seat " << seat.seatNumber << " is available." << std::endl;
                freeCounter++;
            }
        }
        if (freeCounter == 0 ) {
            std::cout << "There are no more available seats..."<< std::endl;
            std::cout << "The Theather is fully booked"<< std::endl;
            oss << "There are no more available seats..."<< std::endl;
            oss<< "The Theather is fully booked"<< std::endl;
        }
        // Mutex will be automatically unlocked when lock goes out of scope!
    } else {
        std::cout << "No theater selected." << std::endl;
        std::cout << "To look for an available seat, You first needs to select a Theatre." << std::endl;
        oss << "No theater selected." << std::endl;
        oss << "To look for an available seat, You first needs to select a Theatre." << std::endl;
    }
    return oss.str();
}

std::string BookingService::bookSeats(const std::vector<int>& seatNumbers) {
    std::ostringstream oss;
    if (selectedTheater) {
        //std::lock_guard<std::mutex> lock(selectedTheater->theaterMutex);
        std::lock_guard<std::mutex> lock(dataMutex); // Lock the mutex 
        for (int seatNumber : seatNumbers) {
            if (seatNumber <= (int) selectedTheater->seats.size()) {
                for (auto& seat : selectedTheater->seats) {
                    if (seat.seatNumber == seatNumber && !seat.isBooked) {
                        seat.isBooked = true;
                        std::cout << "Seat " << seatNumber << " booked successfully." << std::endl;
                        oss << "Seat " << seatNumber << " booked successfully." << std::endl;
                    }else {
                        if(seat.seatNumber == seatNumber && seat.isBooked){
                            std::cout << "Seat " << seatNumber << " is already booked." << std::endl;
                            oss << "Seat " << seatNumber << " is already booked." << std::endl;
                        }
                    }
                }
            } else {
                std::cout << "SeatNumber " << seatNumber << " is out of Theater Capacity." << std::endl;
                oss << "SeatNumber " << seatNumber << " is out of Theater Capacity." << std::endl;
            }
        }
        // Mutex will be automatically unlocked when lock goes out of scope!
    }else{
        std::cout << "No theater selected." << std::endl;
        std::cout << "To book a seat, You first needs to select a Theatre." << std::endl;
        oss << "No theater selected." << std::endl;
        oss << "To book a seat, You first needs to select a Theatre." << std::endl;
    }
    return oss.str();
}

        