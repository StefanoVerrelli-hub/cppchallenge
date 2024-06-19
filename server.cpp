#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <thread>
#include "bookingsystem.h"

#define PORT 8080

BookingService bookingService;

void viewAllMovies(int clientSocket) {
    std::string response = bookingService.viewAllMovies();
    send(clientSocket, response.c_str(), response.length(), 0);
}

void choiceMovie(int clientSocket,int movieTitle){
    std::string response = bookingService.selectMovie( movieTitle);
    send(clientSocket, response.c_str(), response.length(), 0);
}

void showTheatersForSelectedMovie(int clientSocket) {
    std::string response = bookingService.showTheatersForSelectedMovie();
    send(clientSocket, response.c_str(), response.length(), 0);
}

void choiceTheater(int clientSocket, int theaterNumber) {
    std::string response = bookingService.selectTheater(theaterNumber);
    send(clientSocket, response.c_str(), response.length(), 0);
}

void showAvailableSeats(int clientSocket) {
    std::string response = bookingService.showAvailableSeats();
    send(clientSocket, response.c_str(), response.length(), 0);
}

void bookSeats(int clientSocket,const std::vector<int>& seatNumbers) {
    std::string response = bookingService.bookSeats( seatNumbers);
    send(clientSocket, response.c_str(), response.length(), 0);
}

void handleClient(int clientSocket) {
    char buffer[1024]= {0};
    int valread;
    std::vector<int> seatNumbers;
    int seatNumber;
  
    std::string climenu = "\n\nWelcome to the Booking System demo\n1. viewAllMovies\n2. selectMovie\n3. showTheatersForSelectedMovie\n4. selectTheater\n5. showAvailableSeats\n6. bookSeats\n7. Exit\nEnter your choice: ";
    std::string selectMovie = "Enter the movie index:\n";
    std::string selectTheatre = "Enter the theater number:\n";
    std::string bookSeat = "Enter seat numbers (separated by cr, end with -1): \n";
    std::string exit = "Exiting the program. Goodbye!\n";
    std::string errordefault = "Invalid choice. Please try again.\n";
    while (true) {
        // Send menu to client
        send(clientSocket, climenu.c_str(), climenu.length(), 0);

        // Read client response
        valread= read(clientSocket, buffer, 1024);
        if (valread <= 0) {
            break; // Connection closed or an error occurred
        }
        buffer[valread] = '\0'; // Null-terminate the input
        int choice = std::atoi(buffer);

        // Handle client choice
        switch (choice) {
            case 1:
                viewAllMovies(clientSocket);
                break;

            case 2:
                // Send menu to client
                send(clientSocket, selectMovie.c_str(), selectMovie.length(), 0);
                valread = read(clientSocket, buffer, 1024);
                buffer[valread] = '\0'; // Null-terminate the input
                choiceMovie(clientSocket,std::atoi(buffer));
                break;

            case 3:
                showTheatersForSelectedMovie(clientSocket);
                break;
               
            case 4:
                send(clientSocket, selectTheatre.c_str(), selectTheatre.length(), 0);
                valread= read(clientSocket, buffer, 1024);
                buffer[valread] = '\0'; // Null-terminate the input
                choiceTheater(clientSocket,std::atoi(buffer));
                break;

            case 5:
                showAvailableSeats(clientSocket);
                break;

            case 6:                
                send(clientSocket, bookSeat.c_str(), bookSeat.length(), 0);
                while(true) {               
                    valread=read(clientSocket, buffer, sizeof(buffer));
                    buffer[valread ] = '\0'; // Null-terminate the input
                    seatNumber = std::atoi(buffer);
                    if (seatNumber == -1) {
                        break;
                    }

                    seatNumbers.push_back(std::atoi(buffer));
                }
                bookSeats(clientSocket,seatNumbers);
                seatNumbers.clear();
                break;

            case 7:
                send(clientSocket, exit.c_str(), exit.length(), 0);
                close(clientSocket);
                return;
            default:
                send(clientSocket, errordefault.c_str(), errordefault.length(), 0);;
                break;
        }
    }

    // Close the client socket
    close(clientSocket);
}

int main() {
    // Initialize movies, theaters, and seats using constructors
    Movie movie1(1,"Movie 1");
    movie1.theaters.push_back(Theater(1,"Main Theater", 20));
    movie1.theaters.push_back(Theater(3,"VIP Theater", 20));
    
    Movie movie2(2,"Movie 2");
    movie2.theaters.push_back(Theater(2,"Club Theater", 20));
    movie2.theaters.push_back(Theater(4,"VIP ClubTheater", 20));

    // Add movie to the booking service
    bookingService.movies.push_back(movie1);
    bookingService.movies.push_back(movie2);
    

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Define address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to address and port
    if (bind(server_fd, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return 1;
    }

    // Accept and handle clients in a loop
    while (true) {
        if ((new_socket = accept(server_fd, reinterpret_cast<struct sockaddr *>(&address), reinterpret_cast<socklen_t *>(&addrlen))) < 0) {
            perror("Accept failed");
            return 1;
        }

        // Create a new thread to handle the client
        std::thread clientThread(handleClient, new_socket);
        clientThread.detach(); // Detach the thread to run independently
    }

    return 0;
}
