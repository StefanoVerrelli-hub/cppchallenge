Booking System API Documentation

Welcome to the Booking Service API documentation. Below you will find a brief overview of the API endpoints and functionalities provided by the BookingService class.

Overview

The BookingService API allows users to interact with a booking system for movies and theaters. Users can view available movies, select a movie, choose a theater, view available seats, and book seats for a selected movie and theater.

API Endpoints

viewAllMovies()


    Description: Retrieves a list of all available movies.

    Parameters: None

    Returns: A string containing the list of movies.


selectMovie(const int movieIndex)


    Description: Selects a movie based on the provided movie index.

    Parameters: movieIndex - The index of the movie to select.

    Returns: A string confirming the selected movie.


showTheatersForSelectedMovie()


    Description: Displays a list of theaters showing the selected movie.

    Parameters: None

    Returns: A string containing the list of theaters.


selectTheater(int theaterNumber)


    Description: Selects a theater based on the provided theater number.

    Parameters: theaterNumber - The number of the theater to select.

    Returns: A string confirming the selected theater.


showAvailableSeats()


    Description: Shows the available seats in the selected theater.

    Parameters: None

    Returns: A string containing the list of available seats.


bookSeats(const std::vector<int>& seatNumbers)


    Description: Books the seats with the provided seat numbers in the selected theater.

    Parameters: seatNumbers - A vector of seat numbers to book.

    Returns: A string confirming the booked seats.


### Demo Booking System Initialization and Maintenance

#### Initialization:
1. **Create Movies and Theaters**:
   - Use the `Movie` and `Theater` class constructors to create movies and theaters with specified details.

2. **Add Movies to BookingService**:
   - Add the created movies to the `BookingService` instance using the `push_back` method.

#### Maintenance:
1. **Adding New Movies or Theaters**:
   - To add new movies or theaters, create instances of the `Movie` and `Theater` classes and include them in the `BookingService`.

2. **Updating Seat Availability**:
   - Modify the `isBooked` attribute of seats to reflect their availability based on user bookings.

3. **User Interactions**:
   - Ensure user interactions in the main function align with the functionalities offered by the BookingService API endpoints.


Usage Example

include <iostream>
#include "bookingsystem.h"

void displayMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. View All Movies" << std::endl;
    std::cout << "2. Select Movie" << std::endl;
    std::cout << "3. Show Theaters for Selected Movie" << std::endl;
    std::cout << "4. Select Theater" << std::endl;
    std::cout << "5. Show Available Seats" << std::endl;
    std::cout << "6. Book Seats" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
     // Initialize movies, theaters, and seats using constructors
    Movie movie1(1,"Movie 1");
    movie1.theaters.push_back(Theater(1,"Main Theater", 2));
    movie1.theaters.push_back(Theater(3,"VIP Theater", 3));
    
    Movie movie2(2,"Movie 2");
    movie2.theaters.push_back(Theater(2,"Club Theater", 1));
    movie2.theaters.push_back(Theater(4,"VIP ClubTheater", 2));

    // Add movie to the booking service
    BookingService bookingService;
    bookingService.movies.push_back(movie1);
    bookingService.movies.push_back(movie2);
    

    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                bookingService.viewAllMovies();
                break;
            case 2: {
                int indexMovie;//std::string movieTitle;
                std::cout << "Enter the movie index: ";
                //std::cin.ignore(); // Consume the newline character
                std::cin >> indexMovie;
                bookingService.selectMovie(indexMovie);
                break;
            }
            case 3:
                bookingService.showTheatersForSelectedMovie();
                break;
            case 4: {
                int theaterNumber;
                std::cout << "Enter the theater number: ";
                std::cin >> theaterNumber;
                bookingService.selectTheater(theaterNumber);
                break;
            }
            case 5:
                bookingService.showAvailableSeats();
                break;
            case 6: {
                std::vector<int> seatNumbers;
                int seatNumber;
                std::cout << "Enter seat numbers (separated by spaces, end with -1): ";
                while (std::cin >> seatNumber && seatNumber != -1) {
                    seatNumbers.push_back(seatNumber);
                }
                bookingService.bookSeats(seatNumbers);
                break;
            }
            case 0:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}


### Notes
- The `dataMutex` member variable is used to protect access to shared data in a multi-threaded environment.
- The `selectedMovie` and `selectedTheater` static thread-local variables store the selected movie and theater for each thread.

For more details on each API endpoint and their usage, please refer to the provided API headers and consult the BookingService class implementation.

If you have any further questions or require assistance, please feel free to reach out to us. Thank you for using the Booking Service API!